cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

project(revMouse VERSION 0.1)


# Find pkg-config module
find_package(PkgConfig REQUIRED)

#-----Wiiuse config---------------------------
set(WIIUSE_VERSION 0.15.6)
FetchContent_Declare(
    wiiuse
    URL https://github.com/wiiuse/wiiuse/archive/refs/tags/0.15.6.tar.gz
    FIND_PACKAGE_ARGS ${WIIUSE_VERSION} EXACT
)
set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(wiiuse)

#---------------------------------------------

# Use pkg-config to find libevdev
pkg_check_modules(LIBEVDEV REQUIRED IMPORTED_TARGET libevdev)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Use the imported target for includes and linking
target_include_directories(${PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
   
)
target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::LIBEVDEV wiiuse)

