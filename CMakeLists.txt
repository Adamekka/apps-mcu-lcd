cmake_minimum_required(VERSION 3.21)
project(apps-mcu-lcd)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_FLAGS
    "-fsanitize=address -fsanitize=undefined -fstack-protector-strong -Wno-unused-result -Wall -Wextra -Werror=uninitialized -Werror=vla -Werror=return-type -Wshadow -Wnull-dereference -Wformat -Wformat-security -Wstrict-overflow -Wstrict-prototypes -Wcast-align -Wredundant-decls -Wpedantic -Werror -Wno-shadow -Wno-c11-extensions -Wno-cast-align -Wno-unused-parameter"
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(OpenCV QUIET opencv4)

if(NOT OpenCV_FOUND)
    message(FATAL_ERROR "OpenCV library not found!")
endif()

file(GLOB SOURCES src/*.cpp)
add_executable(apps-mcu-lcd ${SOURCES})

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    target_include_directories(apps-mcu-lcd PRIVATE /opt/homebrew/include)
    target_link_directories(apps-mcu-lcd PRIVATE /opt/homebrew/lib)
endif()

target_include_directories(apps-mcu-lcd PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(apps-mcu-lcd PRIVATE ${OpenCV_LIBRARIES})
