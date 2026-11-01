cmake_minimum_required(VERSION 3.15)
project(MyAsioProject VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

find_package(Boost REQUIRED COMPONENTS system url json)

add_executable(my_app
	src/main.cpp
	src/serviceLogic/addMoney.cpp
	src/serviceLogic/createCustomer.cpp
	src/serviceLogic/deleteCustomer.cpp
	src/serviceLogic/getAvaliableSeats.cpp
	src/serviceLogic/getBalance.cpp
	src/serviceLogic/getCustomer.cpp
	src/serviceLogic/reserveSeat.cpp
	src/serviceLogic/updateCustomer.cpp
)

target_include_directories(my_app PRIVATE headers)

target_link_libraries(my_app PRIVATE
    Boost::headers     
    Boost::system      
    Threads::Threads   
    Boost::url
    Boost::json
)


