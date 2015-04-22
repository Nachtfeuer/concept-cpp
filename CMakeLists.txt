cmake_minimum_required (VERSION 2.8 FATAL_ERROR)
add_definitions("-Wall -Wextra -std=c++11")

project(demo)
set(VERSION "0.1")
enable_testing()

include_directories(demo ${CMAKE_CURRENT_SOURCE_DIR}/include)
file(GLOB DEMO_TEST_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/test*.cxx)
add_executable(demo src/main.cxx ${DEMO_TEST_SRC})
add_test(test demo)

install(DIRECTORY include/math DESTINATION include/demo)
install(DIRECTORY include/pattern DESTINATION include/demo)
install(DIRECTORY include/unittest DESTINATION include/demo)

configure_file(README.package README.package COPYONLY)

set(CPACK_GENERATOR "RPM")
set(CPACK_PACKAGE_VERSION ${VERSION})
set(CPACK_PACKAGE_RELEASE 1)
set(CPACK_PACKAGE_CONTACT "Thomas Lehmann")
set(CPACK_PACKAGE_VENDOR "Private")
set(CPACK_RPM_PACKAGE_GROUP "C++ Development Library")
set(CPACK_RPM_PACKAGE_LICENSE "MIT License")
set(CPACK_PACKAGE_DESCRIPTION_FILE ${CMAKE_BINARY_DIR}/README.package)
set(CPACK_RPM_PACKAGE_REQUIRES "Boost >= 1.55")
include(CPack)

# check command workaround that 'test' does not build the binary.
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} DEPENDS demo)
add_custom_target(run COMMAND demo DEPENDS demo)
add_custom_target(memcheck COMMAND valgrind --leak-check=full ${CMAKE_BINARY_DIR}/demo DEPENDS demo)


