#if !defined(_MSC_VER)


#ifndef __WEBSERVER_H__
#define __WEBSERVER_H__

#include <server/webServer/http_server/http_server.h>
#include <server/webServer/http_server/http_message.h>
#include <server/webServer/http_server/uri.h>
#include <server/webServer/webComponents/ComponentFullBody.hpp>

namespace finder::server
{
    /// @brief Class that represents the web server
    class WebServer
    {
        public:
            WebServer();
            virtual ~WebServer() = default;

            /// @brief Start the server
            static void start();

            /// @brief Stop the server
            static void stop();

        protected:
            /// @brief Component that represents the HTTP server
            static std::shared_ptr<simple_http_server::HttpServer> server;

            /// @brief Component that represents the full body of the HTML page
            static std::shared_ptr<webComponents::ComponentFullBody> fullBody;

            /// @brief Hostname of the server
            static std::string _hostname;

            /// @brief Port of the server
            static int _port;

        private:
            /// @brief Register the request handlers for the server
            static void setupRoutes();
    };
} // namespace finder::server

#endif // __WEBSERVER_H__

#endif // !defined(_MSC_VER)