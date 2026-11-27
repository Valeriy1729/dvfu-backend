#include <userver/utest/utest.hpp>

#include "_getFromOptional.hpp"
#include "_BadRequestException.hpp"

namespace logic = service::logic;


UTEST(getFromOptional_Test, Basic) {

	std::optional<int> optionalFull(10);	
	std::optional<int> optionalEmpty(std::nullopt);	

	UEXPECT_NO_THROW( logic::_getFromOptional(optionalFull, "Error ocurred\n") );
	EXPECT_EQ( logic::_getFromOptional(optionalFull, "Error ocurred\n"), 10 );
	UEXPECT_THROW_MSG(
		logic::_getFromOptional(optionalEmpty, "Error ocurred\n"),
		logic::_BadRequestException,
		"Error ocurred\n"
	);
}
