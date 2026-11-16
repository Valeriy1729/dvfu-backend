cmake_minimum_required(VERSION 3.14)
project(cinema_booking_service CXX)


find_package(
    userver
    COMPONENTS core
    REQUIRED
)


add_library(${PROJECT_NAME}_objs OBJECT
	src/models/bankAccount.cpp
	src/models/customer.cpp
	src/http_handler.cpp
	src/repositories/bankAccountRepository.cpp
	src/repositories/customersRepository.cpp
	src/repositories/seatsRepository.cpp
)
target_link_libraries(${PROJECT_NAME}_objs userver::core)
target_include_directories(${PROJECT_NAME}_objs PUBLIC src headers)


# service
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_objs)


# unittests
add_executable(${PROJECT_NAME}-unittest unittests/test.cpp)
target_link_libraries(${PROJECT_NAME}-unittest ${PROJECT_NAME}_objs userver::utest)
add_google_tests(${PROJECT_NAME}-unittest)


# benchmarks
add_executable(${PROJECT_NAME}_benchmark benchmarks/benchmark.cpp)
target_link_libraries(${PROJECT_NAME}_benchmark ${PROJECT_NAME}_objs userver::ubench)
add_google_benchmark_tests(${PROJECT_NAME}_benchmark)


userver_testsuite_add_simple()

