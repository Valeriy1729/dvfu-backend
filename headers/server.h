#ifndef SERVER_H
#define SERVER_H

#include "includes.h"
#include "settings.h"
#include "serviceLogic.h"


class HttpServer final {

	const std::string_view address_;	
	const unsigned short port_;
	asio::io_context context_;
	ServiceLogic serviceLogic_;

	http::response<http::string_body> processRequest_(const http::request<http::string_body>& request)
	{
		http::response<http::string_body> response (http::status::ok, request.version());
		response.set(http::field::server, httpConstants::SERVER_FIELD);
		response.set(http::field::content_type, httpConstants::CONTENT_TYPE_FIELD);
		auto [responseBody, responseResult] = serviceLogic_.processRequest(
			request.target(), request.body(), request.method());
		response.body() = responseBody, response.result(responseResult);
		return response;
	}

	asio::awaitable<void> handleRequest_(tcp::socket socket)
	{
		beast::flat_buffer buff;		
		http::request<http::string_body> request;
		co_await http::async_read(socket, buff, request, asio::use_awaitable);

		http::response<http::string_body> response;
		response = processRequest_(request);
		response.prepare_payload();
		buff.consume(buff.data().size());
		co_await http::async_write(socket, response, asio::use_awaitable);
	}

	asio::awaitable<void> listen_(tcp::endpoint endpoint)
	{
		auto executor = co_await asio::this_coro::executor;
		tcp::acceptor acceptor {executor, endpoint};
		while(true) {
			tcp::socket socket = co_await acceptor.async_accept(asio::use_awaitable);	
			asio::co_spawn(executor, handleRequest_(std::move(socket)), asio::detached);
		}
	}

public:
	HttpServer(std::string_view address, unsigned short port)
		: address_(address), port_(port), context_(), serviceLogic_() { }

	HttpServer(const HttpServer&) = delete;
	HttpServer& operator=(const HttpServer&) = delete;

	void startListening()
	{
		tcp::endpoint endpoint {asio::ip::make_address(address_), port_};
		asio::co_spawn(context_, listen_(endpoint), asio::detached);	
		context_.run();
	}
};


#endif  // SERVER_H
