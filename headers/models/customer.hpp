#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <userver/formats/json.hpp>

namespace service {

namespace models {


class Customer final {
	std::string name_;
	bool hasDiscount_;
	unsigned id_, bankAccountId_;

public:
	Customer() = default;
	Customer(std::string_view name, bool hasDiscount,
		unsigned id, unsigned bankAccountId)
	: name_(name), hasDiscount_(hasDiscount),
	  id_(id), bankAccountId_(bankAccountId) { }

	Customer(const Customer&) = default;
	Customer& operator=(const Customer&) = default;

	unsigned getId() const & noexcept;
	void updateName(const std::string& newName) &;
	unsigned getBankAccountId() const & noexcept;
	std::string_view getName() const & noexcept;
	bool hasDiscount() const & noexcept;

	~Customer() = default;
};

// for JSON, BSON, YAML,... serialization
template <typename Format>
Format Serialize(const Customer& customer,
	userver::formats::serialize::To<Format>)
{
	typename Format::Builder builder;
	builder["name"] = customer.getName();
	builder["hasDiscount"] = customer.hasDiscount();
	return builder.ExtractValue();
}


}  // models

}  // service

#endif  // CUSTOMER_H
