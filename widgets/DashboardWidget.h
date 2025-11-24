#ifndef DASHBOARD_WIDGET_H
#define DASHBOARD_WIDGET_H

#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WPushButton.h>
#include <Wt/WSignal.h>
#include <Wt/WVBoxLayout.h>

class DashboardWidget : public Wt::WContainerWidget {
public:
    DashboardWidget(const std::string& username);
    
    Wt::Signal<>& logoutRequested() { return logoutRequested_; }

private:
    Wt::Signal<> logoutRequested_;
    
    void handleLogout();
};

#endif