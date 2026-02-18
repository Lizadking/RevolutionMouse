cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

project(revMouse VERSION 0.1)
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wall -g -fdiagnostics-color=always")
set(CMAKE_COLOR_DIAGNOSTICS ON)

# Find pkg-config module
find_package(PkgConfig REQUIRED)

#-----WIIUSE CONFIG ---------------------------
set(WIIUSE_VERSION 0.15.6)
FetchContent_Declare(
    wiiuse
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    URL https://github.com/wiiuse/wiiuse/archive/refs/tags/0.15.6.tar.gz
    FIND_PACKAGE_ARGS ${WIIUSE_VERSION} EXACT
)
set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(wiiuse)

#---------------------------------------------

#------------imgui config-------------------
set(IMGUI_VERSION 1.92.5)
FetchContent_Declare(
  imgui
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
  URL https://github.com/ocornut/imgui/archive/refs/tags/v1.92.5.tar.gz
  FIND_PACKAGE_ARGS  ${IMGUI_VERSION} EXACT
)
set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(imgui)

#------------------------------------------

#-----------Opengl config---------------------
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED) 
#---------------------------------------------
# Use pkg-config to find libevdev
pkg_check_modules(LIBEVDEV REQUIRED IMPORTED_TARGET libevdev)

# Globbing files for main build 
#file(GLOB_RECURSE SRC_FILES src/*.cpp)
set(SRC_FILES 
src/main.cpp 
src/monitor.cpp
src/profileManagerNix.cpp
src/profileNix.cpp
src/virtualDeviceNix.cpp
src/glad.c
)

# Globbing files for test SDL build
set(SDL_TEST_FILES 
src/sdltest.cpp
src/monitor.cpp
src/profileManagerNix.cpp
src/profileNix.cpp
src/virtualDeviceNix.cpp
src/glad.c
)

# Create the main binary
add_executable(${PROJECT_NAME} ${SRC_FILES})

#create SDL test binary
add_executable(sdltest ${SDL_TEST_FILES})

#--- MAIN BINARY LINKING ---------------
# Imgui linking
target_sources(${PROJECT_NAME} PRIVATE
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp # Or your chosen backend, e.g., SDL
)

target_include_directories(${PROJECT_NAME} PRIVATE ${imgui_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${imgui_SOURCE_DIR}/backends)

# Use the imported target for includes and linking
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
   
)
target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::LIBEVDEV wiiuse OpenGL::GL glfw)
#---------------------------------------


#----SDL TEST BINARY LINKING------------
# Imgui linking
target_sources(sdltest PRIVATE
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp # Or your chosen backend, e.g., SDL
)

target_include_directories(sdltest PRIVATE ${imgui_SOURCE_DIR})
target_include_directories(sdltest PRIVATE ${imgui_SOURCE_DIR}/backends)

target_include_directories(sdltest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(sdltest PRIVATE PkgConfig::LIBEVDEV wiiuse  OpenGL::GL glfw)
#----------------------------------------
