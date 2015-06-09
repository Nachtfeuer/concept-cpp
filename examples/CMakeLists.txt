cmake_minimum_required (VERSION 2.8 FATAL_ERROR)
add_definitions("-std=c++11 -Wall -Wextra -pedantic")
add_definitions("-Weffc++ -Wnon-virtual-dtor -Wshadow")

project(examples)
set(VERSION "0.1.0")
set(MINIMUM_BOOST_VERSION "1.54")

string(COMPARE EQUAL ${CMAKE_CXX_COMPILER_ID} "GNU" USING_GCC)
string(COMPARE EQUAL ${CMAKE_CXX_COMPILER_ID} "Clang" USING_CLANG)

find_package(Boost ${MINIMUM_BOOST_VERSION} COMPONENTS program_options regex REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)
include_directories(SYSTEM ${Boost_INCLUDE_DIR})

add_executable(primes primes.cxx)
target_link_libraries(primes ${Boost_LIBRARIES})
configure_file(scripts/prime_statistic.py scripts/prime_statistic.py COPYONLY)

add_executable(factorial factorial.cxx)
target_link_libraries(factorial ${Boost_LIBRARIES})

# We don't need to explictly link standard library when using clang
if(!USING_CLANG)
    target_link_libraries(primes stdc++)
    target_link_libraries(factorial stdc++)
endif(!USING_CLANG)

