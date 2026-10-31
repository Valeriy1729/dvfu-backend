#ifndef INCLUDES_H
#define INCLUDES_H


#include <iostream>
#include <array>
#include <vector>

#include <boost/json.hpp>

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>

#include <boost/url/url_view.hpp>
#include <boost/url/parse.hpp>

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/io_context.hpp>

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace http = beast::http;
namespace json = boost::json;
namespace urls = boost::urls;

using tcp = asio::ip::tcp;


#endif  // INCLUDES_H
