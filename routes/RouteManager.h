#pragma once
#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WSignal.h>
#include <string>
#include <functional>
#include <map>

class DatabaseManager;
class LoginWidget;
class DashboardWidget;

class RouteManager {
public:
    using AuthCheckCallback = std::function<bool()>;
    using UserGetterCallback = std::function<std::string()>;
    using UserSetterCallback = std::function<void(const std::string&)>;

    RouteManager(Wt::WApplication* app, DatabaseManager& dbManager);
    
    void setupRoutes();
    void navigateTo(const std::string& path);
    
    void setAuthCheckCallback(AuthCheckCallback callback);
    void setUserGetterCallback(UserGetterCallback callback);
    void setUserSetterCallback(UserSetterCallback callback);

private:
    void handleRoute(const std::string& path);
    void showLogin();
    void showDashboard(const std::string& path = "/dashboard");
    void showNotFound();
    void handleDashboardMenu(const std::string& section);
    std::string getSectionFromPath(const std::string& path);
    
    bool isAuthenticated();
    std::string getLoggedUser();
    void setLoggedUser(const std::string& user);
    std::string loggedUser_;
    int loggedUserId_ = -1; // Add user ID storage
    
    void setLoggedUserId(int userId) { loggedUserId_ = userId; }
    int getLoggedUserId() const { return loggedUserId_; }

    Wt::WApplication* app_;
    DatabaseManager& dbManager_;
    Wt::WContainerWidget* contentArea_;
    
    AuthCheckCallback authCheckCallback_;
    UserGetterCallback userGetterCallback_;
    UserSetterCallback userSetterCallback_;
};