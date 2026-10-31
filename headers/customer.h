#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "includes.h"


class Customer final {
	std::string name_;
	const unsigned id_, bankAccountId_;

public:
	Customer(std::string_view name,
		unsigned id, unsigned bankAccountId)
		: name_(name), id_(id), bankAccountId_(bankAccountId) { }

	Customer(const Customer&) = default;
	Customer& operator=(const Customer&) = default;

	unsigned getId() const noexcept
	{
		return id_;
	}

	unsigned getBankAccountId() const noexcept
	{
		return bankAccountId_;
	}

	std::string_view getName() const noexcept
	{
		return name_;
	}

	void changeName(std::string newName)
	{
		name_ = std::move(newName);
	}

	~Customer() = default;
};


// for unordered_set
namespace std {
template <> struct hash<Customer> {
	size_t operator()(const Customer& customer) const
	{
		return static_cast<size_t>(customer.getId());	
	}		
};		
}


#endif  // CUSTOMER_H
