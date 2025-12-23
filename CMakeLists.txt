cmake_minimum_required(VERSION 3.16)
project(webapp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable debug symbols
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")


# Conditionally set vcpkg toolchain for Windows
if(WIN32)
    set(CMAKE_TOOLCHAIN_FILE "H:/vcpkg/scripts/buildsystems/vcpkg.cmake")
endif()

# Set paths
if(WIN32)
    set(VCPKG_ROOT "H:/vcpkg")
    set(VCPKG_TARGET "x64-windows")
    set(WT_INCLUDE_DIRS "${VCPKG_ROOT}/installed/${VCPKG_TARGET}/include")
    set(WT_LIBRARY_DIRS "${VCPKG_ROOT}/installed/${VCPKG_TARGET}/lib")
    
    # PostgreSQL library path
    set(POSTGRESQL_LIBRARY "${VCPKG_ROOT}/installed/${VCPKG_TARGET}/lib/libpq.lib")
else()
    set(WT_INCLUDE_DIRS "/usr/include")
    set(WT_LIBRARY_DIRS "/usr/lib")
endif()

# CRITICAL: Verify Wt headers exist
if(WIN32 AND EXISTS "${WT_INCLUDE_DIRS}/Wt/WApplication.h")
    message(STATUS "✓ Wt headers found at: ${WT_INCLUDE_DIRS}/Wt/")
elseif(WIN32)
    message(FATAL_ERROR "✗ Wt headers NOT found at: ${WT_INCLUDE_DIRS}/Wt/")
endif()

message(STATUS "WT_INCLUDE_DIRS: ${WT_INCLUDE_DIRS}")
message(STATUS "WT_LIBRARY_DIRS: ${WT_LIBRARY_DIRS}")

# List all source files
set(SOURCES
    main.cpp
    DatabaseManager.cpp
    Utils.cpp
    PasswordUtils.cpp
    routes/RouteManager.cpp
    widgets/DashboardWidget.cpp
    widgets/LoginWidget.cpp
    widgets/dash.cpp
    widgets/UsersList.cpp
    widgets/UsersAdd.cpp
    widgets/SecuritySettings.cpp
)

# Create executable
add_executable(webapp ${SOURCES})

# Include directories
target_include_directories(webapp PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/routes
    ${CMAKE_CURRENT_SOURCE_DIR}/widgets
    ${WT_INCLUDE_DIRS}
)

# Link directories
target_link_directories(webapp PRIVATE ${WT_LIBRARY_DIRS})

# Link libraries - CRITICAL FIX: Add libpq.lib
if(WIN32)
    target_link_libraries(webapp PRIVATE
        # Wt libraries
        wt
        wthttp
        
        # PostgreSQL library (CRITICAL)
        libpq
        
        # Windows system libraries
        ws2_32
        advapi32
        shell32
        user32
        gdi32
        ole32
        oleaut32
        kernel32
        uuid
    )
else()
    target_link_libraries(webapp PRIVATE
        wt
        wthttp
        pq  # PostgreSQL on Linux
        pthread
    )
endif()

get_target_property(INCLUDES webapp INCLUDE_DIRECTORIES)
message(STATUS "Final include directories for webapp: ${INCLUDES}")