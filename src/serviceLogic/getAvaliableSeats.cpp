#include "serviceLogic.h"


ResponsePair ServiceLogic::getAvaliableSeats()
{
	json::value avaliableSeatsJsonValue = json::value_from(
		SeatsRepository::get().getAvaliableSeats());
	return {json::serialize(avaliableSeatsJsonValue), http::status::ok};
}
