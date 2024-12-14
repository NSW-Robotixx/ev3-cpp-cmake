#ifndef __EV3_SYSTEM_HPP__
#define __EV3_SYSTEM_HPP__

#include <Vector3.hpp>
#include <ConfigReader.hpp>
#include <EV3_compute_tcp.hpp>
#include <vector>
#include <deque>
#include <memory>
#include <condition_variable>
#include <tcpcat/tcpcat.h>

#include <spdlog/spdlog.h>

namespace finder::system
{
    /// @brief Event handler for the compute module
    class ComputeModuleEventHandler : public tcpcat::EventHandler
    {
        public:
            /// @brief Callback for when a connection is established
            /// @param session Session that was connected
            void OnConnected(std::shared_ptr<tcpcat::TcpSession> session) override;

            /// @brief Callback to be called when data is received
            /// @param session Session to listen to
            /// @param buf Buffer with the received data
            /// @param bytes Number of bytes received
            void OnReceived(std::shared_ptr<tcpcat::TcpSession> session, const std::vector<unsigned char> &buf, size_t bytes) override;

            /// @brief Callback to be called when an error occurs
            /// @param session Session to listen to
            /// @param err Error code
            void OnError(std::shared_ptr<tcpcat::TcpSession> session, const asio::error_code &err) override;

            /// @brief Callback to be called when a session is disconnected
            /// @param session Session to listen to
            void OnDisconnected(std::shared_ptr<tcpcat::TcpSession> session) override;

            /// @brief Callback to be called when data is sent
            /// @param session Session to listen to
            /// @param buf Buffer with the sent data
            /// @param bytes Number of bytes sent
            void OnSent(std::shared_ptr<tcpcat::TcpSession> session, const std::vector<unsigned char> &buf, size_t bytes) override;

        private:
            bool m_ready = false;
            bool _reconnecting = false;
    };

    /// @brief Class that represents the system and handles the communication with the compute module via TCP
    class SystemTcp
    {
        public:
            SystemTcp();
            ~SystemTcp();

            /// @brief Start the system and connect to the compute module
            void start();

            /// @brief Stop the system
            void stop();

            /// @brief Attempt to reconnect to the compute module if the connection is lost
            static void reconnectComputeModule();

            /// @brief Send the next destination to the compute module
            static void sendNextDestination();

        private:
            static math::Vector2 m_currentPosition;
            static std::deque<math::Vector3> m_destinations;
            static tcpcat::TcpClient m_client;
            static std::shared_ptr<tcpcat::EventHandler> m_eventHandler;

            static std::condition_variable m_cv;
            static std::mutex m_mutex;

            static bool finished;

            compute::EV3_compute_tcp m_compute;
            
    };
} // namespace finder::system

#endif // __EV3_SYSTEM_HPP__