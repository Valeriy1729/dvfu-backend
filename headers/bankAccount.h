#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

class BankAccount final {
	long long moneyAmount_;
public:

	BankAccount() noexcept : moneyAmount_(0) { }
	BankAccount(const BankAccount&) = delete;
	BankAccount& operator=(const BankAccount&) = delete;

	enum class OperationCode {SUCESS, ERROR};

	OperationCode addMoney(long long amount) & noexcept
	{
		moneyAmount_ += amount;	
		return OperationCode::SUCESS;
	}

	OperationCode withdrawMoney(long long amount) & noexcept
	{
		if(moneyAmount_ > amount) {
			moneyAmount_ -= amount;	
			return OperationCode::SUCESS;
		}
		return OperationCode::ERROR;
	}

	long long getMoneyAmount() const &
	{
		return moneyAmount_;	
	}
	
};


#endif  // BANK_ACCOUNT_H
