#ifndef HTTP_HANDLER_H
#define HTTP_HANDLER_H

#include <userver/server/handlers/http_handler_base.hpp>

namespace service {


class HttpHandler final : public userver::server::handlers::HttpHandlerBase {
public:
	using HttpHandlerBase::HttpHandlerBase;
	static constexpr std::string_view kName = "http-handler";
	std::string HandleRequest(
		userver::server::http::HttpRequest& request,
		userver::server::request::RequestContext&) const override;
};


} // service

#endif  // HTTP_HANDLER_H

