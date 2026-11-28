#ifndef SEATS_REPO_H
#define SEATS_REPO_H

#include <optional>
#include <algorithm>
#include <userver/engine/mutex.hpp>

#include "_settings_.hpp"
#include "models/customer.hpp"

#include "repositories/IRepository.hpp"
#include "repositories/bankAccountsRepository.hpp"

namespace service {


class SeatsRepository final
	: public IRepository<SeatsRepository> {

	SeatsMatrix<long long> costs_;
	SeatsMatrix<bool> reservations_;
	mutable userver::engine::Mutex mutex_;

	SeatsRepository();

public:
	SeatsRepository(const SeatsRepository&) = delete;
	SeatsRepository& operator=(const SeatsRepository&) = delete;

	std::optional<long long> getCost(size_t row, size_t column) const &;
	std::optional<bool> getReservation(size_t row, size_t column) const &;
	bool setReservation(size_t row, size_t column, bool value) &;
	bool isValidIndexes(size_t row, size_t column) const &;

	SeatsVector getAvaliableSeats() const &;

	virtual void reset() &;

	static SeatsRepository& get();
};


}  // service

#endif  // SEATS_REPO_H

