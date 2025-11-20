cmake_minimum_required(VERSION 3.16)
project(webapp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set vcpkg toolchain
set(CMAKE_TOOLCHAIN_FILE "D:/vcpkg/scripts/buildsystems/vcpkg.cmake")

# Find PostgreSQL
find_package(PostgreSQL REQUIRED)

# Include directories
include_directories("D:/vcpkg/installed/x64-windows/include")
include_directories(${PostgreSQL_INCLUDE_DIRS})

# Link directories  
link_directories("D:/vcpkg/installed/x64-windows/lib")

# Create executable
add_executable(webapp main.cpp DatabaseManager.cpp)

# Link libraries
target_link_libraries(webapp 
    wt
    wthttp
    libpq
    ws2_32
)