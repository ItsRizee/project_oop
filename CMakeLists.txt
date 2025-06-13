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
        pricing/SummerPlan.cpp
        pricing/SummerPlan.h
        customers/Customer.cpp
        customers/CustomerStatus.h
        customers/StatusType.h
        customers/CustomerStatus.cpp
        customers/Customer.h
        reservations/Date.cpp
        reservations/Date.h
        reservations/Reservation.cpp
        reservations/Reservation.h
        pricing/PricingStrategyFactory.cpp
        pricing/PricingStrategyFactory.h
        rooms/Apartment.cpp
        rooms/Apartment.h
        rooms/LuxuryRoom.cpp
        rooms/LuxuryRoom.h
)
