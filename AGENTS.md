# AGENTS.md

## Project Overview
**cppWebApp** is a C++ web application built with the Wt (Web Toolkit) framework, featuring a login system with PostgreSQL database integration. The application provides a cross-platform solution supporting both Windows and Linux environments.

## Recent Changes and Improvements

### Initial Project Setup (Commit: b4ae5e6)
**Date:** 2025-11-20  
**Author:** pacopacev (pgdimitrov@yahoo.com)

#### Core Features Implemented

##### 1. Web Application Framework
- **Wt Framework Integration**: Built on Wt (Web Toolkit) for C++ web development
- **Login Application**: Implemented `LoginApplication` class with user authentication
- **Responsive UI Components**:
  - Username and password input fields with placeholders
  - Login button with click event handling
  - Error/success message display system
  - Company logo display (Flowbit branding)
  - Footer with version information (v0.0.1)

##### 2. Database Management System
- **PostgreSQL Integration**: Full database connectivity via libpq
- **DatabaseManager Class**:
  - Connection management with Aiven cloud PostgreSQL instance
  - User validation with parameterized queries (SQL injection protection)
  - User creation functionality with bcrypt password hashing
  - Platform-specific header includes (Windows/Linux compatibility)
- **Security**: Implemented prepared statements for secure database queries

##### 3. Cross-Platform Build System
- **CMake Configuration**:
  - Minimum CMake version: 3.16
  - C++17 standard compliance
  - Conditional vcpkg toolchain for Windows builds
  - PostgreSQL auto-detection using `pg_config` on Linux
  - Platform-specific library linking (ws2_32 for Windows networking)

##### 4. Build Scripts
- **Windows**: 
  - `build.bat`: Command-line build script
  - `build.ps1`: PowerShell build script with enhanced error handling
  - `run.bat`: Application launcher
- **Linux**:
  - `dev.sh`: Development build and run script

##### 5. Frontend Styling
- **Custom CSS** (`style/style.css`):
  - Modern login form design
  - Responsive layout with container styling
  - Custom input field styling (300x34px dimensions)
  - Error and success message styling
  - Logo and footer positioning

##### 6. Configuration
- **Wt Configuration** (`wt_config.xml`):
  - Web server settings
  - Resource path configuration
  - Application-specific parameters

##### 7. Project Structure
```
cppWebApp/
├── main.cpp                 # Application entry point and UI
├── DatabaseManager.cpp      # Database operations implementation
├── DatabaseManager.h        # Database manager interface
├── CMakeLists.txt          # Build configuration
├── build.bat/build.ps1     # Windows build scripts
├── dev.sh                  # Linux development script
├── run.bat                 # Windows launcher
├── wt_config.xml           # Wt framework configuration
├── style/style.css         # Frontend styling
├── resources/img/          # Image assets (flowbit.png logo)
└── build/                  # Build artifacts directory
```

## Technical Stack
- **Language**: C++17
- **Web Framework**: Wt (Web Toolkit)
- **Database**: PostgreSQL (via libpq)
- **Build System**: CMake 3.16+
- **Package Manager**: vcpkg (Windows)
- **Platforms**: Windows (x64) and Linux

## Database Configuration
- **Provider**: Aiven Cloud PostgreSQL
- **Connection**: SSL-enabled connection to remote database
- **Schema**: Users table with fields for authentication
  - `id` (primary key)
  - `first_name` (username field)
  - `password` (password field)
  - Additional fields: `email`, `password_hash`

## Security Features
- Parameterized SQL queries to prevent SQL injection
- Password hashing with bcrypt (`gen_salt('bf')`)
- Secure password input fields (WPasswordEdit)
- Password clearing after login attempts
- Connection string management

## Development Notes
- The application uses `WPasswordEdit` for secure password input masking
- Database connection is established on application startup
- Error messages are displayed to users for failed login attempts
- Success messages welcome authenticated users
- The main container uses a vertical box layout (WVBoxLayout) with horizontal sub-layouts (WHBoxLayout)

## Future Considerations
- Session management implementation
- User registration interface
- Password reset functionality
- Role-based access control
- Enhanced error logging
- Unit test coverage
- API endpoint expansion
- Mobile responsive design improvements

---

**Last Updated:** 2025-11-20  
**Project Version:** 0.0.1  
**Maintainer:** pgdimitrov@yahoo.com
