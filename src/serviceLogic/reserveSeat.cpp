#include "serviceLogic.hpp"

namespace service {

namespace logic {


ResponsePair reserveSeat(const HttpRequest& request)
{
	return {"", HttpStatus::kOk};	
}


}  // logic

}  // service

