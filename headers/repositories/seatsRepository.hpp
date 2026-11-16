#ifndef SEATS_REPO_H
#define SEATS_REPO_H

#include <algorithm>
#include <optional>

#include "_settings_.hpp"
#include "models/customer.hpp"

namespace service {


class SeatsRepository final {
	SeatsMatrix<long long> costs_;
	SeatsMatrix<bool> reservations_;

	SeatsRepository();

	bool isValidIndexes(size_t row, size_t column) const;

public:
	SeatsRepository(const SeatsRepository&) = delete;
	SeatsRepository& operator=(const SeatsRepository&) = delete;

	std::optional<long long> getCost(size_t row, size_t column) const;
	std::optional<bool> getReservation(size_t row, size_t column) const;
	bool setReservation(size_t row, size_t column, bool value);
	SeatsVector getAvaliableSeats() const;

	static SeatsRepository& get();
};


}  // service

#endif  // SEATS_REPO_H

