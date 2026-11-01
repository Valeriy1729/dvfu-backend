#include "serviceLogic.h"


ResponsePair ServiceLogic::createCustomer(urls::params_view params, std::string_view body)
{
	auto parsedBody = urls::parse_query(body);
	if(!parsedBody.has_value())
		return {"Error when creating customer: couldn't parse request body",
			http::status::bad_request};
	auto bodyParams = *parsedBody;

	// getting customer name from request body
	auto customerNameIt = bodyParams.find("name");
	if(customerNameIt == bodyParams.end())
		return {"Error when creating: Parametr 'name' did not specified in request body",
			http::status::bad_request};
	std::string customerName = std::string((*customerNameIt).value);

	// creating new bank account
	std::optional<BankAccount> newBankAccount = BankAccountsRepository::get().add();
	if(!newBankAccount.has_value())
		return {"Error when creating: Could not create new bank account for new customer, try again",
			http::status::bad_request};

	// creating new customer
	std::optional<Customer> newCustomer = CustomersRepository::get().add(
			customerName, newBankAccount.value().getId());
	if(!newCustomer.has_value()) {
		std::ignore = BankAccountsRepository::get().delete_(newBankAccount.value().getId());
		return {"Error when creating: Customer with this name already exists",
			http::status::bad_request};
	}

	return {"", http::status::created};
}
