#ifndef SETTINGS_H
#define SETTINGS_H

#include "includes.h"


namespace httpConstants {

constexpr std::string_view SERVER_FIELD = "Boost.Beast/server";
constexpr std::string_view CONTENT_TYPE_FIELD = "Boost.Beast/server";

}  // httpConstants



namespace seatsConstants {

constexpr size_t ROWS_COUNT = 6;
constexpr size_t COLUMNS_COUNT = 5;
constexpr const char* FILE_NAME = "seatsCosts.json";

}

template <typename T>
using SeatsMatrix = std::array<
	std::array<T, seatsConstants::COLUMNS_COUNT>,
	seatsConstants::ROWS_COUNT>;
   
namespace seatsConstants {
		
constexpr SeatsMatrix<unsigned> costs {{
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

}  // customersConstants


#endif  // SETTINGS_H
