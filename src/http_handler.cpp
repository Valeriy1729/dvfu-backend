#include "http_handler.hpp"

namespace service {


std::string HttpHandler::HandleRequest(
	userver::server::http::HttpRequest& request,
	userver::server::request::RequestContext&) const
{
	return "..."; // ... 
}


}  // service
