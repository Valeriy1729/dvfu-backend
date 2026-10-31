#ifndef CUSTOMERS_REPO_H
#define CUSTOMERS_REPO_H

#include "includes.h"
#include "customer.h"


class CustomersRepository final {
	std::unordered_map<std::string, Customer> customers_;

	CustomersRepository() { }

public:

	CustomersRepository(const CustomersRepository&) = delete;
	CustomersRepository& operator=(const CustomersRepository&) = delete;

	bool add(const std::string& name, unsigned id, unsigned bankAccountId)
	{
		std::pair<std::string, Customer> pair (name, {name, id, bankAccountId});
		auto operationResult = customers_.insert(pair);	
		return operationResult.second;
	}

	Customer* findByName(const std::string& name) &
	{
		auto it = customers_.find(name);			
		return (it != customers_.end() ? &(it->second) : nullptr);
	}

	static CustomersRepository& get()
	{
		static CustomersRepository instance;	
		return instance;
	}
};


#endif  // CUSTOMERS_REPO_H
