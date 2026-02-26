cmake_minimum_required(VERSION 3.15)
project(wifi_rssi_analyzer_tests)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include GoogleTest
find_package(GTest REQUIRED)

# Source files for testing
set(TEST_SOURCES
    test/wifi_rssi_tests.cpp
)

# Create test executable
add_executable(wifi_rssi_tests ${TEST_SOURCES})

# Link GoogleTest
target_link_libraries(wifi_rssi_tests PRIVATE GTest::GTest GTest::Main)

# Enable testing
enable_testing()
add_test(NAME wifi_rssi_tests COMMAND wifi_rssi_tests)
