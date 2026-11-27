#include <userver/utest/utest.hpp>
#include <userver/formats/json.hpp>

#include "models/customer.hpp"

using service::models::Customer;
namespace json = userver::formats::json;


UTEST(customerTests, Basic) {
	Customer customer {"Bob", false, 10, 20};		
	EXPECT_EQ(customer.getName(), "Bob");
	EXPECT_EQ(customer.hasDiscount(), false);
	EXPECT_EQ(customer.getId(), 10);
	EXPECT_EQ(customer.getBankAccountId(), 20);
}

UTEST(customerUpdateNameTest, Basic) {
	Customer customer {"John", true, 1, 2};	
	customer.updateName("Alex");
	EXPECT_EQ(customer.getName(), "Alex");
}

UTEST(customerJsonSerializationTest, Basic) {
	Customer customer {"John", true, 1, 2};	
	json::ValueBuilder builder {customer};	
	json::Value jsonValue {builder.ExtractValue()};
	EXPECT_EQ(
		json::ToString(jsonValue),
		"{\"name\":\"John\",\"has_discount\":true}"
	);
}
