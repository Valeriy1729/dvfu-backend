#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

namespace service {

namespace models {


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

	unsigned getId() const & noexcept;
	void updateName(const std::string& newName) &;
	unsigned getBankAccountId() const & noexcept;
	std::string_view getName() const & noexcept;
	bool hasDiscount() const & noexcept;

	~Customer() = default;
};


#if(0)
// for json serialization
inline void tag_invoke(json::value_from_tag, json::value& jv, const Customer& customer)
{
	jv = {
		{ "name", customer.getName() },
		{ "hasDiscount", customer.hasDiscount() }
	};
}
#endif


}  // models

}  // service

#endif  // CUSTOMER_H
