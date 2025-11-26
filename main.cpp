#include <Wt/WApplication.h>
#include <Wt/WEnvironment.h>
#include "routes/RouteManager.h"
#include "DatabaseManager.h"
#include <iostream>

class FlowbitApplication : public Wt::WApplication {
private:
    RouteManager* routeManager_;
    DatabaseManager dbManager_;  // DatabaseManager instance
    std::string loggedUser_;

public:
    FlowbitApplication(const Wt::WEnvironment& env)
        : Wt::WApplication(env) {
        
        std::cout << "FlowbitApplication created" << std::endl;
        
        // Setup application
        useStyleSheet("/style/style.css");
        setTitle("Flowbit");
        
        // Initialize route manager with dbManager
        routeManager_ = new RouteManager(this, dbManager_);
        
        // Register application state callbacks
        routeManager_->setAuthCheckCallback([this]() { 
            return !loggedUser_.empty(); 
        });
        routeManager_->setUserGetterCallback([this]() { 
            return loggedUser_; 
        });
        routeManager_->setUserSetterCallback([this](const std::string& user) { 
            loggedUser_ = user; 
        });
        
        // Setup routes
        routeManager_->setupRoutes();
    }
    
    ~FlowbitApplication() {
        std::cout << "FlowbitApplication destroyed" << std::endl;
        delete routeManager_;
    }
};

int main(int argc, char** argv) {
    return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
        return std::make_unique<FlowbitApplication>(env);
    });
}