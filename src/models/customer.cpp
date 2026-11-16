#include "models/customer.hpp"

namespace service {

namespace models {


unsigned Customer::getId() const & noexcept { return id_; }

void Customer::updateName(const std::string& newName) & { name_ = newName; }

unsigned Customer::getBankAccountId() const & noexcept { return bankAccountId_; }

std::string_view Customer::getName() const & noexcept { return name_; }

bool Customer::hasDiscount() const & noexcept { return hasDiscount_; }


}  // models

}  // service
