#include <userver/utest/utest.hpp>

#include "_executeWithCheck.hpp"
#include "_BadRequestException.hpp"

namespace logic = service::logic;


UTEST(executeWithCheck_Test, Basic) {

	const std::string errorMessage = "message";
	const auto lambdaFalse = [] -> bool { return false; };
	const auto lambdaTrue = [] -> bool { return true; };

	UEXPECT_THROW_MSG(
		logic::_executeWithCheck(lambdaFalse, errorMessage),
		logic::_BadRequestException,
		errorMessage
	);

	UEXPECT_NO_THROW(
		logic::_executeWithCheck(lambdaTrue, errorMessage)
	);
}


