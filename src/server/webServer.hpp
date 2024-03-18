#include <server/http_server/http_server.h>
#include <server/http_server/http_message.h>
#include <server/http_server/uri.h>
#include <server/webComponents/ComponentFullBody.hpp>

namespace finder::server
{
    class WebServer
    {
        public:
            WebServer();
            virtual ~WebServer() = default;

            void start();
            void stop();

        private:
            std::shared_ptr<simple_http_server::HttpServer> server;
            std::shared_ptr<webComponents::ComponentFullBody> fullBody;

            void setupRoutes();
    };
} // namespace finder::server
