#include <EV3_tcp_communication_server.hpp>
#include <Vector2.hpp>
#include <pf/AStar.hpp>
#include <pf/SmoothPath.hpp>
#include <memory>
#include <future>
#include <atomic>
#include <string>
#include <vector>
#include <thread>

namespace finder::compute
{
    class EV3_compute
    {
    public:
        EV3_compute();
        ~EV3_compute();

        void start();
        void stop();

    private:
        std::unique_ptr<::finder::network::tcp::TCPServer> m_tcp_communication_server;
        std::atomic_bool m_running = true;
        std::thread m_client_thread;

        // pathfinder stuff
        ::finder::pathfind::AStar::Generator m_pathfinder;
        ::finder::pathfind::SmoothPath m_smooth_path;

        void handle_client();
        std::string parse_message(const std::string &message);
    };
} // namespace finder::compute