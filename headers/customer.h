#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "includes.h"


class Customer final {
	std::string name_;
	bool hasDiscount_;
	const unsigned id_, bankAccountId_;

public:
	Customer(std::string_view name, bool hasDiscount,
		unsigned id, unsigned bankAccountId)
	: name_(name), hasDiscount_(hasDiscount),
	  id_(id), bankAccountId_(bankAccountId) { }

	Customer(const Customer&) = default;
	Customer& operator=(const Customer&) = default;

	unsigned getId() const noexcept
	{
		return id_;
	}

	void updateName(const std::string& newName)
	{
		name_ = newName;	
	}

	unsigned getBankAccountId() const noexcept
	{
		return bankAccountId_;
	}

	std::string_view getName() const noexcept
	{
		return name_;
	}

	bool hasDiscount() const noexcept
	{
		return hasDiscount_;	
	}

	void changeName(std::string newName)
	{
		name_ = std::move(newName);
	}

	~Customer() = default;
};


// for json serialization
inline void tag_invoke(json::value_from_tag, json::value& jv, const Customer& customer)
{
	jv = {
		{ "name", customer.getName() },
		{ "hasDiscount", customer.hasDiscount() }
	};
}


#endif  // CUSTOMER_H
