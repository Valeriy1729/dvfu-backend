#include <benchmark/benchmark.h>
#include <userver/engine/run_standalone.hpp>
#include <userver/utils/rand.hpp>

#include "repositories/customersRepository.hpp"


void FindingCustomerBenchmark(benchmark::State& state)
{
	userver::engine::RunStandalone([&] -> void {

		const unsigned N = state.range(0);

		// Creating N customers 
		for(size_t i = 0; i < N; ++i) {
			service::CustomersRepository::get().add(
				"TestCustomer" + std::to_string(i), i
			);
		}

		// benchmarking time to get customer
		for(auto _ : state) {
			auto result = service::CustomersRepository::get().findByName(
				"TestCustomer" + std::to_string(userver::utils::RandRange(0U, N)));
			benchmark::DoNotOptimize(result);
		}		
	});
}


BENCHMARK(FindingCustomerBenchmark)->RangeMultiplier(4)->Range(16, 65536);

