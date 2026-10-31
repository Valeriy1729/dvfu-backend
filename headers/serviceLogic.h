#ifndef SERVICE_LOGIC
#define SERVICE_LOGIC

#include "includes.h"
#include "customer.h"


struct ServiceLogic {
public:
	ServiceLogic() { };

	template <typename T>
	using SitsArray = std::array<
		std::array<T, sitsConstants::ROWS_COUNT>,
		sitsConstants::COLUMNS_COUNT
	>;

	std::vector<Customer> customers {};
	SitsArray<bool> reservations {false};
	const SitsArray<unsigned> sitsCosts {};

	std::string updateCustomer(urls::params_view params)
	{
		return "";	
	}
	std::string getCustomer(urls::params_view params)
	{
		return "";	
	}
	std::string createCustomer(urls::params_view params)
	{
		return "";	
	}
	std::string deleteCustomer(urls::params_view params)
	{
		return "";	
	}
	std::string buyTicket(urls::params_view params)
	{
		return "";	
	}
	std::string getAvaliableSeats()
	{
		return "";	
	}

	std::string processRequestTarget(const std::string_view target)
	{
		const auto parsedData = urls::parse_origin_form(target);	
		urls::url_view dataView = *parsedData;
		std::string result;

		if(dataView.path() == "/updateCustomer") {
			result = updateCustomer(dataView.params());
		} else if (dataView.path() == "/getCustomer") {
			result = getCustomer(dataView.params());
		} else if(dataView.path() == "/createCustomer") {
			result = createCustomer(dataView.params());
		} else if(dataView.path() == "/deleteCustomer") {
			result = deleteCustomer(dataView.params());
		} else if(dataView.path() == "/buyTicket") {
			result = buyTicket(dataView.params());
		} else if(dataView.path() == "/getAvaliableSeats") {
			result = getAvaliableSeats();
		} else {
			result = "Unknown target";
		}

		return result;
	}	
};


#endif  // SERVICE_LOGIC
