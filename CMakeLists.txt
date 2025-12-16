cmake_minimum_required(VERSION 3.16)
project(webapp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
else()
    # Linux paths - adjust as needed
    set(WT_INCLUDE_DIRS "/usr/include")
    set(WT_LIBRARY_DIRS "/usr/lib")
endif()

# Find PostgreSQL
find_package(PostgreSQL REQUIRED)

# CRITICAL: Verify Wt headers exist
if(WIN32 AND EXISTS "${WT_INCLUDE_DIRS}/Wt/WApplication.h")
    message(STATUS "✓ Wt headers found at: ${WT_INCLUDE_DIRS}/Wt/")
elseif(WIN32)
    message(FATAL_ERROR "✗ Wt headers NOT found at: ${WT_INCLUDE_DIRS}/Wt/")
endif()

# Debug output
message(STATUS "WT_INCLUDE_DIRS: ${WT_INCLUDE_DIRS}")
message(STATUS "WT_LIBRARY_DIRS: ${WT_LIBRARY_DIRS}")

# List all source files
set(SOURCES
    main.cpp
    DatabaseManager.cpp
    Utils.cpp
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

# CRITICAL FIX: Use target_include_directories instead of include_directories
target_include_directories(webapp PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/routes
    ${CMAKE_CURRENT_SOURCE_DIR}/widgets
    ${WT_INCLUDE_DIRS}
    ${PostgreSQL_INCLUDE_DIRS}
)

# Link directories
target_link_directories(webapp PRIVATE ${WT_LIBRARY_DIRS})

# Link libraries
if(WIN32)
    target_link_libraries(webapp PRIVATE
        # Wt libraries
        wt.lib
        wthttp.lib
        
        # PostgreSQL
        ${PostgreSQL_LIBRARIES}
        
        # Windows system libraries (CRITICAL for resolving linker errors)
        ws2_32.lib      # Windows Sockets
        advapi32.lib    # Security/Registry
        shell32.lib     # Shell API
        user32.lib      # User Interface
        gdi32.lib       # Graphics Device Interface
        
        # Additional libraries often needed
        ole32.lib       # OLE
        oleaut32.lib    # OLE Automation  
        uuid.lib        # UUID/GUID
    )
else()
    target_link_libraries(webapp PRIVATE
        wt
        wthttp
        ${PostgreSQL_LIBRARIES}
        pthread
    )
endif()

# Optional: Add debug info for include paths
get_target_property(INCLUDES webapp INCLUDE_DIRECTORIES)
message(STATUS "Final include directories for webapp: ${INCLUDES}")