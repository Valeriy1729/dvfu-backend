#ifndef CUSTOMERS_REPO_H
#define CUSTOMERS_REPO_H

#include "includes.h"
#include "settings.h"
#include "customer.h"

#include "bankAccountsRepo.h"


class CustomersRepository final {
	unsigned creatingCustomerId_ {0};
	std::unordered_map<std::string, Customer> customers_;

	CustomersRepository() { }

public:

	CustomersRepository(const CustomersRepository&) = delete;
	CustomersRepository& operator=(const CustomersRepository&) = delete;

	std::optional<Customer> add(const std::string& name, unsigned bankAccountId) &
	{
		bool isSpecialCustomer = (
			++creatingCustomerId_ % customersConstants::DISCOUNT_PERIOD == 0);

		// customer is special => customer has discount
		Customer newCustomer (name, isSpecialCustomer, creatingCustomerId_, bankAccountId);
		std::pair<std::string, Customer> pair (name, newCustomer);
		auto operationResult = customers_.insert(pair);	
		return (operationResult.second == true ?
			std::optional<Customer>(newCustomer) : std::nullopt);
	}

	bool updateCustomerName(const std::string& customerName, const std::string& newCustomerName) &
	{
		auto it1 = customers_.find(customerName);			
		auto it2 = customers_.find(newCustomerName);			
		if(it1 == customers_.end() || it2 != customers_.end())
			return false;

		Customer customer = it1->second;
		customer.updateName(newCustomerName);
		customers_.erase(it1);
		customers_.insert({newCustomerName, customer});

		return true;
	}

	std::optional<Customer> findByName(const std::string& name) &
	{
		auto it = customers_.find(name);			
		return (it != customers_.end() ?
			std::optional<Customer>(it->second) : std::nullopt);
	}

	size_t deleteByName(const std::string& customerName)
	{
		unsigned bankAccountId = customers_.find(customerName)->second.getBankAccountId();		
		BankAccountsRepository::get().delete_(bankAccountId);
		return customers_.erase(customerName);
	}

	static CustomersRepository& get()
	{
		static CustomersRepository instance;	
		return instance;
	}
};


#endif  // CUSTOMERS_REPO_H
