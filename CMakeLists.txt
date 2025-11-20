cmake_minimum_required(VERSION 3.16)
project(webapp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Conditionally set vcpkg toolchain for Windows
if(WIN32)
    set(CMAKE_TOOLCHAIN_FILE "D:/vcpkg/scripts/buildsystems/vcpkg.cmake")
endif()

# Platform-specific PostgreSQL configuration
if(WIN32)
    find_package(PostgreSQL REQUIRED)
else()
    # Manual PostgreSQL configuration for Linux
    execute_process(
        COMMAND pg_config --includedir
        OUTPUT_VARIABLE PG_INCLUDE_DIR
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    execute_process(
        COMMAND pg_config --libdir
        OUTPUT_VARIABLE PG_LIB_DIR
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    
    set(PostgreSQL_INCLUDE_DIRS ${PG_INCLUDE_DIR})
    set(PostgreSQL_LIBRARIES pq)
    
    message(STATUS "PostgreSQL include dir: ${PG_INCLUDE_DIR}")
    message(STATUS "PostgreSQL lib dir: ${PG_LIB_DIR}")
endif()

# Include directories
if(WIN32)
    include_directories("D:/vcpkg/installed/x64-windows/include")
    link_directories("D:/vcpkg/installed/x64-windows/lib")
else()
    include_directories(${PostgreSQL_INCLUDE_DIRS})
    link_directories(${PG_LIB_DIR})
endif()

# Create executable
add_executable(webapp main.cpp DatabaseManager.cpp)

# Link libraries
target_link_libraries(webapp ${PostgreSQL_LIBRARIES})

if(WIN32)
    target_link_libraries(webapp 
        wt
        wthttp
        ws2_32
    )
else()
    target_link_libraries(webapp 
        wt
        wthttp
    )
endif()