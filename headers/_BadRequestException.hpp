#ifndef BAD_REQUEST_EXCEPTION_H
#define BAD_REQUEST_EXCEPTION_H

#include <string>
#include <exception>

namespace service {

namespace logic {


class _BadRequestException : std::exception {
	std::string message_;
public:
	_BadRequestException(const std::string& message)
	: message_(message) { }
	const char* what() { return message_.c_str(); }
};


}  // logic

}  // service

#endif  // BAD_REQUEST_EXCEPTION_H

