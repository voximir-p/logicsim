cmake_minimum_required(VERSION 3.30)

project(logicsim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
        SFML GIT_REPOSITORY
        https://github.com/SFML/SFML.git
        GIT_TAG 3.1.0
)
set(BUILD_SHARED_LIBS ON)
FetchContent_MakeAvailable(SFML)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE MODULE_SOURCES CONFIGURE_DEPENDS src/*.cppm)

add_executable(logicsim ${SOURCES})
target_sources(logicsim PRIVATE FILE_SET CXX_MODULES FILES ${MODULE_SOURCES})
target_link_libraries(logicsim PRIVATE SFML::Graphics SFML::Window SFML::System)

# Copy DLLs to build directory
add_custom_command(TARGET logicsim POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:logicsim>
        $<TARGET_FILE_DIR:logicsim>
        COMMAND_EXPAND_LISTS
)

# Create a symlink for data directory
add_custom_command(TARGET logicsim POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_SOURCE_DIR}/data
        $<TARGET_FILE_DIR:logicsim>/data
)
