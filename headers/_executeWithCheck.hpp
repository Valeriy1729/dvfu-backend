#ifndef EXECUTE_WITH_CHECK
#define EXECUTE_WITH_CHECK

#include <string>
#include "_BadRequestException.hpp"

namespace service {

namespace logic {


template <typename F>
concept _BoolLambda = requires (F getLambda) {
	{ getLambda() } -> std::convertible_to<bool>; 		
};

template <_BoolLambda F>
void _executeWithCheck(F&& lambda, const std::string& errorMsg) {
	bool wasSuccess = lambda();
	if(!wasSuccess) throw _BadRequestException(errorMsg);
}


}  // logic

}  // service

#endif  // EXECUTE_WITH_CHECK
