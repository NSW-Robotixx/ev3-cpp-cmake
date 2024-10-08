#include <EV3_compute_tcp.hpp>

namespace finder::compute
{
    #if !EV3_COMPUTE_NO_TCP

    EV3_compute_tcp::EV3_compute_tcp()
    {
        m_tcp_communication_server = std::make_unique<::finder::network::tcp::TCPServer>();

        m_running = true;

        start();
    }

    EV3_compute_tcp::~EV3_compute_tcp()
    {
        // m_tcp_communication_server->sendMessage("exit");
        stop();
        m_client_thread.join();
    }

    void EV3_compute_tcp::start()
    {
        m_client_thread = std::thread([this]()
        {
            m_tcp_communication_server->start(EV3_COMPUTE_PORT);
            handle_client();
        });
    }

    void EV3_compute_tcp::stop()
    {
        m_tcp_communication_server->stop();
        m_running = false;
    }

    void EV3_compute_tcp::handle_client()
    {
        while (m_running)
        {
            _logger << "waiting for client message...";
            std::string message = m_tcp_communication_server->receiveMessage();
            if (message.length() > 0)
            {
                if (message == "exit")
                {
                    _logger << "received exit message from client";
                    break;
                }
                _logger << "received message: " << message;
                std::string response = extract_coordinates(message);

                _logger << "sending response: " << response;
                m_tcp_communication_server->sendMessage(response);
            } else {
                // throw std::runtime_error("Received empty message from client");
            }
        }
    }

    std::string EV3_compute_tcp::extract_coordinates(const std::string &message)
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

    #endif
} // namespace finder::compute
