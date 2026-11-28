#ifndef BANK_ACCOUNTS_REPO_H
#define BANK_ACCOUNTS_REPO_H

#include <optional>
#include <unordered_map>
#include <userver/engine/mutex.hpp>

#include "repositories/IRepository.hpp"
#include "models/bankAccount.hpp"

namespace service {


class BankAccountsRepository final
	: public IRepository<BankAccountsRepository> {

	unsigned creatingBankAccountId_ {0};
	std::unordered_map<unsigned, models::BankAccount> bankAccounts_;
	mutable userver::engine::Mutex mutex_;
	BankAccountsRepository() { }

public:
	BankAccountsRepository(const BankAccountsRepository&) = delete;
	BankAccountsRepository& operator=(const BankAccountsRepository&) = delete;

	std::optional<models::BankAccount> add() &;
	size_t delete_(unsigned bankAccountId) &;
	std::optional<models::BankAccount> findById(unsigned bankAccountId) &;
	bool addMoney(unsigned bankAccountId, long long amount) &;
	bool withdrawMoney(unsigned bankAccountId, long long amount) &;
	std::optional<long long> getMoneyAmountById(unsigned bankAccountId) &;

	virtual void reset() &;

	static BankAccountsRepository& get();
};


}  // service

#endif  // BANK_ACCOUNTS_REPO_H

