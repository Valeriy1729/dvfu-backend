#include "serviceLogic.hpp"

namespace service {

namespace logic {


ResponsePair deleteCustomer(const HttpRequest& request)
{
	std::string customerName;
	models::Customer customer;
	const std::string errorPrefix = "Error when deleting: ";

	try {
		customerName = _getArgWithCheck<std::string>(request, "name", errorPrefix);

		customer = _getFromOptional(CustomersRepository::get().findByName(customerName),
			errorPrefix + "No such customer with name '" + customerName + "'\n");

		_executeWithCheck([&customerName] -> bool {
			return CustomersRepository::get().deleteByName(customerName) > 0;				
		}, errorPrefix + "Couldn't delete customer");

	} catch(_BadRequestException& ex) {
		return {ex.what(), HttpStatus::kBadRequest};		
	}

	return {"Customer '" + customerName + "' deleted\n", HttpStatus::kOk};	
}


}  // logic

}  // service
