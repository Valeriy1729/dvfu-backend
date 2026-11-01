#include "serviceLogic.h"


ResponsePair ServiceLogic::getBalance(urls::params_view params, std::string_view body)
{
	// getting customer name from url
	auto customerNameIt = params.find("name");
	if(customerNameIt == params.end())
		return {"Error when getting balance: Parametr 'name' did not specified in url",
			http::status::bad_request};
	std::string customerName = std::string((*customerNameIt).value);

	// finding customer by customerName
	std::optional<Customer> customer = CustomersRepository::get().findByName(customerName);
	if(!customer.has_value())
		return {"Error when getting balance: No such customer with name: '" + customerName + "'",
			http::status::bad_request};
	
	// getting money amount by bank account id
	std::optional<long long> moneyAmount = BankAccountsRepository::get().getMoneyAmountById(
		customer.value().getBankAccountId());	
	if(!moneyAmount.has_value())
		return {"Error when getting balance: No bank account for customer with name: '" +
			customerName + "'", http::status::bad_request};

	json::object moneyAmountJsonObject = {
		{"balance", moneyAmount.value()}
	};

	return {json::serialize(moneyAmountJsonObject),
		http::status::ok};
}
