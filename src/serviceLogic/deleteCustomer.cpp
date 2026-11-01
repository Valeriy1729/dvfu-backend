#include "serviceLogic.h"


ResponsePair ServiceLogic::deleteCustomer(urls::params_view params, std::string_view body)
{
	// getting customer name from url
	auto customerNameIt = params.find("name");
	if(customerNameIt == params.end())
		return {"Error when deleting: Parametr 'name' did not specified in url",
			http::status::bad_request};
	std::string customerName = std::string((*customerNameIt).value);

	// deleting customer with given name
	size_t deletedCount = CustomersRepository::get().deleteByName(customerName);
	if(deletedCount != 1)
		return {"Error when deleting: No such customer with name: '" + customerName + "'",
			http::status::bad_request};

	return {"", http::status::no_content};
}
