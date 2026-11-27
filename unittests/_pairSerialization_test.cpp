#include <userver/utest/utest.hpp>
#include <userver/formats/json.hpp>

#include "models/customer.hpp"
#include "_pairSerialization.hpp"

using service::models::Customer;
namespace json = userver::formats::json;


UTEST(pairJsonSerialization_Test, Basic) {
	auto pair1 = std::make_pair<size_t, size_t>(10, 20);		
	auto pair2 = std::make_pair<std::string, int>("text", 30);
	auto pair3 = std::make_pair<Customer, int>(Customer{"John",false,0,0}, 40);

	json::ValueBuilder builder1(pair1), builder2(pair2), builder3(pair3);

	json::Value jsonValue1(builder1.ExtractValue());
	json::Value jsonValue2(builder2.ExtractValue());
	json::Value jsonValue3(builder3.ExtractValue());

	EXPECT_EQ( json::ToString(jsonValue1), R"([10,20])" );
	EXPECT_EQ( json::ToString(jsonValue2), R"(["text",30])" );
	EXPECT_EQ( json::ToString(jsonValue3),
		R"([{"name":"John","has_discount":false},40])" );
}
