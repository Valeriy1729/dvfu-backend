#ifndef GET_ARGUMENT_WITH_CHECK
#define GET_ARGUMENT_WITH_CHECK

#include <userver/server/http/http_request.hpp>
#include <userver/server/handlers/exceptions.hpp>
#include <userver/utils/from_string.hpp>

namespace service {

namespace logic {


using userver::server::http::HttpRequest;

template <typename T>
T _getArgWithCheck(const HttpRequest&, const std::string&, const std::string&) = delete;

template <> inline std::string _getArgWithCheck(
	const HttpRequest& request, const std::string& argName, const std::string& errorMsg)
{
	std::string argumentStr = request.GetArg(argName);		
	if(argumentStr.empty())
		throw _BadRequestException(errorMsg);
	return argumentStr;
}

template <> inline long long _getArgWithCheck(
	const HttpRequest& request, const std::string& argName, const std::string& errorMsg)
{
	long long argumentLL;
	std::string argument = request.GetArg(argName);		

	if(argument.empty())
		throw _BadRequestException(errorMsg);

	try { argumentLL = userver::utils::FromString<long long>(argument); }
	catch(const userver::utils::FromStringException& exception) {
		throw _BadRequestException(errorMsg);
	}

	return argumentLL;
}


}  // logic

}  // service

#endif  // GET_ARGUMENT_WITH_CHECK
