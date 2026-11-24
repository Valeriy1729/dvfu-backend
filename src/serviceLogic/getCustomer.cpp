#include "serviceLogic.hpp"

namespace service {

namespace logic {


ResponsePair getCustomer(const HttpRequest& request)
{
	return {"", HttpStatus::kOk};	
}


}  // logic

}  // service

