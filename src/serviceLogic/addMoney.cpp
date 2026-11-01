#include "serviceLogic.h"


ResponsePair ServiceLogic::addMoney(urls::params_view params, std::string_view body)
{
	// getting customer name from url
	auto customerNameIt = params.find("name");
	if(customerNameIt == params.end())
		return {"Error when topping up: Parametr 'name' did not specified in url",
			http::status::bad_request};
	std::string customerName = std::string((*customerNameIt).value);

	// paring request body
	auto parsedBody = urls::parse_query(body);
	if(!parsedBody.has_value())
		return {"Error when topping up balance: couldn't parse request body",
			http::status::bad_request};
	auto bodyParams = *parsedBody;

	// getting amount of money from the request body
	auto moneyAmountIt = bodyParams.find("amount");
	if(moneyAmountIt == bodyParams.end())
		return {"Error when topping up balance: Parametr 'amount' did not specified in request body",
			http::status::bad_request};
	long long moneyAmount = std::stoll(std::string((*moneyAmountIt).value));

	// finding customer by customerName
	std::optional<Customer> customer = CustomersRepository::get().findByName(customerName);
	if(!customer.has_value())
		return {"Error when topping up balance: No such customer with name: '" + customerName + "'",
			http::status::bad_request};

	// topping up balance
	bool wasAddedMoney = BankAccountsRepository::get().addMoney(
		customer.value().getBankAccountId(), moneyAmount);
	if(!wasAddedMoney)
	       return {"Error when topping up balance: No bank account for such customer with name: '" +
		       customerName + "' OR 'amount' < 0", http::status::bad_request};	


	return {"", http::status::no_content};
}

