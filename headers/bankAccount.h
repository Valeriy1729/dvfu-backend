#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include "includes.h"


class BankAccount final {
	unsigned id_;
	long long moneyAmount_;

public:
	BankAccount(unsigned id) noexcept
		: id_(id), moneyAmount_(0) { }
	BankAccount(const BankAccount&) = default;
	BankAccount& operator=(const BankAccount&) = default;

	enum class OperationCode {SUCESS, ERROR};

	unsigned getId() const
	{
		return id_;	
	}

	OperationCode addMoney(long long amount) & noexcept
	{
		OperationCode opCode {OperationCode::ERROR};
		if(amount >= 0) {
			moneyAmount_ += amount;	
			opCode = OperationCode::SUCESS;
		}
		return opCode;
	}

	OperationCode withdrawMoney(long long amount) & noexcept
	{
		OperationCode opCode {OperationCode::ERROR};
		if(moneyAmount_ >= amount && amount >= 0) {
			moneyAmount_ -= amount;	
			opCode = OperationCode::SUCESS;
		}
		return opCode;
	}

	long long getMoneyAmount() const &
	{
		return moneyAmount_;	
	}
	
};


#endif  // BANK_ACCOUNT_H
