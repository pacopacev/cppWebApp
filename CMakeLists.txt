cmake_minimum_required(VERSION 3.16)
project(webapp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories("d:/vcpkg/installed/x64-windows/include")

# Link directories  
link_directories("d:/vcpkg/installed/x64-windows/lib")

# Create executable
add_executable(webapp main.cpp)

# Link with available libraries (no boost_system needed)
target_link_libraries(webapp 
    wt
    wthttp
    boost_filesystem-vc143-mt-x64-1_89
    boost_date_time-vc143-mt-x64-1_89
    boost_thread-vc143-mt-x64-1_89
)