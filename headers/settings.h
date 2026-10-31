#ifndef SETTINGS_H
#define SETTINGS_H

#include "includes.h"


namespace httpConstants {
constexpr std::string_view SERVER_FIELD = "Boost.Beast/server";
constexpr std::string_view CONTENT_TYPE_FIELD = "Boost.Beast/server";
}  // httpConstants

namespace sitsConstants {
constexpr size_t ROWS_COUNT = 5;
constexpr size_t COLUMNS_COUNT = 5;
}  // sitsConstants


#endif  // SETTINGS_H
