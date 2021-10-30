# ------------------------------------------------------------
# Main Settings
cmake_minimum_required(VERSION 3.1...3.15)
project(halloween)
set(BINARY halloween)

# ------------------------------------------------------------
# Language Standards
enable_language(C CXX ASM)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ------------------------------------------------------------
# Packages
find_package(Threads REQUIRED)

# ------------------------------------------------------------
# Source Files
set(SOURCES
    ${CMAKE_SOURCE_DIR}/source/main.cpp
    ${CMAKE_SOURCE_DIR}/source/character.cpp
    ${CMAKE_SOURCE_DIR}/source/config_parser.cpp
    ${CMAKE_SOURCE_DIR}/source/font_renderer.cpp
    ${CMAKE_SOURCE_DIR}/source/scrolling_font_renderer.cpp
    ${CMAKE_SOURCE_DIR}/source/font.cpp
    ${CMAKE_SOURCE_DIR}/source/primatives.cpp
    ${CMAKE_SOURCE_DIR}/source/animation.cpp
)


# ------------------------------------------------------------
# Main Binary
add_executable(${BINARY} ${SOURCES})

# ------------------------------------------------------------
# Includes
target_include_directories(${BINARY} PRIVATE
    ${CMAKE_SOURCE_DIR}/source
    ${CMAKE_SOURCE_DIR}/modules/json/include
    ${CMAKE_SOURCE_DIR}/modules/range-v3/include
    ${CMAKE_SOURCE_DIR}/modules/fmt/include
    ${CMAKE_SOURCE_DIR}/modules/bitmap
)

# ------------------------------------------------------------
# Submodules
add_subdirectory(modules)
add_subdirectory(modules/json)
add_subdirectory(modules/range-v3)
add_subdirectory(modules/fmt)

# ------------------------------------------------------------
# Build Settings

# Link libraries
target_link_libraries(${BINARY} rpi-rgb-led-matrix Threads::Threads)

# Compiler flags
target_compile_options(${BINARY} PRIVATE
    -O2
    -g0
    -Wall
    -Wextra
    -c
    -fmessage-length=0 
    -fdata-sections 
    -ffunction-sections
    -Wno-psabi
)

# Linker flags
target_link_options(${BINARY} PRIVATE
    -Wl,--gc-sections
    -Wl,--strip-all
)
