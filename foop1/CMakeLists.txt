cmake_minimum_required(VERSION 2.8.0)
project(foop1)

set(VERSION 1)

if(NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE Debug)
endif()

find_package(Qt4 REQUIRED)
find_package(QJSON REQUIRED)

include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

set(COMMON_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/common/")
set(COMMON_LIBRARIES "foop1_common")

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_definitions("-Wextra -pedantic -Wno-long-long")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu++11")
endif()

add_subdirectory(client)
add_subdirectory(common)
add_subdirectory(server)

# vim:set ts=4 sw=4 et:
