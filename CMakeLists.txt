cmake_minimum_required(VERSION 3.10)
project(DO178B_CyberSecurity_Logging)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/src)

add_library(logger 
    src/modules/logging/logger.cpp
    src/modules/logging/logger.h
)

add_library(access_control
    src/modules/access_control/access_control.cpp
    src/modules/access_control/access_control.h
)

add_library(comms
    src/modules/communication/comms.cpp
    src/modules/communication/comms.h
)

add_library(crypto_utils
    src/utils/crypto_utils.cpp
    src/utils/crypto_utils.h
)

add_executable(DO178B_CyberSecurity_Logging
    src/main.cpp
)

target_link_libraries(DO178B_CyberSecurity_Logging
    logger
    access_control
    comms
    crypto_utils
)

enable_testing()

# Unit tests
add_executable(test_logger tests/unit/test_logger.cpp)
target_link_libraries(test_logger logger crypto_utils)

add_executable(test_access_control tests/unit/test_access_control.cpp)
target_link_libraries(test_access_control access_control crypto_utils)

add_executable(test_comms tests/unit/test_comms.cpp)
target_link_libraries(test_comms comms crypto_utils)

# Integration tests
add_executable(test_logging_comms tests/integration/test_logging_comms.cpp)
target_link_libraries(test_logging_comms logger comms access_control crypto_utils)

add_test(NAME TestLogger COMMAND test_logger)
add_test(NAME TestAccessControl COMMAND test_access_control)
add_test(NAME TestComms COMMAND test_comms)
add_test(NAME TestLoggingComms COMMAND test_logging_comms)
