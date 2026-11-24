#include "serviceLogic.hpp"

namespace service {

namespace logic {


ResponsePair getAvaliableSeats(const HttpRequest& request)
{
	return {"", HttpStatus::kOk};	
}


}  // logic

}  // service

