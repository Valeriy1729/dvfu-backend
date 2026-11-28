#include "repositories/bankAccountsRepository.hpp"

namespace service {


std::optional<models::BankAccount> BankAccountsRepository::add() &
{
	std::lock_guard<userver::engine::Mutex> lock (mutex_);

	models::BankAccount newBankAccount{++creatingBankAccountId_};
	std::pair<unsigned, models::BankAccount> pair (creatingBankAccountId_, newBankAccount);
	auto operationResult = bankAccounts_.insert(pair);
	return (operationResult.second == true ?
		std::optional<models::BankAccount>(newBankAccount) : std::nullopt);
}

size_t BankAccountsRepository::delete_(unsigned bankAccountId) &
{
	std::lock_guard<userver::engine::Mutex> lock (mutex_);
	return bankAccounts_.erase(bankAccountId);	
}

std::optional<models::BankAccount> BankAccountsRepository::findById(unsigned bankAccountId) &
{
	std::lock_guard<userver::engine::Mutex> lock (mutex_);

	auto it = bankAccounts_.find(bankAccountId);			
	return (it != bankAccounts_.end() ?
		std::optional<models::BankAccount>(it->second) : std::nullopt);
}

bool BankAccountsRepository::addMoney(unsigned bankAccountId, long long amount) &
{
	std::lock_guard<userver::engine::Mutex> lock (mutex_);

	auto it = bankAccounts_.find(bankAccountId);	
	if(it == bankAccounts_.end()) return false;
	models::BankAccount::OperationCode result = it->second.addMoney(amount);
	return (result == models::BankAccount::OperationCode::SUCESS ? true : false);
}

bool BankAccountsRepository::withdrawMoney(unsigned bankAccountId, long long amount) &
{
	std::lock_guard<userver::engine::Mutex> lock (mutex_);

	auto it = bankAccounts_.find(bankAccountId);	
	if(it == bankAccounts_.end()) return false;
	models::BankAccount::OperationCode result = it->second.withdrawMoney(amount);
	return (result == models::BankAccount::OperationCode::SUCESS ? true : false);
}

std::optional<long long> BankAccountsRepository::getMoneyAmountById(unsigned bankAccountId) &
{
	std::lock_guard<userver::engine::Mutex> lock (mutex_);

	auto it = bankAccounts_.find(bankAccountId);		
	if(it == bankAccounts_.end()) return std::nullopt;
	return it->second.getMoneyAmount();
}

void BankAccountsRepository::reset() &
{
	std::lock_guard<userver::engine::Mutex> lock (mutex_);
	bankAccounts_.clear();			
}

BankAccountsRepository& BankAccountsRepository::get()
{
	static BankAccountsRepository instance;	
	return instance;
}


}  // service
