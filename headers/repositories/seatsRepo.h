#ifndef SEATS_REPO_H
#define SEATS_REPO_H

#include "includes.h"
#include "customer.h"
#include "settings.h"


class SeatsRepository final {
	SeatsMatrix<long long> costs_;
	SeatsMatrix<bool> reservations_;

	SeatsRepository() : costs_(seatsConstants::costs)
	{
		std::for_each(reservations_.begin(), reservations_.end(), [](auto& row) {
			std::fill(row.begin(), row.end(), false);				
		});
	}

	bool isValidIndexes(size_t row, size_t column) const
	{
		return row < seatsConstants::ROWS_COUNT &&
		       column < seatsConstants::COLUMNS_COUNT;	
	}

public:
	SeatsRepository(const SeatsRepository&) = delete;
	SeatsRepository& operator=(const SeatsRepository&) = delete;

	std::optional<long long> getCost(size_t row, size_t column) const
	{
		if(!isValidIndexes(row, column)) return std::nullopt;
		return costs_[row][column];
	}

	std::optional<bool> getReservation(size_t row, size_t column) const
	{
		if(!isValidIndexes(row, column)) return std::nullopt;
		return reservations_[row][column];
	}

	bool setReservation(size_t row, size_t column, bool value)
	{
		if(!isValidIndexes(row, column)) return false;
		reservations_[row][column] = value;	
		return true;
	}

	SeatsVector getAvaliableSeats() const
	{
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

	static SeatsRepository& get()
	{
		static SeatsRepository instance;	
		return instance;
	}
};


#endif  // SEATS_REPO_H
