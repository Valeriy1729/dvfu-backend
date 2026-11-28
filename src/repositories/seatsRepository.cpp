#include "repositories/seatsRepository.hpp"

namespace service {


SeatsRepository::SeatsRepository() : costs_ (seatsConstants::costs)
{
	std::for_each(reservations_.begin(), reservations_.end(), [](auto& row) {
		std::fill(row.begin(), row.end(), false);
	});
}

bool SeatsRepository::isValidIndexes(size_t row, size_t column) const &
{
	return row < seatsConstants::ROWS_COUNT &&
	       column < seatsConstants::COLUMNS_COUNT;
}

std::optional<long long> SeatsRepository::getCost(size_t row, size_t column) const &
{
	std::lock_guard<userver::engine::Mutex> lock (mutex_);

	if(!isValidIndexes(row, column)) return std::nullopt;
	return costs_[row][column];
}

std::optional<bool> SeatsRepository::getReservation(size_t row, size_t column) const &
{
	std::lock_guard<userver::engine::Mutex> lock (mutex_);

	if(!isValidIndexes(row, column)) return std::nullopt;
	return reservations_[row][column];
}

bool SeatsRepository::setReservation(size_t row, size_t column, bool value) &
{
	std::lock_guard<userver::engine::Mutex> lock (mutex_);

	if(!isValidIndexes(row, column)) return false;
	reservations_[row][column] = value;
	return true;
}

SeatsVector SeatsRepository::getAvaliableSeats() const &
{
	std::lock_guard<userver::engine::Mutex> lock (mutex_);

	SeatsVector avaliableSeats;
	std::pair<size_t, size_t> position;
	for(size_t i = 0; i < seatsConstants::ROWS_COUNT; ++i) {
		for(size_t j = 0; j < seatsConstants::COLUMNS_COUNT; ++j) {
			if(reservations_[i][j] == false)
				avaliableSeats.emplace_back(std::pair{i, j}, costs_[i][j]);
		}
	}
	return avaliableSeats;
}

void SeatsRepository::reset() &
{
	std::lock_guard<userver::engine::Mutex> lock (mutex_);

	std::for_each(reservations_.begin(), reservations_.end(), [](auto& row) {
		std::fill(row.begin(), row.end(), false);
	});
}

SeatsRepository& SeatsRepository::get()
{
	static SeatsRepository instance;
	return instance;
}


}  // service
