#if !defined(_MSC_VER)

#include "../../EV3_conf.hpp"


#include "webServer.hpp"

namespace finder::server
{
    std::shared_ptr<simple_http_server::HttpServer> WebServer::server;
    std::shared_ptr<webComponents::ComponentFullBody> WebServer::fullBody;
    std::string WebServer::_hostname;
    int WebServer::_port;

    WebServer::WebServer()
    {
        _hostname = EV3_WEBSERVER_HOST;
        _port = EV3_WEBSERVER_PORT;
        server = std::make_shared<simple_http_server::HttpServer>(_hostname, _port);
        fullBody = std::make_shared<webComponents::ComponentFullBody>();
    }

    void WebServer::start()
    {
        try
        {
            setupRoutes();
            server->Start();
        }
        catch(const std::exception& e)
        {
            spdlog::error(e.what());
        }
        
    }

    void WebServer::stop()
    {
        try
        {
            server->Stop();
        }
        catch(const std::exception& e)
        {
            spdlog::error(e.what());
        }
        
    }

    void WebServer::setupRoutes()
    {
        using namespace simple_http_server;

        auto say_hello = [](const HttpRequest &request) {
            HttpResponse response(HttpStatusCode::Ok);
            response.SetHeader("Content-Type", "text/plain");
            response.SetContent("Hello, World!");
            return response;
        };

        auto mainPage = [](const HttpRequest &request) {
            HttpResponse response(HttpStatusCode::Ok);
            response.SetHeader("Content-Type", "text/html");
            response.SetContent(fullBody->render());
            return response;
        };

        auto testPage = [](const HttpRequest &request) {
            HttpResponse response(HttpStatusCode::Ok);
            response.SetHeader("Content-Type", "text/html");
            response.SetContent("");
            return response;
        };
        
        server->RegisterHttpRequestHandler("/hello", HttpMethod::HEAD, say_hello);
        server->RegisterHttpRequestHandler("/hello", HttpMethod::GET, say_hello);
        server->RegisterHttpRequestHandler("/", HttpMethod::HEAD, mainPage);
        server->RegisterHttpRequestHandler("/", HttpMethod::GET, mainPage);
    }
} // namespace finder::server

#endif // !_MSC_VER