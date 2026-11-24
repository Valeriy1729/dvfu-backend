#ifndef GET_FROM_OPTIONAL_H
#define GET_FROM_OPTIONAL_H

#include <string>
#include "_BadRequestException.hpp"

namespace service {

namespace logic {


template <typename F, typename T>
concept _OptionalLambda = requires (F getLambda) {
	{ getLambda() } -> std::convertible_to<std::optional<T>>; 		
};

template <typename T, _OptionalLambda<T> F>
T _getFromOptional(F&& getLambda, const std::string& errorMsg) {
	std::optional<T> result = getLambda();
	if(!result.has_value())
		throw _BadRequestException(errorMsg);
	return result.value();
}


}  // logic

}  // service

#endif  // GET_FROM_OPTIONAL_H
