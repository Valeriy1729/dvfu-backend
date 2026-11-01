#include "server.h"
#include "repositories/customersRepo.h"
#include "repositories/bankAccountsRepo.h"
#include "repositories/seatsRepo.h"

int main(int argc, char** argv)
{
	HttpServer server {"127.0.0.1", 1111};	
	server.startListening();
	return EXIT_SUCCESS;
}
