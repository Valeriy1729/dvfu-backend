#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

namespace service {

namespace models {


class BankAccount final {
	unsigned id_;
	long long moneyAmount_;

public:
	BankAccount() = default;
	BankAccount(unsigned id) noexcept
		: id_(id), moneyAmount_(0) { }
	BankAccount(const BankAccount&) = default;
	BankAccount& operator=(const BankAccount&) = default;

	enum class OperationCode {SUCESS, ERROR};

	unsigned getId() const noexcept;
	OperationCode addMoney(long long amount) & noexcept;
	OperationCode withdrawMoney(long long amount) & noexcept;
	long long getMoneyAmount() const & noexcept;
};


}  // models

}  // service

#endif  // BANK_ACCOUNT_H

