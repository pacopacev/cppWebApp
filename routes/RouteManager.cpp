#include "RouteManager.h"
#include "../widgets/LoginWidget.h"
#include "../widgets/DashboardWidget.h"
#include <iostream>

RouteManager::RouteManager(Wt::WApplication* app, DatabaseManager& dbManager) 
    : app_(app), dbManager_(dbManager) {
    
    contentArea_ = app_->root()->addWidget(std::make_unique<Wt::WContainerWidget>());
    contentArea_->setStyleClass("content-area");
}

void RouteManager::setupRoutes() {
    // Connect to internal path changes using lambda
    app_->internalPathChanged().connect([this] {
        handleRoute(app_->internalPath());
    });
    
    // Handle initial route
    handleRoute(app_->internalPath());
}

void RouteManager::navigateTo(const std::string& path) {
    app_->setInternalPath(path, true);
}

void RouteManager::setAuthCheckCallback(AuthCheckCallback callback) {
    authCheckCallback_ = callback;
}

void RouteManager::setUserGetterCallback(UserGetterCallback callback) {
    userGetterCallback_ = callback;
}

void RouteManager::setUserSetterCallback(UserSetterCallback callback) {
    userSetterCallback_ = callback;
}

void RouteManager::handleRoute(const std::string& path) {
    std::cout << "Routing to: " << path << std::endl;
    
    contentArea_->clear();
    
    // Check for dashboard routes
    if (path == "/dashboard" || 
        path == "/dashboard/users" ||
        path == "/dashboard/users/add" ||
        path == "/dashboard/settings/profile" ||
        path == "/dashboard/settings/security" ||
        path == "/dashboard/reports/daily" ||
        path == "/dashboard/reports/monthly") {
        
        if (!isAuthenticated()) {
            std::cout << "Not authenticated, redirecting to login" << std::endl;
            navigateTo("/login");
            showLogin();
        } else {
            showDashboard(path);
        }
    } else if (path == "/login") {
        showLogin();
    } else if (path.empty() || path == "/") {
        navigateTo("/login");
    } else {
        showNotFound();
    }
}

void RouteManager::showLogin() {
    std::cout << "Showing login page" << std::endl;
    
    // ✅ CORRECT: Use direct construction
    auto loginWidget = new LoginWidget(dbManager_);
    contentArea_->addWidget(std::unique_ptr<LoginWidget>(loginWidget));
    
    // Connect login success signal using lambda
    loginWidget->loginSuccess().connect([this](const std::string& username) {
        std::cout << "Login successful for user: " << username << std::endl;
        setLoggedUser(username);
        navigateTo("/dashboard");
    });
    
    // Connect login failed signal using lambda
    loginWidget->loginFailed().connect([this](const std::string& message) {
        std::cout << "Login failed: " << message << std::endl;
        // Error handling would be implemented in LoginWidget
    });
}

void RouteManager::showDashboard(const std::string& path) {
    std::cout << "Showing dashboard for user: " << getLoggedUser() << " at path: " << path << std::endl;
    
    auto dashboardWidget = contentArea_->addWidget(std::make_unique<DashboardWidget>(getLoggedUser()));
    
    // Connect logout signal using lambda
    dashboardWidget->logoutRequested().connect([this]() {
        std::cout << "Logout requested" << std::endl;
        setLoggedUser("");
        navigateTo("/login");
    });
    
    // Connect menu selection signal to handle navigation
    dashboardWidget->menuItemSelected().connect([this](const std::string& section) {
        handleDashboardMenu(section);
    });
    
    // Set the initial content based on the path
    std::string section = getSectionFromPath(path);
    dashboardWidget->setActiveSection(section);
}

void RouteManager::handleDashboardMenu(const std::string& section) {
    std::cout << "Dashboard menu selected: " << section << std::endl;
    
    // Map section names to routes
    std::map<std::string, std::string> routeMap = {
        {"dashboard", "/dashboard"},
        {"users_list", "/dashboard/users"},
        {"users_add", "/dashboard/users/add"},
        {"profile", "/dashboard/settings/profile"},
        {"security", "/dashboard/settings/security"},
        {"report_daily", "/dashboard/reports/daily"},
        {"report_monthly", "/dashboard/reports/monthly"}
    };
    
    auto it = routeMap.find(section);
    if (it != routeMap.end()) {
        navigateTo(it->second);
    }
}

std::string RouteManager::getSectionFromPath(const std::string& path) {
    if (path == "/dashboard") return "dashboard";
    if (path == "/dashboard/users") return "users_list";
    if (path == "/dashboard/users/add") return "users_add";
    if (path == "/dashboard/settings/profile") return "profile";
    if (path == "/dashboard/settings/security") return "security";
    if (path == "/dashboard/reports/daily") return "report_daily";
    if (path == "/dashboard/reports/monthly") return "report_monthly";
    return "dashboard"; // default
}

void RouteManager::showNotFound() {
    contentArea_->addWidget(std::make_unique<Wt::WText>("Page not found: " + app_->internalPath()));
}

bool RouteManager::isAuthenticated() {
    if (authCheckCallback_) {
        return authCheckCallback_();
    }
    return !getLoggedUser().empty();
}

std::string RouteManager::getLoggedUser() {
    if (userGetterCallback_) {
        return userGetterCallback_();
    }
    return "";
}

void RouteManager::setLoggedUser(const std::string& user) {
    if (userSetterCallback_) {
        userSetterCallback_(user);
    }
}