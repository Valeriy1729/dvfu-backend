#include "server.h"
#include "repositories/customersRepo.h"
#include "repositories/bankAccountsRepo.h"
#include "repositories/seatsRepo.h"

int main(int argc, char** argv)
{
	if(argc != 3)
		throw std::invalid_argument("Usage: ./my_app <host> <port>");

	HttpServer server {
		argv[1],  // host
		static_cast<unsigned short>(std::stoul(argv[2]))  // port
	};	

	server.startListening();
	return EXIT_SUCCESS;
}
