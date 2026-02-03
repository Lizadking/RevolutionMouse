## NONE OF THIS HAS BEEN VERIFIED 
cmake_minimum_required(VERSION 3.10)
project(MyProject C CXX)  # Enable both C and C++

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Find required packages
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBEVDEV REQUIRED libevdev)

# Find libraries
find_library(WIIUSE_LIB wiiuse)
find_library(BLUETOOTH_LIB bluetooth)

# Set source files
set(SOURCES
    src/main.cpp
    src/profileNix.cpp
    src/profileManagerNix.cpp
    src/virtualDeviceNix.cpp
    src/main.c
    src/monitor.c
)

# Header files (optional, for IDEs)
set(HEADERS
    include/profileNix.h
    include/profileManagerNix.h
    include/virtualDeviceNix.h
    include/wiiusehelper.h
    include/fileio.h
    include/monitor.h
)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Set include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    include
    ${LIBEVDEV_INCLUDE_DIRS}
)

# Set compile flags for both C and C++
target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
    $<$<COMPILE_LANGUAGE:CXX>:-std=c++11>
    $<$<COMPILE_LANGUAGE:C>:-std=c11>
)

# Link libraries
target_link_libraries(${PROJECT_NAME}
    ${LIBEVDEV_LIBRARIES}
    ${WIIUSE_LIB}
    ${BLUETOOTH_LIB}
    m
)

# Handle pkg-config link directories
if(LIBEVDEV_LINK_DIRECTORIES)
    target_link_directories(${PROJECT_NAME} PRIVATE ${LIBEVDEV_LINK_DIRECTORIES})
endif()

# Install target (optional)
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

# Custom targets
add_custom_target(run
    COMMAND ./${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running ${PROJECT_NAME}"
)

# Clean target
add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}
    COMMENT "Removing build directory"
)

# Set output directory (optional)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)