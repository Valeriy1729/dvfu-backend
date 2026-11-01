#include "serviceLogic.h"


ResponsePair ServiceLogic::getCustomer(urls::params_view params, std::string_view body)
{
	// getting customer name from url
	auto customerNameIt = params.find("name");
	if(customerNameIt == params.end())
		return {"Error when finding: Parametr 'name' did not specified in url",
			http::status::bad_request};
	std::string customerName = std::string((*customerNameIt).value);

	// finding customer with given name
	std::optional<Customer> customer = CustomersRepository::get().findByName(customerName);
	if(!customer.has_value())
		return {"Error when finding: No customer with such name: '" + customerName + "'",
			http::status::bad_request};

	json::value customerJsonValue = json::value_from(customer);
	return {json::serialize(customerJsonValue), http::status::ok};
}
