cmake_minimum_required(VERSION 3.10)
project(WebApp)

set(CMAKE_CXX_STANDARD 17)

# Find required packages
find_package(PkgConfig)

pkg_search_module(WTHTTP REQUIRED wthttp)
pkg_search_module(WT REQUIRED wt)
pkg_search_module(BOOST REQUIRED boost_system)

# Create executable
add_executable(webapp main.cpp MemoryMonitor.cpp)

# Link libraries
target_link_libraries(webapp ${WTHTTP_LIBRARIES} ${WT_LIBRARIES} ${BOOST_LIBRARIES})
target_include_directories(webapp PRIVATE ${WTHTTP_INCLUDE_DIRS} ${WT_INCLUDE_DIRS})
target_compile_options(webapp PRIVATE ${WTHTTP_CFLAGS_OTHER} ${WT_CFLAGS_OTHER})