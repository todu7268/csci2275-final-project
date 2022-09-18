cmake_minimum_required(VERSION 3.20)
project(Project)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(.)

add_executable(Project
        Block.cpp
        Blockchain.cpp
        main_1.cpp
        sha256.cpp
	  Wallet.cpp
        Transaction.cpp)
