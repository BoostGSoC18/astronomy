find_package(Boost 1.67.0 COMPONENTS unit_test_framework REQUIRED)

add_executable(Tests test.cpp representation_test.cpp differential_test.cpp)
target_link_libraries(Tests ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(NAME Tests COMMAND Tests)
