#include "serviceLogic.hpp"

namespace service {

namespace logic {


ResponsePair getAvaliableSeats(const HttpRequest&)
{
	const SeatsVector& avaliableSeats = SeatsRepository::get().getAvaliableSeats();
	json::ValueBuilder builder (avaliableSeats);
	json::Value jsonValue (builder.ExtractValue());
	return {json::ToString(jsonValue), HttpStatus::kOk};	
}


}  // logic

}  // service

