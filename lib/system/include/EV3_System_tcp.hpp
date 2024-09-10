#ifndef __EV3_SYSTEM_HPP__
#define __EV3_SYSTEM_HPP__

#include <Logger.hpp>
#include <Vector3.hpp>
#include <ConfigReader.hpp>
#include <EV3_compute_tcp.hpp>
#include <vector>
#include <deque>
#include <memory>
#include <condition_variable>

#include <tcpcat/tcpcat.h>
namespace finder::system
{
    class ComputeModuleEventHandler : public tcpcat::EventHandler
    {
        public:
            void OnConnected(std::shared_ptr<tcpcat::TcpSession> session) override;
            void OnReceived(std::shared_ptr<tcpcat::TcpSession> session, const std::vector<unsigned char> &buf, size_t bytes) override;
            void OnError(std::shared_ptr<tcpcat::TcpSession> session, const asio::error_code &err) override;
            void OnDisconnected(std::shared_ptr<tcpcat::TcpSession> session) override;
            void OnSent(std::shared_ptr<tcpcat::TcpSession> session, const std::vector<unsigned char> &buf, size_t bytes) override;

        private:
            bool m_ready = false;
            bool _reconnecting = false;
    };
    class SystemTcp
    {
        public:
            SystemTcp();
            ~SystemTcp();

            void start();
            void stop();

            static void reconnectComputeModule();
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