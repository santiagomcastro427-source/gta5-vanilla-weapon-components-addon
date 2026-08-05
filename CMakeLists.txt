cmake_minimum_required(VERSION 3.10)
project(VanillaWeaponComponentsAddon)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Platform detection
if(WIN32)
    set(PLATFORM_WINDOWS TRUE)
    message(STATUS "Building for Windows")
else()
    message(FATAL_ERROR "This project only supports Windows/GTA V")
endif()

# Project configuration
set(PROJECT_VERSION "1.0.0")
set(ADDON_NAME "VanillaWeaponComponentsAddon")

# Add source files
set(SOURCE_FILES
    src/VanillaWeaponComponentsAddon.cpp
    src/WeaponComponentLoader.cpp
    src/LaserSightComponent.cpp
)

set(HEADER_FILES
    src/VanillaWeaponComponentsAddon.h
    src/WeaponComponentLoader.h
    src/LaserSightComponent.h
    include/gta/weapon_components.h
)

# Create DLL for ASI loading
add_library(${ADDON_NAME} SHARED ${SOURCE_FILES} ${HEADER_FILES})

# Set output directory
set_target_properties(${ADDON_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    PREFIX ""
    SUFFIX ".dll"
)

# Include directories
target_include_directories(${ADDON_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)

# Compiler flags
if(MSVC)
    target_compile_options(${ADDON_NAME} PRIVATE
        /W4
        /WX
        /EHsc
        /Oi
        /Ot
    )
endif()

# Define preprocessor macros
target_compile_definitions(${ADDON_NAME} PRIVATE
    _WIN32_WINNT=0x0601
    NOMINMAX
    WIN32_LEAN_AND_MEAN
)

message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Version: ${PROJECT_VERSION}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")