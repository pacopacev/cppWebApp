#include "DashboardWidget.h"

DashboardWidget::DashboardWidget(const std::string& username) {
    setStyleClass("dashboard-widget");
    
    auto layout = setLayout(std::make_unique<Wt::WVBoxLayout>());
    
    // Welcome message
    auto welcomeText = layout->addWidget(std::make_unique<Wt::WText>("Welcome to Dashboard, " + username));
    welcomeText->setStyleClass("dashboard-title");
    
    // Content
    auto content = layout->addWidget(std::make_unique<Wt::WText>("This is your dashboard content."));
    
    // Logout button
    auto logoutButton = layout->addWidget(std::make_unique<Wt::WPushButton>("Logout"));
    logoutButton->setStyleClass("btn btn-logout");
    logoutButton->clicked().connect(this, &DashboardWidget::handleLogout);
}

void DashboardWidget::handleLogout() {
    logoutRequested_.emit();
}