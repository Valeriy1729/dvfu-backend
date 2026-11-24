#include "serviceLogic.hpp"

namespace service {

namespace logic {


void _throwResourceNotFound(const std::string& error)
{
	throw userver::server::handlers::ResourceNotFound(
		userver::server::handlers::ExternalBody(error)
	);
}


}  // logic

}  // service

