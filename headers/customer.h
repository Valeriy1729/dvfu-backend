#ifndef USER_H
#define USER_H

#include "bankAccount.h"


struct Customer {
	const std::string name;
	BankAccount bankAccount;
};


#endif  // USER_H
