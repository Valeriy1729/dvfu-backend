#include <userver/utest/utest.hpp>
#include <userver/server/http/http_request_builder.hpp>
#include <userver/http/common_headers.hpp>

#include "serviceLogic.hpp"

UTEST(createCustomer_test1, Basic) {
	const auto request = userver::server::http::HttpRequestBuilder()
		.SetMethod(userver::server::http::HttpMethod::kPost)
		.SetUrl("/cinema-service/customers")
		.AddRequestArg("name", "User")
		.Build();

	EXPECT_EQ(service::logic::createCustomer(*request),
		(std::pair<std::string, userver::server::http::HttpStatus>(
			"Customer 'User' created\n", userver::server::http::HttpStatus::kCreated
		))
	);
}

