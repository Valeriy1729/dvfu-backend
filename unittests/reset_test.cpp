#include <userver/utest/utest.hpp>
#include <userver/formats/json.hpp>

#include "repositories/bankAccountsRepository.hpp"
#include "repositories/customersRepository.hpp"
#include "repositories/seatsRepository.hpp"


UTEST(resetService_Test) {

	auto bankAccount = service::BankAccountsRepository::get().add().value();
	auto customer = service::CustomersRepository::get().add("Customer", 1).value();
	bool result = service::SeatsRepository::get().setReservation(0, 0, true);

	service::BankAccountsRepository::get().reset();		
	service::CustomersRepository::get().reset();		
	service::SeatsRepository::get().reset();		

	EXPECT_EQ(
		service::BankAccountsRepository::get().findById(bankAccount.getId()),
		std::nullopt);
	EXPECT_EQ(
		service::CustomersRepository::get().findByName(customer.getName()),
		std::nullopt);

	EXPECT_EQ( service::SeatsRepository::get().getReservation(0, 0), false );
}
