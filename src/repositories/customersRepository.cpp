#include "repositories/customersRepository.hpp"

namespace service {
		

std::optional<models::Customer> CustomersRepository::add(
	const std::string& name, unsigned bankAccountId) &
{
	std::lock_guard<userver::engine::Mutex> lock (mutex_);
	bool isSpecialCustomer = (
		++creatingCustomerId_ % customersConstants::DISCOUNT_PERIOD == 0);

	// customer is special => customer has discount
	models::Customer newCustomer (name, isSpecialCustomer, creatingCustomerId_, bankAccountId);
	std::pair<std::string, models::Customer> pair (name, newCustomer);
	auto operationResult = customers_.insert(pair);	
	return (operationResult.second == true ?
		std::optional<models::Customer>(newCustomer) : std::nullopt);
}

bool CustomersRepository::updateCustomerName(
	const std::string& customerName, const std::string& newCustomerName) &
{
	std::lock_guard<userver::engine::Mutex> lock (mutex_);

	auto it1 = customers_.find(customerName);
	auto it2 = customers_.find(newCustomerName);
	if(it1 == customers_.end() || it2 != customers_.end())
		return false;

	models::Customer customer = it1->second;
	customer.updateName(newCustomerName);
	customers_.erase(it1);
	customers_.insert({newCustomerName, customer});

	return true;
}

std::optional<models::Customer> CustomersRepository::findByName(const std::string& name) &
{
	auto it = customers_.find(name);
	return (it != customers_.end() ?
		std::optional<models::Customer>(it->second) : std::nullopt);
}

size_t CustomersRepository::deleteByName(const std::string& customerName)
{
	std::lock_guard<userver::engine::Mutex> lock (mutex_);

	unsigned bankAccountId;
	auto it = customers_.find(customerName);
	if(it == customers_.end()) return 0;
	bankAccountId = it->second.getBankAccountId();
	BankAccountsRepository::get().delete_(bankAccountId);
	return customers_.erase(customerName);
}

CustomersRepository& CustomersRepository::get()
{
	static CustomersRepository instance;
	return instance;
}


}  // service

