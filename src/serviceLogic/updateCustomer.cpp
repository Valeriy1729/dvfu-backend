#include "serviceLogic.h"


ResponsePair ServiceLogic::updateCustomer(urls::params_view params, std::string_view body)
{
	// getting old customer name from url
	auto customerNameIt = params.find("name");
	if(customerNameIt == params.end())
		return {"Error when updating customer: Parametr 'name' did not specified in url",
			http::status::bad_request};
	std::string customerName = std::string((*customerNameIt).value);

	// getting new customer name from body
	auto parsedBody = urls::parse_query(body);
	if(!parsedBody.has_value())
		return {"Error when updating customer: couldn't parse request body",
			http::status::bad_request};
	auto bodyParams = *parsedBody;
	auto newCustomerNameIt = bodyParams.find("newName");
	if(newCustomerNameIt == bodyParams.end())
		return {"Error when updating customer: Parametr 'newName' did not specified in request body",
			http::status::bad_request};
	std::string newCustomerName = std::string((*newCustomerNameIt).value);

	// checking the existing of customer
	if(!CustomersRepository::get().findByName(customerName).has_value())
		return {"Error when updating customer: No customer with such name: '" + customerName + "'",
			http::status::bad_request};

	CustomersRepository::get().updateCustomerName(customerName, newCustomerName);
	return {"", http::status::no_content};
}
