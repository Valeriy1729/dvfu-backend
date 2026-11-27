#ifndef CUSTOMERS_REPO_H
#define CUSTOMERS_REPO_H

#include <optional>
#include <unordered_map>
#include <userver/engine/mutex.hpp>
#include <userver/utils/rand.hpp>

#include "_settings_.hpp"
#include "models/customer.hpp"
#include "repositories/bankAccountsRepository.hpp"

namespace service {

namespace utils = userver::utils;


class CustomersRepository final {
	unsigned creatingCustomerId_ {0};
	mutable userver::engine::Mutex mutex_;
	std::unordered_map<std::string, models::Customer> customers_;

	CustomersRepository() { }

public:
	CustomersRepository(const CustomersRepository&) = delete;
	CustomersRepository& operator=(const CustomersRepository&) = delete;

	std::optional<models::Customer> add(const std::string& name, unsigned bankAccountId) &;
	bool updateCustomerName(const std::string& customerName, const std::string& newCustomerName) &;
	std::optional<models::Customer> findByName(const std::string& name) &;
	size_t deleteByName(const std::string& customerName);

	static CustomersRepository& get();
};


}  // service

#endif  // CUSTOMERS_REPO_H

