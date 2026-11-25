#include "serviceLogic.hpp"

namespace service {

namespace logic {


ResponsePair getBalance(const HttpRequest& request)
{
	long long moneyAmount;
	std::string customerName;
	models::Customer customer;
	const std::string errorPrefix = "Error whten getting balance: ";

	try {
		customerName = _getArgWithCheck<std::string>(request, "name", errorPrefix);
		
		customer = _getFromOptional(
			CustomersRepository::get().findByName(customerName),
			errorPrefix + "No such customer with name '" + customerName + "'\n");
	
		moneyAmount = _getFromOptional(
			BankAccountsRepository::get().getMoneyAmountById(customer.getBankAccountId()),
			errorPrefix + "No bank account for customer with name '" + customerName + "'\n");

	} catch(_BadRequestException& ex) {
		return {ex.what(), HttpStatus::kBadRequest};	
	}

	json::ValueBuilder builder (formats::common::Type::kObject);
	builder["name"] = customerName, builder["balance"] = moneyAmount;
	json::Value jsonValue = builder.ExtractValue();
	return {json::ToString(jsonValue), HttpStatus::kOk};	
}


}  // logic

}  // service

