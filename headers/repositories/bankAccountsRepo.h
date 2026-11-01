#ifndef BANK_ACCOUNTS_REPO_H
#define BANK_ACCOUNTS_REPO_H

#include "includes.h"
#include "bankAccount.h"


class BankAccountsRepository final {
	std::unordered_map<unsigned, BankAccount> bankAccounts_;

	BankAccountsRepository() { }

public:

	BankAccountsRepository(const BankAccountsRepository&) = delete;
	BankAccountsRepository& operator=(const BankAccountsRepository&) = delete;

	bool add(unsigned id, unsigned customerId) &
	{
		std::pair<unsigned, BankAccount> pair (id, {id, customerId});
		auto operationResult = bankAccounts_.insert(pair);	
		return operationResult.second;
	}

	std::optional<BankAccount> findById(unsigned id) &
	{
		auto it = bankAccounts_.find(id);			
		return (it != bankAccounts_.end() ?
			std::optional<BankAccount>(it->second) : std::nullopt);
	}

	static BankAccountsRepository& get()
	{
		static BankAccountsRepository instance;	
		return instance;
	}
};


#endif  // BANK_ACCOUNTS_REPO_H
