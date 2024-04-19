#ifndef __WEBSERVER_H__
#define __WEBSERVER_H__

#include <server/webServer/http_server/http_server.h>
#include <server/webServer/http_server/http_message.h>
#include <server/webServer/http_server/uri.h>
#include <server/webServer/webComponents/ComponentFullBody.hpp>

namespace finder::server
{

    class WebServer
    {
        public:
            WebServer();
            virtual ~WebServer() = default;

            static void start();
            static void stop();

        protected:
            static std::shared_ptr<simple_http_server::HttpServer> server;
            static std::shared_ptr<webComponents::ComponentFullBody> fullBody;

            static std::string _hostname;
            static int _port;

        private:
            static void setupRoutes();
    };
} // namespace finder::server

#endif // __WEBSERVER_H__