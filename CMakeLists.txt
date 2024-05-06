cmake_minimum_required(VERSION 3.10)
project(BlackJackWithFriends)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(./include)

file(GLOB TARGET_SRC "./src/*.cpp" )

add_executable(BlackJackWithFriends ${TARGET_SRC})
