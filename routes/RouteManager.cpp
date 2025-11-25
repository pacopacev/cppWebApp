#include "RouteManager.h"
#include "../widgets/LoginWidget.h"
#include "../widgets/DashboardWidget.h"
#include <iostream>

RouteManager::RouteManager(Wt::WApplication* app) 
    : app_(app) {
    
    // Create main content area
    contentArea_ = app_->root()->addWidget(std::make_unique<Wt::WContainerWidget>());
    contentArea_->setStyleClass("content-area");
}

void RouteManager::setupRoutes() {
    std::cout << "Setting up routes" << std::endl;
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
    
    if (path == "/dashboard") {
        if (!isAuthenticated()) {
            std::cout << "Not authenticated, redirecting to login" << std::endl;
            navigateTo("/login");
            showLogin();
        } else {
            showDashboard();
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
    
    auto loginWidget = contentArea_->addWidget(std::make_unique<LoginWidget>());
    
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

void RouteManager::showDashboard() {
    std::cout << "Showing dashboard for user: " << getLoggedUser() << std::endl;
    
    auto dashboardWidget = contentArea_->addWidget(std::make_unique<DashboardWidget>(getLoggedUser()));
    
    // Connect logout signal using lambda
    dashboardWidget->logoutRequested().connect([this]() {
        std::cout << "Logout requested" << std::endl;
        setLoggedUser("");
        navigateTo("/login");
    });
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