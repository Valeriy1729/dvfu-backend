#ifndef SERVICE_LOGIC
#define SERVICE_LOGIC

#include "includes.h"
#include "customer.h"

#include "repositories/customersRepo.h"
#include "repositories/bankAccountsRepo.h"
#include "repositories/seatsRepo.h"


using ResponsePair = std::pair<std::string, http::status>;


struct ServiceLogic final {

	ServiceLogic() = default;

	ResponsePair updateCustomer(urls::params_view params, std::string_view body);
	ResponsePair getCustomer(urls::params_view params, std::string_view body);
	ResponsePair createCustomer(urls::params_view params, std::string_view body);
	ResponsePair deleteCustomer(urls::params_view params, std::string_view body);
	ResponsePair reserveSeat(urls::params_view params, std::string_view body);
	ResponsePair getAvaliableSeats();

	ResponsePair processRequest(
		const std::string_view target, const std::string_view body,
		const http::verb method)
	{
		const auto parsedData = urls::parse_origin_form(target);	
		urls::url_view dataView = *parsedData;
		ResponsePair result;

		if(dataView.path() == "/customers") {

			if(method == http::verb::patch) result = updateCustomer(dataView.params(), body);
			else if(method == http::verb::get) result = getCustomer(dataView.params(), body);
			else if(method == http::verb::post) result = createCustomer(dataView.params(), body);
			else if(method == http::verb::delete_) result = deleteCustomer(dataView.params(), body);
			else result = {"Unknown method for customers", http::status::not_found};

		} else if(dataView.path() == "/seats/reserve" && method == http::verb::post) {
			result = reserveSeat(dataView.params(), body);
		} else if(dataView.path() == "/seats/avaliable" && method == http::verb::get) {
			result = getAvaliableSeats();
		} else {
			result = {"Unknown target", http::status::not_found};
		}

		return result;
	}	
};


#endif  // SERVICE_LOGIC
