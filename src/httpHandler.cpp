#include "httpHandler.hpp"

namespace service {


std::string HttpHandler::HandleRequest(
	userver::server::http::HttpRequest& request,
	userver::server::request::RequestContext&) const
{
	std::pair<std::string, logic::HttpStatus> result;
       	try {
		result = logic::_processRequest(request);
	} catch(std::exception& ex) {
		request.GetHttpResponse().SetStatus(
			userver::server::http::HttpStatus::kBadRequest);
		return ex.what();
	}
	request.GetHttpResponse().SetStatus(result.second);
	return result.first;
}


}  // service
