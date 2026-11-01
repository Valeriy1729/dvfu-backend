#ifndef SETTINGS_H
#define SETTINGS_H

#include "includes.h"


namespace httpConstants {

constexpr std::string_view SERVER_FIELD = "Boost.Beast/server";
constexpr std::string_view CONTENT_TYPE_FIELD = "Boost.Beast/server";
constexpr size_t MAX_REQUEST_BODY_SIZE = 100;
constexpr size_t MAX_REQUEST_TARGET_SIZE = 100;

}  // httpConstants



namespace seatsConstants {

constexpr size_t ROWS_COUNT = 6;
constexpr size_t COLUMNS_COUNT = 5;

}

template <typename T>
using SeatsMatrix = std::array<
	std::array<T, seatsConstants::COLUMNS_COUNT>,
	seatsConstants::ROWS_COUNT>;

using SeatsVector = std::vector<
	std::pair<std::pair<size_t, size_t>, long long>>;
   
namespace seatsConstants {
		
constexpr SeatsMatrix<long long> costs {{
	{1000, 1100, 1200, 1100, 1000},
	{1100, 1200, 1300, 1200, 1100},
	{1200, 1300, 1500, 1300, 1200},
	{1100, 1200, 1300, 1200, 1100},
	{1000, 1100, 1200, 1100, 1000},
	{ 900, 1000, 1100, 1000, 900 }	
}};

}  // seatsConstants


namespace customersConstants {
	
constexpr unsigned DISCOUNT_PERIOD = 5;
constexpr long long DISCOUNT = 500;

}  // customersConstants


#endif  // SETTINGS_H
