#include <EV3_compute.hpp>

namespace finder::compute
{
    EV3_compute::EV3_compute()
    {
        m_tcp_communication_server = std::make_unique<::finder::network::tcp::TCPServer>();

        m_running = true;

        start();
    }

    EV3_compute::~EV3_compute()
    {
        // m_tcp_communication_server->sendMessage("exit");
        stop();
        m_client_thread.join();
    }

    void EV3_compute::start()
    {
        m_client_thread = std::thread([this]()
        {
            m_tcp_communication_server->start(34001);
            handle_client();
        });
    }

    void EV3_compute::stop()
    {
        m_tcp_communication_server->stop();
        m_running = false;
    }

    void EV3_compute::handle_client()
    {
        while (m_running)
        {
            std::cout << "waiting for client message..." << std::endl;
            std::string message = m_tcp_communication_server->receiveMessage();
            if (message.length() > 0)
            {
                std::cout << "received message: " << message << std::endl;
                std::string response = parse_message(message);

                std::cout << "sending response: " << response << std::endl;
                m_tcp_communication_server->sendMessage(response);
            } else {
                m_tcp_communication_server->sendMessage("invalid");
            }
        }
    }

    std::string EV3_compute::parse_message(const std::string &message)
    {
        ::finder::math::Vector2 start{};
         ::finder::math::Vector2 end{};
        // format of message: "start_x,start_y;end_x,end_y"
        size_t delimiter = message.find(';');
        if (delimiter == std::string::npos)
        {
            return std::string("invalid");
        }
        std::string start_str = message.substr(0, delimiter);
        std::string end_str = message.substr(delimiter + 1);
        size_t comma = start_str.find(',');
        if (comma == std::string::npos)
        {
            return std::string("invalid");
        }
        start.x = std::stof(start_str.substr(0, comma));
        start.y = std::stof(start_str.substr(comma + 1));
        comma = end_str.find(',');
        if (comma == std::string::npos)
        {
            return std::string("invalid");
        }
        end.x = std::stof(end_str.substr(0, comma));
        end.y = std::stof(end_str.substr(comma + 1));
        
        // find path
        std::vector<::finder::math::Vector2> path = m_pathfinder.findPath(start, end);

        // smooth path
        std::vector<::finder::math::Vector2> smooth_path = m_smooth_path.smoothPath(path);

        // flip path so that it starts at the start point
        std::reverse(smooth_path.begin(), smooth_path.end());

        // format of response: "x1,y1;x2,y2;...;xn,yn"
        std::string response;
        for (const auto &point : smooth_path)
        {
            response += std::to_string(point.x) + "," + std::to_string(point.y) + ";";
        }
        response.pop_back(); // remove trailing ';'

        return response;

        return std::string("invalid");
    }

} // namespace finder::compute
