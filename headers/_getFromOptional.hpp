#ifndef GET_FROM_OPTIONAL_H
#define GET_FROM_OPTIONAL_H

#include <string>
#include "_BadRequestException.hpp"

namespace service {

namespace logic {


template <typename T>
T _getFromOptional(std::optional<T> optional, const std::string& errorMsg)
{
	if(!optional.has_value())
		throw _BadRequestException(errorMsg);
	return optional.value();
}


}  // logic

}  // service

#endif  // GET_FROM_OPTIONAL_H
