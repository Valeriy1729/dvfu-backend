#include "httpHandler.hpp"

namespace service {


std::string HttpHandler::HandleRequest(
	userver::server::http::HttpRequest& request,
	userver::server::request::RequestContext&) const
{
	std::pair<std::string, logic::HttpStatus> result = logic::_processRequest(request);
	request.GetHttpResponse().SetContentType(userver::http::content_type::kTextPlain);
	request.GetHttpResponse().SetStatus(result.second);
	return result.first;
}


}  // service
