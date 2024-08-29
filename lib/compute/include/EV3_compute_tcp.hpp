#include <EV3_tcp_communication_server.hpp>
#include <Vector2.hpp>
#include <pf/AStar.hpp>
#include <pf/SmoothPath.hpp>
#include "../../EV3_conf.hpp"
#include <memory>
#include <future>
#include <atomic>
#include <string>
#include <vector>
#include <thread>
#include "../../EV3_conf.hpp"

#ifdef EV3_COMPUTE_NO_TCP
    //#error "COMPUTE_NO_TCP set, this file should not be imported!"
#endif

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
        std::string extract_coordinates(const std::string &message);
    };
} // namespace finder::compute