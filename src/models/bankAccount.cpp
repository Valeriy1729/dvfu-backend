#include "models/bankAccount.hpp"

namespace service {

namespace models {


unsigned BankAccount::getId() const noexcept { return id_; }

BankAccount::OperationCode BankAccount::addMoney(long long amount) & noexcept
{
	OperationCode opCode {OperationCode::ERROR};
	if(amount > 0) {
		moneyAmount_ += amount;	
		opCode = OperationCode::SUCESS;
	}
	return opCode;
}

BankAccount::OperationCode BankAccount::withdrawMoney(long long amount) & noexcept
{
	OperationCode opCode {OperationCode::ERROR};
	if(moneyAmount_ >= amount && amount >= 0) {
		moneyAmount_ -= amount;	
		opCode = OperationCode::SUCESS;
	}
	return opCode;
}

long long BankAccount::getMoneyAmount() const & noexcept { return moneyAmount_; }


}  // models

}  // service
