#ifndef INCLUDES_H
#define INCLUDES_H


#include <iostream>

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/io_context.hpp>

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace http = beast::http;

using tcp = asio::ip::tcp;


#endif  // INCLUDES_H
