#ifndef PAIR_SERIALIZATION
#define PAIR_SERIALIZATION

#include <userver/formats/json.hpp>
#include <userver/formats/serialize/to.hpp>
#include <userver/formats/serialize/common_containers.hpp>

namespace userver::formats::serialize {


template <typename T1, typename T2, typename Value>
Value Serialize(const std::pair<T1, T2>& pair, To<Value>)
{
	typename Value::Builder builder {formats::common::Type::kArray};	
	builder.PushBack(pair.first);
	builder.PushBack(pair.second);
	return builder.ExtractValue();
}


}  // userver::formats::serialize

#endif  // PAIR_SERIALIZATION
