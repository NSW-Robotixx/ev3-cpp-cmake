#include "../../EV3_conf.hpp"
#include <EV3_System_tcp.hpp>

namespace finder::system
{
    #if !EV3_COMPUTE_NO_TCP

    math::Vector2 SystemTcp::m_currentPosition = math::Vector2(0, 0);
    std::deque<math::Vector3> SystemTcp::m_destinations;
    std::shared_ptr<tcpcat::EventHandler> SystemTcp::m_eventHandler = std::make_shared<ComputeModuleEventHandler>();
    tcpcat::TcpClient SystemTcp::m_client(EV3_COMPUTE_IP, EV3_COMPUTE_PORT, m_eventHandler);
    std::condition_variable SystemTcp::m_cv;
    std::mutex SystemTcp::m_mutex;
    bool SystemTcp::finished = false;

    SystemTcp::SystemTcp()
    {
        
    }

    SystemTcp::~SystemTcp()
    {
        // wait for the compute module to finish
        std::unique_lock<std::mutex> lock(m_mutex);
        m_cv.wait(lock, [] { return finished; });

        #if EV3_COMPUTE_LOCAL
        m_compute.stop();
        #endif
    }

    void SystemTcp::start()
    {
        // Read the destinations from the file
        std::vector<math::Vector3> desinations = ConfigReader::readDestinationsFromFile();
        m_destinations = std::deque<math::Vector3>(desinations.begin(), desinations.end());

        m_client.Connect();

        if (!m_client.IsConnected())
        {
            log::Logger::error("Could not connect to the compute module");
            exit(1);
        }


#if EV3_COMPUTE_LOCAL
        // Start the compute module
        // m_compute.start();
#endif

        m_currentPosition = math::Vector2(0, 0); 

        // Start the first destination
        sendNextDestination();
    }

    void SystemTcp::stop()
    {
        #if EV3_COMPUTE_LOCAL
        m_compute.stop();
        #endif
    }

    void SystemTcp::reconnectComputeModule()
    {
        m_client.Connect();
    }

    void SystemTcp::sendNextDestination()
    {
        if (m_destinations.empty())
        {
            finished = true;
            m_cv.notify_all();
            m_client.Send(std::vector<unsigned char>("exit", "exit" + 4));
            log::Logger::info("All destinations have been reached");
            // exit(0);
            return;
        }

        math::Vector3 destination = m_destinations.front();
        m_destinations.pop_front();

        // Calculate the path to the destination
        // Send the path to the compute module
        // format of message: "start_x,start_y;end_x,end_y"
        std::string message = std::to_string(0) + "," + std::to_string(0) + ";" + std::to_string(destination.x) + "," + std::to_string(destination.y);
        m_client.Send(std::vector<unsigned char>(message.begin(), message.end()));

        m_currentPosition = math::Vector2(destination.x, destination.y);
    }

    void ComputeModuleEventHandler::OnConnected(std::shared_ptr<tcpcat::TcpSession> session)
    {
        log::Logger::debug("Connected to the compute module" + session->RemoteEndpoint().address().to_string() + ":" + std::to_string(session->RemoteEndpoint().port()));
    }

    void ComputeModuleEventHandler::OnReceived(std::shared_ptr<tcpcat::TcpSession> session, const std::vector<unsigned char> &buf, size_t bytes)
    {
        log::Logger::debug("Received message from the compute module: " + std::string(buf.begin(), buf.end()));
        SystemTcp::sendNextDestination();
    }

    void ComputeModuleEventHandler::OnError(std::shared_ptr<tcpcat::TcpSession> session, const asio::error_code &err)
    {
        log::Logger::error("Error on the compute module connection: " + err.message());

        if (!_reconnecting)
        {
        _reconnecting = true;

            for (int i = 0; i < 10; i++)
            {
                log::Logger::warn("Reconnecting to the compute module...");
                SystemTcp::reconnectComputeModule();
                if (session->IsConnected())
                {
                    log::Logger::debug("Reconnected to the compute module");
                    _reconnecting = false;
                    break;
                }
            }
            _reconnecting = false;
            log::Logger::error("Could not reconnect to the compute module");
            exit(1);
        }
    }

    void ComputeModuleEventHandler::OnDisconnected(std::shared_ptr<tcpcat::TcpSession> session)
    {
        log::Logger::warn("Disconnected from the compute module at: " + session->RemoteEndpoint().address().to_string() + ":" + std::to_string(session->RemoteEndpoint().port()));
    }

    void ComputeModuleEventHandler::OnSent(std::shared_ptr<tcpcat::TcpSession> session, const std::vector<unsigned char> &buf, size_t bytes)
    {
        log::Logger::debug("Sent message to the compute module: " + std::string(buf.begin(), buf.end()));
    }

    #endif

} // namespace finder::system
