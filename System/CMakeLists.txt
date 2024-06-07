cmake_minimum_required(VERSION 3.28)

project(SupermarketManagementSystem C CXX)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_C_STANDARD 11)

add_executable(System

        item.c
        function.c
        main.c
        logIn.cpp

)
