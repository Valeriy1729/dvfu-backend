#include "httpHandler.hpp"

namespace service {


std::string HttpHandler::HandleRequest(
	userver::server::http::HttpRequest& request,
	userver::server::request::RequestContext&) const
{
	std::pair<std::string, logic::HttpStatus> result;
       	try {
		result = logic::_processRequest(request);
	} catch(userver::server::handlers::CustomHandlerException& ex) {
		throw;	// status sets by Userver
	} catch(std::exception& ex) {
		throw server::handlers::InternalServerError(
			server::handlers::InternalMessage("Internal server error")
		);
	}
	request.GetHttpResponse().SetStatus(result.second);
	return result.first;
}


}  // service
