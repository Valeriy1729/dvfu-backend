#include <userver/utest/utest.hpp>
#include <userver/server/http/http_request_builder.hpp>

#include "_getArgWithCheck.hpp"
#include "_BadRequestException.hpp"

namespace logic = service::logic;
namespace http = userver::server::http;


UTEST(getArgWithCheck_string_Test, Basic) {

	auto request = http::HttpRequestBuilder()
		.AddRequestArg("name", "Customer")
		.Build();
	
	UEXPECT_NO_THROW( logic::_getArgWithCheck<std::string>(*request, "name", "ERROR: ") );
	EXPECT_EQ( logic::_getArgWithCheck<std::string>(*request, "name", "ERROR:"), "Customer" );
	UEXPECT_THROW_MSG(
		logic::_getArgWithCheck<std::string>(*request, "age", "ERROR: "),
		logic::_BadRequestException,
		"ERROR: Parametr 'age' did not specified\n"
	);
}

UTEST(getArgWithCheck_integral_Test, Basic) {

	auto request = http::HttpRequestBuilder()
		.AddRequestArg("name", "Richard")
		.AddRequestArg("number1", "10")
		.AddRequestArg("number2", "10.0")
		.Build();

	UEXPECT_NO_THROW( logic::_getArgWithCheck<int>(*request, "number1", "ERROR: ") );
	UEXPECT_NO_THROW( logic::_getArgWithCheck<long long>(*request, "number1", "ERROR: ") );

	EXPECT_EQ( logic::_getArgWithCheck<int>(*request, "number1", "ERROR: "), 10);
	EXPECT_EQ( logic::_getArgWithCheck<long long>(*request, "number1", "ERROR: "), 10);

	UEXPECT_THROW_MSG(
		logic::_getArgWithCheck<int>(*request, "name", "ERROR: "),
		logic::_BadRequestException,
		"ERROR: Parametr 'name' can not be converted to integral type\n"
	);
	UEXPECT_THROW_MSG(
		logic::_getArgWithCheck<int>(*request, "number2", "ERROR: "),
		logic::_BadRequestException,
		"ERROR: Parametr 'number2' can not be converted to integral type\n"
	);
	UEXPECT_THROW_MSG(
		logic::_getArgWithCheck<long long>(*request, "name", "ERROR: "),
		logic::_BadRequestException,
		"ERROR: Parametr 'name' can not be converted to integral type\n"
	);
	UEXPECT_THROW_MSG(
		logic::_getArgWithCheck<long long>(*request, "number2", "ERROR: "),
		logic::_BadRequestException,
		"ERROR: Parametr 'number2' can not be converted to integral type\n"
	);
}

