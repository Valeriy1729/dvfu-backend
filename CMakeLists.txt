cmake_minimum_required(VERSION 3.14)
project(cinema_booking_service CXX)


find_package(
    userver
    COMPONENTS core
    REQUIRED
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


add_library(${PROJECT_NAME}_objs OBJECT
	src/models/bankAccount.cpp
	src/models/customer.cpp
	src/httpHandler.cpp

	src/repositories/bankAccountRepository.cpp
	src/repositories/customersRepository.cpp
	src/repositories/seatsRepository.cpp

	src/serviceLogic/_throwResourceNotFound.cpp
	src/serviceLogic/_processRequest.cpp
	src/serviceLogic/addMoney.cpp
	src/serviceLogic/createCustomer.cpp
	src/serviceLogic/getCustomer.cpp
	src/serviceLogic/updateCustomer.cpp
	src/serviceLogic/deleteCustomer.cpp
	src/serviceLogic/getAvaliableSeats.cpp
	src/serviceLogic/getBalance.cpp
	src/serviceLogic/reserveSeat.cpp
	src/serviceLogic/resetService.cpp
)

target_link_libraries(${PROJECT_NAME}_objs userver::core)
target_include_directories(${PROJECT_NAME}_objs PUBLIC src headers)


# service
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_objs)


# unittests
add_executable(${PROJECT_NAME}-unittest
	unittests/bankAccount_test.cpp
	unittests/customer_test.cpp
	unittests/_executeWithCheck_test.cpp
	unittests/_getArgWithCheck_test.cpp
	unittests/_getFromOptional_test.cpp
	unittests/_pairSerialization_test.cpp
)
target_link_libraries(${PROJECT_NAME}-unittest ${PROJECT_NAME}_objs userver::utest)
add_google_tests(${PROJECT_NAME}-unittest)


# benchmarks
add_executable(${PROJECT_NAME}_benchmark
	benchmarks/findingCustomer_bench.cpp
	benchmarks/creatingCustmer_bench.cpp
)
target_link_libraries(${PROJECT_NAME}_benchmark ${PROJECT_NAME}_objs userver::ubench)
add_google_benchmark_tests(${PROJECT_NAME}_benchmark)


userver_testsuite_add_simple()

