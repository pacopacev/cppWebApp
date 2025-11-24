#ifndef ROUTE_MANAGER_H
#define ROUTE_MANAGER_H

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WString.h>
#include <Wt/WSignal.h>
#include <memory>
#include <functional>
#include <unordered_map>

// Forward declarations
class LoginWidget;
class DashboardWidget;

class RouteManager {
public:
    // Application state callbacks
    using AuthCheckCallback = std::function<bool()>;
    using UserGetterCallback = std::function<std::string()>;
    using UserSetterCallback = std::function<void(const std::string&)>;
    
    RouteManager(Wt::WApplication* app);
    
    // Setup routes and connect signals
    void setupRoutes();
    
    // Navigation
    void navigateTo(const std::string& path);
    
    // Register application state callbacks
    void setAuthCheckCallback(AuthCheckCallback callback);
    void setUserGetterCallback(UserGetterCallback callback);
    void setUserSetterCallback(UserSetterCallback callback);

private:
    Wt::WApplication* app_;
    Wt::WContainerWidget* contentArea_;
    
    // Application state callbacks
    AuthCheckCallback authCheckCallback_;
    UserGetterCallback userGetterCallback_;
    UserSetterCallback userSetterCallback_;
    
    // Route handlers
    void handleRoute(const std::string& path);
    void showLogin();
    void showDashboard();
    void showNotFound();
    
    // Utility methods
    bool isAuthenticated();
    std::string getLoggedUser();
    void setLoggedUser(const std::string& user);
};

#endif