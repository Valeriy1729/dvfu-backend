#include "serviceLogic.hpp"

namespace service {

namespace logic {


userver::engine::Mutex reserveSeatMutex;

ResponsePair reserveSeat(const HttpRequest& request)
{
	bool seatReservation;
	size_t seatRow, seatColumn;
	long long seatCost, moneyAmount;
	std::string customerName;
	models::Customer customer;

	const std::string errorPrefix = "Error when reserving seat: ";

	try {
		seatRow = _getArgWithCheck<size_t>(request, "row", errorPrefix);	
		seatColumn = _getArgWithCheck<size_t>(request, "column", errorPrefix);	
		customerName = _getArgWithCheck<std::string>(request, "name", errorPrefix);

		customer = _getFromOptional(
			CustomersRepository::get().findByName(customerName),
			errorPrefix + "No such customer with name '" + customerName + "'\n");

		moneyAmount = _getFromOptional(
			BankAccountsRepository::get().getMoneyAmountById(customer.getBankAccountId()),
			errorPrefix + "No bank account for customer with name '" + customerName + "'\n");
		
		seatReservation = _getFromOptional(
			SeatsRepository::get().getReservation(seatRow, seatColumn),
			errorPrefix + "Row or column is out of range\n");

		seatCost = _getFromOptional(
			SeatsRepository::get().getCost(seatRow, seatColumn),
			errorPrefix + "Could not get seat cost\n");

	} catch(_BadRequestException& ex) {
		return {ex.what(), HttpStatus::kBadRequest};	
	}

	if(customer.hasDiscount()) {
		seatCost = std::max(
			seatCost - customersConstants::DISCOUNT, 0ll);			
	}

	// first checks
	if(seatReservation == true) {
		return {errorPrefix + "Seat is already reserved\n", HttpStatus::kConflict};
	}
	if(moneyAmount < seatCost) {
		return {errorPrefix + "Insufficient funds, balance is too low",
			HttpStatus::kConflict};	
	} {
		std::lock_guard<userver::engine::Mutex> lock(reserveSeatMutex);

		seatReservation = SeatsRepository::get().getReservation(seatRow, seatColumn).value();

		// second checks
		if(seatReservation == true) {
			return {errorPrefix + "Seat is already reserved\n", HttpStatus::kConflict};
		}
		if(!BankAccountsRepository::get().withdrawMoney(
			customer.getBankAccountId(), seatCost)) {
			return {errorPrefix + "Insufficient funds, balance is too low",
				HttpStatus::kConflict};	
		}

		SeatsRepository::get().setReservation(seatRow, seatColumn, true);
	}

	return {fmt::format("Seat ({}, {}) reserved with {}\n",
		seatRow, seatColumn, customerName), HttpStatus::kOk};	
}


}  // logic

}  // service

