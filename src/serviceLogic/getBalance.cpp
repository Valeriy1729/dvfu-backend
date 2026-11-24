#include "serviceLogic.hpp"

namespace service {

namespace logic {


ResponsePair getBalance(const HttpRequest& request)
{
	return {"", HttpStatus::kOk};	
}


}  // logic

}  // service

