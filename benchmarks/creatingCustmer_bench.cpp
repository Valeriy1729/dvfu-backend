#include <benchmark/benchmark.h>
#include <userver/engine/run_standalone.hpp>
#include <userver/utils/rand.hpp>

#include "repositories/customersRepository.hpp"


void CreatingCustomerBenchmark(benchmark::State& state)
{
	userver::engine::RunStandalone([&] -> void {

		const unsigned N = state.range(0);

		for(auto _ : state) {

			// Creating and deleting N customers 
			for(size_t i = 0; i < N; ++i) {
				auto createResult = service::CustomersRepository::get().add(
					"TestCustomer" + std::to_string(i), i
				);
				auto deleteResult = service::CustomersRepository::get().deleteByName(
					"TestCustomer" + std::to_string(i)
				);
				benchmark::DoNotOptimize(createResult);
				benchmark::DoNotOptimize(deleteResult);
			}
		}
	});
}


BENCHMARK(CreatingCustomerBenchmark)->RangeMultiplier(4)->Range(16, 65536);

