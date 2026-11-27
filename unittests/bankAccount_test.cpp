#include <userver/utest/utest.hpp>

#include "models/bankAccount.hpp"

using service::models::BankAccount;


UTEST(addMoney_Test, Basic) {
	BankAccount bankAccount{};
	EXPECT_EQ(bankAccount.addMoney(100), BankAccount::OperationCode::SUCESS);
	EXPECT_EQ(bankAccount.addMoney(0), BankAccount::OperationCode::ERROR);
	EXPECT_EQ(bankAccount.addMoney(-1), BankAccount::OperationCode::ERROR);
}	

UTEST(withdrawMoney_Test, Basic) {
	BankAccount bankAccount{};
	std::ignore = bankAccount.addMoney(1000);
	EXPECT_EQ(bankAccount.withdrawMoney(10), BankAccount::OperationCode::SUCESS);
	EXPECT_EQ(bankAccount.withdrawMoney(-1), BankAccount::OperationCode::ERROR);
	EXPECT_EQ(bankAccount.withdrawMoney(0), BankAccount::OperationCode::ERROR);
	EXPECT_EQ(bankAccount.withdrawMoney(1000), BankAccount::OperationCode::ERROR);
}	

UTEST(getMoney_Test, Basic) {
	BankAccount bankAccount{};
	EXPECT_EQ(bankAccount.getMoneyAmount(), 0);
	std::ignore = bankAccount.addMoney(1000);
	EXPECT_EQ(bankAccount.getMoneyAmount(), 1000);
}	

UTEST(bankAccountGetId_Test, Basic) {
	BankAccount bankAccount{1024};
	EXPECT_EQ(bankAccount.getId(), 1024);
}	
