#include "serviceLogic.hpp"

namespace service {

namespace logic {


ResponsePair _processRequest(const HttpRequest& request)
{
	HttpMethod method = request.GetMethod();
	std::string suffix = request.GetPathArg("suffix");
	ResponsePair result;

	switch(method) {
		case HttpMethod::kGet:
			if(suffix == "customers") result = getCustomer(request);
			else if(suffix == "balance") result = getBalance(request);
			else if(suffix == "seats") result = getAvaliableSeats(request);
			else _throwResourceNotFound("Unknown suffix for method GET");
			break;
		case HttpMethod::kPost:
			if(suffix == "customers") result = createCustomer(request);
			else _throwResourceNotFound("Unknown suffix for method POST");
			break;
		case HttpMethod::kDelete:
			if(suffix == "customers") result = deleteCustomer(request);
			else _throwResourceNotFound("Unknown suffix for method DELETE");
			break;
		case HttpMethod::kPatch:
			if(suffix == "customers") result = updateCustomer(request);
			else if(suffix == "balance") result = addMoney(request);
			else if(suffix == "reserve") result = reserveSeat(request);
			else _throwResourceNotFound("Unknown suffix for method PATCH");
			break;
		default:
			_throwResourceNotFound("Unknown method");
	}

	return result;
}	


}  // logic

}  // service
