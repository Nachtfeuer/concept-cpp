cmake_minimum_required (VERSION 2.8 FATAL_ERROR)
add_definitions("-std=c++11 -Wall -Wextra -pedantic -Weffc++ -Wnon-virtual-dtor")

project(concept)
set(VERSION "0.17.0")
set(MINIMUM_BOOST_VERSION "1.54")
enable_testing()

option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" OFF)

find_program(GCOV gcov)
find_program(LCOV lcov)
find_program(GCOVR gcovr)
find_program(GENHTML genhtml)
find_program(CPPCHECK cppcheck)
find_package(Doxygen)
find_package(Boost ${MINIMUM_BOOST_VERSION} COMPONENTS program_options regex REQUIRED)

include_directories(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${PROJECT_NAME} SYSTEM ${Boost_INCLUDE_DIR})

file(GLOB TEST_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/test*.cxx)

add_executable(${PROJECT_NAME} src/main.cxx ${TEST_SRC})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME} stdc++)
add_test(test ${PROJECT_NAME})

if(LCOV)
    message("-- Found LCOV: ${LCOV}")
endif(LCOV)

if(GCOVR)
    message("-- Found GCOVR: ${GCOVR}")
endif(GCOVR)

if(GCOV)
    message("-- Found GCOV: ${GCOV}")
    add_definitions("--coverage -fprofile-arcs -ftest-coverage")
    target_link_libraries(${PROJECT_NAME} gcov)
endif(GCOV)

if(GENHTML)
    message("-- Found GENHTML: ${GENHTML}")
endif(GENHTML)

if(CPPCHECK)
    message("-- Found CPPCHECK: ${CPPCHECK}")
endif(CPPCHECK)

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
add_custom_target(memcheck COMMAND valgrind --leak-check=full ${CMAKE_BINARY_DIR}/${PROJECT_NAME}
                  DEPENDS ${PROJECT_NAME})
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



