cmake_minimum_required(VERSION 3.31)
project(project_oop)

set(CMAKE_CXX_STANDARD 20)

add_executable(project_oop main.cpp
        rooms/Room.h
        pricing/PricingStrategy.h
        rooms/Room.cpp
        rooms/SingleRoom.cpp
        rooms/SingleRoom.h
        rooms/ConferenceRoom.cpp
        rooms/ConferenceRoom.h
        rooms/DoubleRoom.cpp
        rooms/DoubleRoom.h
        pricing/StandartPlan.cpp
        pricing/StandartPlan.h
        pricing/WeekendPlan.cpp
        pricing/WeekendPlan.h
        customers/Customer.cpp
        customers/CustomerStatus.h
        customers/StatusType.h
        customers/CustomerStatus.cpp
        customers/Customer.h
)
