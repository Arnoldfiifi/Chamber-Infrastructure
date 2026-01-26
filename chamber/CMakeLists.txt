cmake_minimum_required(VERSION 3.10)
project(chamber)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find PostgreSQL
find_package(PostgreSQL REQUIRED)
include_directories(${PostgreSQL_INCLUDE_DIRS})

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/external)
include_directories(${CMAKE_SOURCE_DIR}/src)

# Collect all source files
file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
)

# Create executable
add_executable(chamber ${SOURCES})

# Link libraries
target_link_libraries(chamber 
    ${PostgreSQL_LIBRARIES}
    pqxx
    pthread
)
