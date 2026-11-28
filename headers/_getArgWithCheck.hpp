#ifndef GET_ARGUMENT_WITH_CHECK
#define GET_ARGUMENT_WITH_CHECK

#include <userver/server/http/http_request.hpp>
#include <userver/server/handlers/exceptions.hpp>
#include <userver/utils/from_string.hpp>

#include "_BadRequestException.hpp"

namespace service {

namespace logic {


using userver::server::http::HttpRequest;

template <typename T>
T _getArgWithCheck(const HttpRequest&, const std::string&, const std::string&) = delete;

template <> inline std::string _getArgWithCheck(
	const HttpRequest& request, const std::string& argName, const std::string& errorPrefix)
{
	std::string argumentStr = request.GetArg(argName);		
	if(argumentStr.empty())
		throw _BadRequestException(
			errorPrefix + "Parametr '" + argName + "' did not specified\n");
	return argumentStr;
}

template <std::integral T> inline T _getArgWithCheck(
	const HttpRequest& request, const std::string& argName, const std::string& errorPrefix)
{
	T argumentIntegral {};
	std::string argument = request.GetArg(argName);		
	if(argument.empty())
		throw _BadRequestException(
			errorPrefix + "Parametr '" + argName + "' did not specified\n");
	try { argumentIntegral = userver::utils::FromString<long long>(argument); }
	catch(const userver::utils::FromStringException& exception) {
		throw _BadRequestException(
			errorPrefix + "Parametr '" + argName + "' can not be converted to integral type\n");
	}
	return argumentIntegral;
}


}  // logic

}  // service

#endif  // GET_ARGUMENT_WITH_CHECK
