##UNVERIFIED
cmake_minimum_required(VERSION 3.14)
project(myproject LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set compiler warnings
add_compile_options(-Wall)

# Find dependencies
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBEVDEV REQUIRED IMPORTED_TARGET libevdev)

# Define executable
add_executable(bin
    src/main.cpp
    src/profileNix.cpp
    src/profileManagerNix.cpp
    src/virtualDeviceNix.cpp
)

# Include directories
target_include_directories(bin PRIVATE include)

# Link libraries
target_link_libraries(bin
    PkgConfig::LIBEVDEV
    wiiuse
    bluetooth
    m
)