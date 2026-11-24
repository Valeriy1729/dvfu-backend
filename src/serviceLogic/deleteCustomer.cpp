#include "serviceLogic.hpp"

namespace service {

namespace logic {


ResponsePair deleteCustomer(const HttpRequest& request)
{
	return {"", HttpStatus::kOk};	
}


}  // logic

}  // service
