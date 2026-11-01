#ifndef BANK_ACCOUNTS_REPO_H
#define BANK_ACCOUNTS_REPO_H

#include "includes.h"
#include "bankAccount.h"


class BankAccountsRepository final {

	unsigned creatingBankAccountId_ {0};
	std::unordered_map<unsigned, BankAccount> bankAccounts_;

	BankAccountsRepository() { }

public:

	BankAccountsRepository(const BankAccountsRepository&) = delete;
	BankAccountsRepository& operator=(const BankAccountsRepository&) = delete;

	std::optional<BankAccount> add() &
	{
		BankAccount newBankAccount{++creatingBankAccountId_};
		std::pair<unsigned, BankAccount> pair (creatingBankAccountId_, newBankAccount);
		auto operationResult = bankAccounts_.insert(pair);	
		return (operationResult.second == true ?
			std::optional<BankAccount>(newBankAccount) : std::nullopt);
	}

	size_t delete_(unsigned bankAccountId) &
	{
		return bankAccounts_.erase(bankAccountId);	
	}

	std::optional<BankAccount> findById(unsigned bankAccountId) &
	{
		auto it = bankAccounts_.find(bankAccountId);			
		return (it != bankAccounts_.end() ?
			std::optional<BankAccount>(it->second) : std::nullopt);
	}

	bool addMoney(unsigned bankAccountId, long long amount)
	{
		auto it = bankAccounts_.find(bankAccountId);	
		if(it == bankAccounts_.end()) return false;
		BankAccount::OperationCode result = it->second.addMoney(amount);
		return (result == BankAccount::OperationCode::SUCESS ? true : false);
	}

	bool withdrawMoney(unsigned bankAccountId, long long amount)
	{
		auto it = bankAccounts_.find(bankAccountId);	
		if(it == bankAccounts_.end()) return false;
		BankAccount::OperationCode result = it->second.withdrawMoney(amount);
		return (result == BankAccount::OperationCode::SUCESS ? true : false);
	}

	std::optional<long long> getMoneyAmountById(unsigned bankAccountId) &
	{
		auto it = bankAccounts_.find(bankAccountId);		
		if(it == bankAccounts_.end()) return std::nullopt;
		return it->second.getMoneyAmount();
	}

	static BankAccountsRepository& get()
	{
		static BankAccountsRepository instance;	
		return instance;
	}
};


#endif  // BANK_ACCOUNTS_REPO_H
