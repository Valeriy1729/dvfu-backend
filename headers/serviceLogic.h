#ifndef SERVICE_LOGIC
#define SERVICE_LOGIC

#include "includes.h"
#include "customer.h"


struct ServiceLogic final {

	ServiceLogic() = default;

	using ResponsePair = std::pair<std::string, http::status>;

	ResponsePair updateCustomer(urls::params_view params, std::string_view body);
	ResponsePair getCustomer(urls::params_view params, std::string_view body);
	ResponsePair createCustomer(urls::params_view params, std::string_view body);
	ResponsePair deleteCustomer(urls::params_view params, std::string_view body);
	ResponsePair buyTicket(urls::params_view params, std::string_view body);
	ResponsePair getAvaliableSeats();

	ResponsePair processRequest(
		const std::string_view target, const std::string_view body)
	{
		const auto parsedData = urls::parse_origin_form(target);	
		urls::url_view dataView = *parsedData;
		ResponsePair result;

		if(dataView.path() == "/updateCustomer") {
			result = updateCustomer(dataView.params(), body);
		} else if (dataView.path() == "/getCustomer") {
			result = getCustomer(dataView.params(), body);
		} else if(dataView.path() == "/createCustomer") {
			result = createCustomer(dataView.params(), body);
		} else if(dataView.path() == "/deleteCustomer") {
			result = deleteCustomer(dataView.params(), body);
		} else if(dataView.path() == "/buyTicket") {
			result = buyTicket(dataView.params(), body);
		} else if(dataView.path() == "/getAvaliableSeats") {
			result = getAvaliableSeats();
		} else {
			result = {"Unknown target", http::status::not_found};
		}

		return result;
	}	
};


#endif  // SERVICE_LOGIC
