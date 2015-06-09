cmake_minimum_required (VERSION 2.8 FATAL_ERROR)

project(concept)
set(VERSION "0.27.0")
set(MINIMUM_BOOST_VERSION "1.54")

option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" OFF)

string(COMPARE EQUAL ${CMAKE_CXX_COMPILER_ID} "GNU" USING_GCC)
string(COMPARE EQUAL ${CMAKE_CXX_COMPILER_ID} "Clang" USING_CLANG)

find_program(GCOV gcov)
find_program(LCOV lcov)
find_program(GCOVR gcovr)
find_program(GENHTML genhtml)
find_program(CPPCHECK cppcheck)
find_program(VALGRIND valgrind)

find_package(Doxygen)
find_package(Boost ${MINIMUM_BOOST_VERSION} COMPONENTS program_options regex REQUIRED)

include_directories(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${PROJECT_NAME} SYSTEM ${Boost_INCLUDE_DIR})

file(GLOB TEST_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/test*.cxx)

add_definitions("-std=c++11 -Wall -Wextra -pedantic")
add_definitions("-Weffc++ -Wnon-virtual-dtor -Wshadow")
add_definitions("-DVERSION=\"${VERSION}\"")

add_executable(${PROJECT_NAME} src/main.cxx ${TEST_SRC})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

# We don't need to explictly link standard library when using clang
if(!USING_CLANG)
    target_link_libraries(${PROJECT_NAME} stdc++)
endif(!USING_CLANG)

enable_testing()
add_test(test ${PROJECT_NAME})

add_subdirectory(examples)

if(LCOV)
    message("-- Found LCOV: ${LCOV}")
endif(LCOV)

if(GCOVR)
    message("-- Found GCOVR: ${GCOVR}")
endif(GCOVR)

if(GCOV)
    message("-- Found GCOV: ${GCOV}")
    set(COVERAGE_FLAGS "-fprofile-arcs -ftest-coverage")
    # Setting up gcc coverage flags and libraries
    if(USING_GCC)
        set(COVERAGE_FLAGS "--coverage ${COVERAGE_FLAGS}")
        target_link_libraries(${PROJECT_NAME} gcov)
    endif(USING_GCC)
    # Setting up clang coverage linger flags
    if(USING_CLANG)
        set(PROFILE_LINK_FLAGS "${LINK_FLAGS} ${COVERAGE_FLAGS}")
        set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS ${PROFILE_LINK_FLAGS})
    endif(USING_CLANG)
    # Adding definitions
    add_definitions(${COVERAGE_FLAGS})
endif(GCOV)

if(GENHTML)
    message("-- Found GENHTML: ${GENHTML}")
endif(GENHTML)

if(CPPCHECK)
    message("-- Found CPPCHECK: ${CPPCHECK}")
endif(CPPCHECK)

if(VALGRIND)
    message("-- Found VALGRIND: ${VALGRIND}")
endif(VALGRIND)

install(DIRECTORY include/math         DESTINATION include/${PROJECT_NAME})
install(DIRECTORY include/pattern      DESTINATION include/${PROJECT_NAME})
install(DIRECTORY include/types        DESTINATION include/${PROJECT_NAME})
install(DIRECTORY include/unittest     DESTINATION include/${PROJECT_NAME})
install(DIRECTORY include/algorithm    DESTINATION include/${PROJECT_NAME})
install(DIRECTORY include/matcher      DESTINATION include/${PROJECT_NAME})
install(DIRECTORY include/query        DESTINATION include/${PROJECT_NAME})
install(DIRECTORY include/generator    DESTINATION include/${PROJECT_NAME})
install(DIRECTORY include/document     DESTINATION include/${PROJECT_NAME})

configure_file(README.package README.package COPYONLY)
configure_file(CHANGELOG CHANGELOG COPYONLY)
configure_file(doc/doxygen.cfg doc/doxygen.cfg)

set(CPACK_GENERATOR "RPM")
set(CPACK_PACKAGE_VERSION ${VERSION})
set(CPACK_PACKAGE_RELEASE 1)
set(CPACK_PACKAGE_CONTACT "Thomas Lehmann")
set(CPACK_PACKAGE_VENDOR "Private")
set(CPACK_RPM_PACKAGE_GROUP "C++ Development Library")
set(CPACK_RPM_PACKAGE_LICENSE "MIT License")
set(CPACK_RPM_PACKAGE_URL "https://github.com/Nachtfeuer/concept-cpp")
set(CPACK_PACKAGE_DESCRIPTION_FILE ${CMAKE_BINARY_DIR}/README.package)
set(CPACK_RPM_CHANGELOG_FILE ${CMAKE_BINARY_DIR}/CHANGELOG)
set(CPACK_RPM_PACKAGE_ARCHITECTURE "noarch")
set(CPACK_RPM_PACKAGE_REQUIRES "Boost >= ${MINIMUM_BOOST_VERSION}")
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
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} DEPENDS ${PROJECT_NAME})
add_custom_target(run COMMAND ${PROJECT_NAME} DEPENDS ${PROJECT_NAME})

if(VALGRIND)
    add_custom_target(memcheck COMMAND valgrind
                      --leak-check=full --leak-resolution=high --show-leak-kinds=all --track-origins=yes
                      ${CMAKE_BINARY_DIR}/${PROJECT_NAME} DEPENDS ${PROJECT_NAME})
endif(VALGRIND)

add_custom_target(clear-coverage
    COMMAND find ${CMAKE_BINARY_DIR} -name "*.gcno" | xargs -i rm -f {}
    COMMAND find ${CMAKE_BINARY_DIR} -name "*.gcda" | xargs -i rm -f {})

if(GCOV AND LCOV AND GENHTML AND GCOVR)
    add_custom_target(coverage
           COMMAND mkdir -p ${CMAKE_BINARY_DIR}/coverage
           COMMAND ${LCOV} --capture
                           --no-external
                           --rc lcov_branch_coverage=1
                           --base-directory ${CMAKE_CURRENT_SOURCE_DIR}
                           --directory=${CMAKE_CURRENT_BINARY_DIR}
                           --output-file=${CMAKE_BINARY_DIR}/coverage/coverage.info
           COMMAND ${GENHTML} ${CMAKE_BINARY_DIR}/coverage/coverage.info
                           --title ${PROJECT_NAME}
                           --legend
                           --show-details
                           --function-coverage
                           --branch-coverage
                           --output-directory ${CMAKE_BINARY_DIR}/coverage
            COMMAND ${GCOVR}
                           --root=${CMAKE_CURRENT_SOURCE_DIR}
                           --object-directory=${CMAKE_BINARY_DIR}
                           --xml-pretty > ${CMAKE_BINARY_DIR}/coverage.xml
            DEPENDS run)
endif(GCOV AND LCOV AND GENHTML AND GCOVR)

if(CPPCHECK)
    add_custom_target(cppcheck
        COMMAND ${CPPCHECK} -I${CMAKE_CURRENT_SOURCE_DIR}/include
                            --enable=all
                            --std=c++11
                            ${CMAKE_CURRENT_SOURCE_DIR})
endif(CPPCHECK)

