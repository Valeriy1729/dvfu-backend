#include "serviceLogic.h"


ResponsePair ServiceLogic::reserveSeat(urls::params_view params, std::string_view body)
{
	// parsing request body
	auto parsedBody = urls::parse_query(body);
	if(!parsedBody.has_value())
		return {"Error when reserving seat: couldn't parse request body",
			http::status::bad_request};
	auto bodyParams = *parsedBody;

	// getting customer name from request body
	auto customerNameIt = bodyParams.find("name");
	if(customerNameIt == bodyParams.end())
		return {"Error when reserving seat: Parametr 'name' did not specified in request body",
			http::status::bad_request};
	std::string customerName = std::string((*customerNameIt).value);

	// finding customer by customerName
	std::optional<Customer> customer = CustomersRepository::get().findByName(customerName);
	if(!customer.has_value())
		return {"Error when reserving seat: No such customer with name: '" + customerName + "'",
			http::status::bad_request};

	// getting seat row from request body
	auto seatRowIt = bodyParams.find("row");
	if(seatRowIt == bodyParams.end())
		return {"Error when reserving seat: Parametr 'row' did not specified in request body",
			http::status::bad_request};
	unsigned seatRow = std::stoi(std::string((*seatRowIt).value));

	// getting seat column from request body
	auto seatColumnIt = bodyParams.find("column");
	if(seatColumnIt == bodyParams.end())
		return {"Error when reserving seat: Parametr 'column' did not specified in request body",
			http::status::bad_request};
	unsigned seatColumn = std::stoi(std::string((*seatColumnIt).value));

	// getting money amount from bank account
	std::optional<long long> moneyAmount = BankAccountsRepository::get().getMoneyAmountById(
		customer.value().getBankAccountId());
	if(!moneyAmount.has_value())
		return {"Error when reserving seat: No bank account for customer with name: '" +
			customerName + "'", http::status::bad_request};

	// getting current reservation
	std::optional<bool> reservation = SeatsRepository::get().getReservation(seatRow, seatColumn);
	if(!reservation.has_value())
	       return {"Error when reserving seat: Row and column are out of range",
		       http::status::bad_request};	
	if(reservation.value() == true)
	       return {"Seat is already reserved", http::status::ok};	

	long long seatCost = std::max(SeatsRepository::get().getCost(seatRow, seatColumn).value() -
		(customer.value().hasDiscount() ? customersConstants::DISCOUNT : 0ll), 0ll);
	if(moneyAmount < seatCost)
	       return {"Insufficient funds: balance is too low", http::status::ok};	

	// reserving the seat
	BankAccountsRepository::get().withdrawMoney(customer.value().getBankAccountId(), seatCost);	
	SeatsRepository::get().setReservation(seatRow, seatColumn, true);
	
	return {"Seat (" + std::to_string(seatRow) + ", " + std::to_string(seatColumn) + ") reserved",
		http::status::ok};
}

