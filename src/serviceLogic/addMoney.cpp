#include "serviceLogic.hpp"

namespace service {

namespace logic {


ResponsePair addMoney(const HttpRequest& request)
{
	long long moneyAmount;
	std::string customerName;
	models::Customer customer;

	const std::string errorPrefix = "Error when topping up balance: ";

	try {
		customerName = _getArgWithCheck<std::string>(request, "name", errorPrefix);
		moneyAmount = _getArgWithCheck<long long>(request, "amount", errorPrefix);

		customer = _getFromOptional<models::Customer>(
			CustomersRepository::get().findByName(customerName),
			errorPrefix + "No such customer with name: '" + customerName + "'\n"
		);

		_executeWithCheck([&customer, moneyAmount] -> bool {
			return BankAccountsRepository::get().addMoney(
				customer.getBankAccountId(), moneyAmount);
			},
			errorPrefix + "No bank account for such customer with name: '" +
			customerName + "' OR 'amount' < 0\n"
		);	

	} catch(_BadRequestException& exception) {
		return {exception.what(), HttpStatus::kBadRequest};	
	}

	return {"Balance topped sucessfully\n", HttpStatus::kOk};
}


}  // logic

}  // service
