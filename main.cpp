#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <iostream>
#include <nlohmann/json.hpp>

#include "generated/index_html.h"
#include "generated/jquery.h"
#include "generated/script_js.h"
#include "generated/style_css.h"
#include "generated/favicon.h"


using tcp = boost::asio::ip::tcp;
namespace http = boost::beast::http;

using namespace std;
using json = nlohmann::json;

void processIndexHtml(http::request<http::string_body>& request, tcp::socket& socket) {
    // Prepare the response message
    http::response<http::string_body> response;
    response.version(request.version());
    response.result(http::status::ok);
    response.set(http::field::content_type, "text/html");
    response.body() = indexHtml;
    response.prepare_payload();

    // Send the response to the client
    boost::beast::http::write(socket, response);
}

void processStyleCss(http::request<http::string_body>& request, tcp::socket& socket) {
    // Prepare the response message
    http::response<http::string_body> response;
    response.version(request.version());
    response.result(http::status::ok);
    response.set(http::field::content_type, "text/css");
    response.body() = styleCss;
    response.prepare_payload();

    // Send the response to the client
    boost::beast::http::write(socket, response);
}

void processScriptJs(http::request<http::string_body>& request, tcp::socket& socket) {
    // Prepare the response message
    http::response<http::string_body> response;
    response.version(request.version());
    response.result(http::status::ok);
    response.set(http::field::content_type, "text/javascript");
    response.body() = scriptJs;
    response.prepare_payload();

    // Send the response to the client
    boost::beast::http::write(socket, response);
}

void processJQuery(http::request<http::string_body>& request, tcp::socket& socket) {
    // Prepare the response message
    http::response<http::string_body> response;
    response.version(request.version());
    response.result(http::status::ok);
    response.set(http::field::content_type, "text/javascript");
    response.body() = jqueryJs;
    response.prepare_payload();

    // Send the response to the client
    boost::beast::http::write(socket, response);
}

void processFavicon(http::request<http::string_body>& request, tcp::socket& socket) {
    // Prepare the response message
    http::response<http::string_body> response;
    response.version(request.version());
    response.result(http::status::ok);
    response.set(http::field::content_type, "image/ico");
    response.body() = favicon;
    response.prepare_payload();

    // Send the response to the client
    boost::beast::http::write(socket, response);
}

void processApiGet(http::request<http::string_body>& request, tcp::socket& socket) {
    json output;
    output["pi"] = 3.141;
    output["happy"] = true;
    output["name"] = "Landru";
    output["nothing"] = nullptr;
    output["answer"]["everything"] = 42;
    output["list"] = {1, 0, 2};
    output["object"] = {{"currency", "USD"}, {"value", 42.99}};

    // Prepare the response message
    http::response<http::string_body> response;
    response.version(request.version());
    response.result(http::status::ok);
    response.set(http::field::content_type, "application/json");
    response.body() = output.dump();
    response.prepare_payload();

    // Send the response to the client
    boost::beast::http::write(socket, response);
}

void processApiPost(http::request<http::string_body>& request, tcp::socket& socket) {
    auto json_request = json::parse(request.body());

    json output = {{"message", json_request["message"]}};

    output["status"] = "ok";

    // Prepare the response message
    http::response<http::string_body> response;
    response.version(request.version());
    response.result(http::status::ok);
    response.set(http::field::content_type, "application/json");
    response.body() = output.dump();
    response.prepare_payload();

    // Send the response to the client
    boost::beast::http::write(socket, response);
}

void process404(http::request<http::string_body>& request, tcp::socket& socket) {
    // Prepare the response message
    http::response<http::string_body> response;
    response.version(request.version());
    response.result(http::status::not_found);
    response.set(http::field::content_type, "text/plain");
    response.body() = "not found";
    response.prepare_payload();

    // Send the response to the client
    boost::beast::http::write(socket, response);
}



void handleRequest(http::request<http::string_body>& request, tcp::socket& socket) {
    //printf("Route: [%s] %s\n", request.method(), request.target());

    if (request.method() == http::verb::get && request.target() == "/") {
        processIndexHtml(request, socket);

        return ;
    }

    if (request.method() == http::verb::get && request.target() == "/style.css") {
        processStyleCss(request, socket);

        return ;
    }

    if (request.method() == http::verb::get && request.target() == "/script.js") {
        processScriptJs(request, socket);

        return ;
    }

    if (request.method() == http::verb::get && request.target() == "/jquery.js") {
        processJQuery(request, socket);

        return ;
    }

    if (request.method() == http::verb::get && request.target() == "/favicon.ico") {
        processFavicon(request, socket);

        return ;
    }

    if (request.method() == http::verb::get && request.target() == "/read") {
        processApiGet(request, socket);

        return ;
    }

    if (request.method() == http::verb::post && request.target() == "/write") {
        processApiPost(request, socket);

        return ;
    }
    
    process404(request, socket);
}

void runServer() {
    boost::asio::io_context io_context;
    tcp::acceptor acceptor(io_context, {tcp::v4(), 8080});

    while (true) {
        tcp::socket socket(io_context);
        acceptor.accept(socket);

        // Read the HTTP request
        boost::beast::flat_buffer buffer;
        http::request<http::string_body> request;
        boost::beast::http::read(socket, buffer, request);

        // Handle the request
        handleRequest(request, socket);

        // Close the socket
        socket.shutdown(tcp::socket::shutdown_send);
    }
}

int main() {
    printf("Browse http://localhost:8080");

    try {
        runServer();
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}