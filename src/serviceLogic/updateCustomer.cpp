#include "serviceLogic.hpp"

namespace service {

namespace logic {


ResponsePair updateCustomer(const HttpRequest& request)
{
	std::string customerName, newCustomerName;
	const std::string errorPrefix = "Error when updating customer: ";

	try {
		customerName = _getArgWithCheck<std::string>(request, "name", errorPrefix);	
		newCustomerName = _getArgWithCheck<std::string>(request, "new_name", errorPrefix);	

		_executeWithCheck(
			[&] -> bool {
				return CustomersRepository::get().updateCustomerName(
					customerName, newCustomerName);
			}, fmt::format(
				"{} No customer with name '{}' or customer with name '{}' already exists\n",
				errorPrefix, customerName, newCustomerName));

	} catch(_BadRequestException& ex) {
		return {ex.what(), HttpStatus::kBadRequest};	
	}

	return {"Customer '" + customerName + "' updated\n", HttpStatus::kOk};	
}


}  // logic

}  // service

