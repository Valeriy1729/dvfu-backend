#ifndef SERVICE_LOGIC
#define SERVICE_LOGIC

#include <string>
#include <fmt/format.h>

#include <userver/server/http/http_request.hpp>
#include <userver/server/http/http_response.hpp>
#include <userver/http/status_code.hpp>
#include <userver/server/handlers/exceptions.hpp>
#include <userver/utils/from_string.hpp>

#include <userver/engine/mutex.hpp>

#include "models/customer.hpp"

#include "_pairSerialization.hpp"
#include "_getFromOptional.hpp"
#include "_executeWithCheck.hpp"
#include "_getArgWithCheck.hpp"

#include "repositories/customersRepository.hpp"
#include "repositories/bankAccountsRepository.hpp"
#include "repositories/seatsRepository.hpp"

namespace service {

namespace logic {


using userver::server::http::HttpRequest;
using userver::server::http::HttpResponse;
using userver::server::http::HttpStatus;
using userver::server::http::HttpMethod;

using ResponsePair = std::pair<std::string, HttpStatus>;

namespace formats = userver::formats;
namespace json = formats::json;

void _throwResourceNotFound(const std::string&);
ResponsePair _processRequest(const HttpRequest&);

ResponsePair updateCustomer(const HttpRequest&);
ResponsePair getCustomer(const HttpRequest&);
ResponsePair createCustomer(const HttpRequest&);
ResponsePair deleteCustomer(const HttpRequest&);
ResponsePair addMoney(const HttpRequest&);
ResponsePair getBalance(const HttpRequest&);
ResponsePair reserveSeat(const HttpRequest&);
ResponsePair getAvaliableSeats(const HttpRequest&);


}  // logic

}  // service

#endif  // SERVICE_LOGIC

