#pragma once
#include <Wt/WContainerWidget.h>
#include <Wt/WSignal.h>

class DashboardWidget : public Wt::WContainerWidget {
public:
    DashboardWidget(const std::string& username, int userId);
    
    Wt::Signal<>& logoutRequested() { return logoutRequested_; }
    Wt::Signal<std::string>& menuItemSelected() { return menuItemSelected_; }

    // Add this method to set section from routes
    void setActiveSection(const std::string& section);

private:
    void setupSidebarTree(Wt::WContainerWidget* treeContainer);
    void showContent(const std::string& content);
    void handleLogout();

    Wt::WContainerWidget* contentArea_;
    
    Wt::Signal<> logoutRequested_;
    Wt::Signal<std::string> menuItemSelected_;

    int userId_;
    std::string username_;
};