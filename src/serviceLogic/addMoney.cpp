#include "serviceLogic.hpp"

namespace service {

namespace logic {


ResponsePair addMoney(const HttpRequest& request)
{
	long long moneyAmount;
	std::string customerName;
	models::Customer customer;

	const std::string ErrorPrefix = "Error when topping up balance: ";

	try {
		customerName = _getArgWithCheck<std::string>(
			request, "name", ErrorPrefix + "argument 'name' did not specified\n");
		moneyAmount = _getArgWithCheck<long long>(
			request, "amount", ErrorPrefix + "argument 'amount' did not specified\n");

		customer = _getFromOptional<models::Customer>(
			[&customerName]{ return CustomersRepository::get().findByName(customerName); },
			ErrorPrefix + "No such customer with name: '" + customerName + "'\n"
		);

		_executeWithCheck([&customer, moneyAmount] {
			return BankAccountsRepository::get().addMoney(
				customer.getBankAccountId(), moneyAmount);
			},
			ErrorPrefix + "No bank account for such customer with name: '" +
			customerName + "' OR 'amount' < 0\n"
		);	

	} catch(_BadRequestException& exception) {
		return {exception.what(), HttpStatus::kBadRequest};	
	}

	return {"Balance topped sucessfully\n", HttpStatus::kNoContent};
}


}  // logic

}  // service
