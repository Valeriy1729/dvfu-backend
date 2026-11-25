#include "serviceLogic.hpp"

namespace service {

namespace logic {


ResponsePair getCustomer(const HttpRequest& request)
{
	std::string customerName;
	models::Customer customer;
	const std::string errorPrefix = "Error when getting customer: ";

	try {
		customerName = _getArgWithCheck<std::string>(request, "name", errorPrefix);
		
		customer = _getFromOptional(
			CustomersRepository::get().findByName(customerName),
			errorPrefix + "No such customer with name '" + customerName + "'\n");

	} catch(_BadRequestException& ex) {
		return {ex.what(), HttpStatus::kBadRequest};	
	}

	json::ValueBuilder builder(customer);
	json::Value jsonValue = builder.ExtractValue();
	return {json::ToString(jsonValue), HttpStatus::kOk};	
}


}  // logic

}  // service

