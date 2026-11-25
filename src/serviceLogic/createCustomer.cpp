#include "serviceLogic.hpp"

namespace service {

namespace logic {


ResponsePair createCustomer(const HttpRequest& request)
{ 
	std::string customerName;
	models::BankAccount newBankAccount;
	models::Customer newCustomer;

	const std::string errorPrefix = "Error when creating new customer: ";

	try {
		customerName = _getArgWithCheck<std::string>(request, "name", errorPrefix);

		newBankAccount = _getFromOptional<models::BankAccount>(
			BankAccountsRepository::get().add(),
			errorPrefix + "Could not create new bank account for new customer, try again\n");

		newCustomer = _getFromOptional<models::Customer>(
			CustomersRepository::get().add(customerName, newBankAccount.getId()),
			errorPrefix + "Customer with this name already exists\n");

	} catch(_BadRequestException& ex) {
		return {ex.what(), HttpStatus::kBadRequest};	
	}

	return {"Customer '" + customerName + "' created\n", HttpStatus::kCreated};	
}


}  // logic

}  // service
