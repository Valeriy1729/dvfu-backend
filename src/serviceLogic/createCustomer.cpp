#include "serviceLogic.hpp"

namespace service {

namespace logic {


ResponsePair createCustomer(const HttpRequest& request)
{ 
	std::string customerName;
	models::BankAccount newBankAccount;
	models::Customer newCustomer;

	const std::string ErrorPrefix = "Error when creating new customer: ";

	try {
		customerName = _getArgWithCheck<std::string>(
			request, "name", ErrorPrefix + "Parametr 'name' did not specified\n");

		newBankAccount = _getFromOptional<models::BankAccount>(
			[&customerName]{ return BankAccountsRepository::get().add(); },
			ErrorPrefix + "Could not create new bank account for new customer, try again\n");

		std::ignore = _getFromOptional<models::Customer>(
			[&customerName, &newBankAccount]{
				return CustomersRepository::get().add(customerName, newBankAccount.getId());
			}, ErrorPrefix + "Error when creating: Customer with this name already exists\n");

	} catch(_BadRequestException& ex) {
		return {ex.what(), HttpStatus::kBadRequest};	
	}

	return {"", HttpStatus::kCreated};	
}


}  // logic

}  // service
