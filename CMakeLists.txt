cmake_minimum_required (VERSION 2.8 FATAL_ERROR)
add_definitions("-Wall -Wextra -std=c++11")

project(demo)
set(VERSION "0.1")
enable_testing()

option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" OFF)

find_program(GCOV gcov)
find_program(LCOV lcov)
find_program(GENHTML genhtml)
find_package(Doxygen)

include_directories(demo ${CMAKE_CURRENT_SOURCE_DIR}/include)
file(GLOB DEMO_TEST_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/test*.cxx)
add_executable(demo src/main.cxx ${DEMO_TEST_SRC})
add_test(test demo)

if(LCOV)
    message("-- Found LCOV: ${LCOV}")
endif(LCOV)

if(GCOV)
    message("-- Found GCOV: ${GCOV}")
    add_definitions("--coverage -fprofile-arcs -ftest-coverage")
    target_link_libraries(demo gcov)
endif(GCOV)

if(GENHTML)
    message("-- Found GENHTML: ${GENHTML}")
endif(GENHTML)

install(DIRECTORY include/math DESTINATION include/demo)
install(DIRECTORY include/pattern DESTINATION include/demo)
install(DIRECTORY include/unittest DESTINATION include/demo)

configure_file(README.package README.package COPYONLY)
configure_file(doc/doxygen.cfg doc/doxygen.cfg)

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

if(BUILD_DOCUMENTATION)
    if(DOXYGEN_FOUND)
        add_custom_target(doc
            ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/doc/doxygen.cfg
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen" VERBATIM)
    endif(DOXYGEN_FOUND)
endif(BUILD_DOCUMENTATION)

# check command workaround that 'test' does not build the binary.
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} DEPENDS demo)
add_custom_target(run COMMAND demo DEPENDS demo)
add_custom_target(memcheck COMMAND valgrind --leak-check=full ${CMAKE_BINARY_DIR}/demo DEPENDS demo)

if(GCOV)
    add_custom_target(coverage 
           COMMAND mkdir -p ${CMAKE_BINARY_DIR}/coverage
           COMMAND ${LCOV} --capture
                           --no-external
                           --base-directory ${CMAKE_CURRENT_SOURCE_DIR}
                           --directory=${CMAKE_CURRENT_BINARY_DIR}
                           --output-file=${CMAKE_BINARY_DIR}/coverage/coverage.info
           COMMAND ${GENHTML} ${CMAKE_BINARY_DIR}/coverage/coverage.info
                           --title ${PROJECT_NAME}
                           --legend
                           --output-directory ${CMAKE_BINARY_DIR}/coverage
           DEPENDS run)
endif(GCOV)


