#include "DashboardWidget.h"
#include <Wt/WHBoxLayout.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WCssDecorationStyle.h>
#include <iostream>
#include "dash.h"
#include "UsersList.h"
#include "UsersAdd.h"
#include "SecuritySettings.h"

DashboardWidget::DashboardWidget(const std::string& username, int userId) {
    setStyleClass("dashboard-container");
    
    // Create main layout
    auto mainLayout = setLayout(std::make_unique<Wt::WHBoxLayout>());
    mainLayout->setContentsMargins(0, 0, 0, 0);
    
    // ===== SIDEBAR CREATION =====
    auto sidebar = std::make_unique<Wt::WContainerWidget>();
    sidebar->setStyleClass("sidebar");
    
    auto sidebarLayout = sidebar->setLayout(std::make_unique<Wt::WVBoxLayout>());
    sidebarLayout->setContentsMargins(0, 0, 0, 0);
    
    // Sidebar header
    auto header = sidebarLayout->addWidget(std::make_unique<Wt::WContainerWidget>());
    header->setStyleClass("sidebar-header");
    header->addWidget(std::make_unique<Wt::WText>("Flowbit Menu"));
    
    // Create tree container and add it to sidebar
    auto treeContainer = std::make_unique<Wt::WContainerWidget>();
    treeContainer->setStyleClass("manual-tree");
    setupSidebarTree(treeContainer.get());
    sidebarLayout->addWidget(std::move(treeContainer), 1); // Add with stretch factor 1
    
    // Logout button at bottom
    auto logoutContainer = sidebarLayout->addWidget(std::make_unique<Wt::WContainerWidget>());
    logoutContainer->setStyleClass("sidebar-footer");
    auto logoutBtn = logoutContainer->addWidget(std::make_unique<Wt::WPushButton>("Logout"));
    logoutBtn->setStyleClass("btn btn-logout");
    logoutBtn->clicked().connect(this, &DashboardWidget::handleLogout);
    
    // Add sidebar to main layout
    mainLayout->addWidget(std::move(sidebar), 0);
    
    // ===== MAIN CONTENT CREATION =====
    auto mainContent = std::make_unique<Wt::WContainerWidget>();
    mainContent->setStyleClass("main-content");
    
    auto mainContentLayout = mainContent->setLayout(std::make_unique<Wt::WVBoxLayout>());
    mainContentLayout->setContentsMargins(20, 20, 20, 20);
    
    // Welcome header
    auto welcomeHeader = mainContentLayout->addWidget(std::make_unique<Wt::WText>(
        "Welcome to Dashboard, " + username + "! (ID: " + std::to_string(userId) + ")"
    ));
    welcomeHeader->setStyleClass("content-header");

    // Content area
    contentArea_ = mainContentLayout->addWidget(std::make_unique<Wt::WContainerWidget>());
    contentArea_->setStyleClass("content-area");
    
    // Show default content
    showContent("dashboard");
    
    // Add main content to main layout with stretch factor 1
    mainLayout->addWidget(std::move(mainContent), 1);
    
    std::cout << "Dashboard created for user: " << username << std::endl;
}

void DashboardWidget::setupSidebarTree(Wt::WContainerWidget* treeContainer) {
    // Dashboard
    auto dashboardItem = treeContainer->addWidget(std::make_unique<Wt::WText>("📊 Dashboard"));
    dashboardItem->setStyleClass("tree-item");
    dashboardItem->clicked().connect([this]() {
        showContent("dashboard");
        menuItemSelected_.emit("dashboard");
    });
    
    // User Management section
    auto usersHeader = treeContainer->addWidget(std::make_unique<Wt::WText>("👥 User Management ▼"));
    usersHeader->setStyleClass("tree-header expanded");
    
    auto usersContainer = treeContainer->addWidget(std::make_unique<Wt::WContainerWidget>());
    usersContainer->setStyleClass("tree-children");
    
  // In setupSidebarTree, update each click handler like this:
auto listUsers = usersContainer->addWidget(std::make_unique<Wt::WText>("List Users"));
listUsers->setStyleClass("tree-child");
listUsers->clicked().connect([this]() {
    showContent("users_list");
    menuItemSelected_.emit("users_list"); // This will trigger RouteManager
});
    
    auto addUser = usersContainer->addWidget(std::make_unique<Wt::WText>("Add User"));
    addUser->setStyleClass("tree-child");
    addUser->clicked().connect([this]() {
        showContent("users_add");
        menuItemSelected_.emit("users_add");
    });
    
    // Settings section
    auto settingsHeader = treeContainer->addWidget(std::make_unique<Wt::WText>("⚙️ Settings ▼"));
    settingsHeader->setStyleClass("tree-header expanded");
    
    auto settingsContainer = treeContainer->addWidget(std::make_unique<Wt::WContainerWidget>());
    settingsContainer->setStyleClass("tree-children");
    
    auto profileItem = settingsContainer->addWidget(std::make_unique<Wt::WText>("Profile Settings"));
    profileItem->setStyleClass("tree-child");
    profileItem->clicked().connect([this]() {
        showContent("profile");
        menuItemSelected_.emit("profile");
    });
    
    auto securityItem = settingsContainer->addWidget(std::make_unique<Wt::WText>("Security"));
    securityItem->setStyleClass("tree-child");
    securityItem->clicked().connect([this]() {
        showContent("security");
        menuItemSelected_.emit("security");
    });
    
    // Reports section
    auto reportsHeader = treeContainer->addWidget(std::make_unique<Wt::WText>("📈 Reports ▼"));
    reportsHeader->setStyleClass("tree-header expanded");
    
    auto reportsContainer = treeContainer->addWidget(std::make_unique<Wt::WContainerWidget>());
    reportsContainer->setStyleClass("tree-children");
    
    auto dailyReport = reportsContainer->addWidget(std::make_unique<Wt::WText>("Daily Report"));
    dailyReport->setStyleClass("tree-child");
    dailyReport->clicked().connect([this]() {
        showContent("report_daily");
        menuItemSelected_.emit("report_daily");
    });
    
    auto monthlyReport = reportsContainer->addWidget(std::make_unique<Wt::WText>("Monthly Report"));
    monthlyReport->setStyleClass("tree-child");
    monthlyReport->clicked().connect([this]() {
        showContent("report_monthly");
        menuItemSelected_.emit("report_monthly");
    });
    
    // Connect header clicks to toggle sections
    usersHeader->clicked().connect([usersContainer, usersHeader]() {
    if (usersContainer->isHidden()) {
        usersContainer->show();
        usersHeader->setText("👥 User Management");
        usersHeader->removeStyleClass("collapsed");
        usersHeader->addStyleClass("expanded");
    } else {
        usersContainer->hide();
        usersHeader->setText("👥 User Management");
        usersHeader->removeStyleClass("expanded");
        usersHeader->addStyleClass("collapsed");
    }
});
    
    settingsHeader->clicked().connect([settingsContainer, settingsHeader]() {
        if (settingsContainer->isHidden()) {
            settingsContainer->show();
            settingsHeader->setText("⚙️ Settings ▼");
            settingsHeader->removeStyleClass("collapsed");
            settingsHeader->addStyleClass("expanded");
        } else {
            settingsContainer->hide();
            settingsHeader->setText("⚙️ Settings ▶");
            settingsHeader->removeStyleClass("expanded");
            settingsHeader->addStyleClass("collapsed");
        }
    });
    
    reportsHeader->clicked().connect([reportsContainer, reportsHeader]() {
        if (reportsContainer->isHidden()) {
            reportsContainer->show();
            reportsHeader->setText("📈 Reports ▼");
            reportsHeader->removeStyleClass("collapsed");
            reportsHeader->addStyleClass("expanded");
        } else {
            reportsContainer->hide();
            reportsHeader->setText("📈 Reports ▶");
            reportsHeader->removeStyleClass("expanded");
            reportsHeader->addStyleClass("collapsed");
        }
    });
}

void DashboardWidget::showContent(const std::string& content) {
    contentArea_->clear();
     if (content == "dashboard") {
        dash myDash;
        myDash.showdash(contentArea_);

    } else if (content == "users_list") {
        UserList userListWidget;
        userListWidget.showUserList(contentArea_);

    } else if (content == "users_add") {
        usersAdd usersAddWidget;
        usersAddWidget.showUsersAdd(contentArea_);
    } else if (content == "profile") {
        auto contentText = contentArea_->addWidget(std::make_unique<Wt::WText>());
        contentText->setTextFormat(Wt::TextFormat::UnsafeXHTML);
        contentText->setText("<h2>👤 Profile Settings</h2>"
                           "<p>Manage your profile settings:</p>"
                           "<div class='form-container'>"
                           "<input type='text' placeholder='Full Name' class='input-field'>"
                           "<input type='email' placeholder='Email' class='input-field'>"
                           "<input type='tel' placeholder='Phone' class='input-field'>"
                           "<button class='btn btn-primary'>Update Profile</button>"
                           "</div>");
    } else if (content == "security") {
        SecuritySettings securitySettingsWidget;
        securitySettingsWidget.showSecuritySettings(contentArea_);
    } else if (content == "report_daily") {
        auto contentText = contentArea_->addWidget(std::make_unique<Wt::WText>());
        contentText->setTextFormat(Wt::TextFormat::UnsafeXHTML);
        contentText->setText("<h2>📅 Daily Report</h2>"
                           "<p>Daily activity report for today:</p>"
                           "<div class='report-stats'>"
                           "<p>📈 Logins: 45</p>"
                           "<p>👥 New Users: 3</p>"
                           "<p>📊 Activities: 127</p>"
                           "<p>⚠️ Warnings: 2</p>"
                           "</div>");
    } else if (content == "report_monthly") {
        auto contentText = contentArea_->addWidget(std::make_unique<Wt::WText>());
        contentText->setTextFormat(Wt::TextFormat::UnsafeXHTML);
        contentText->setText("<h2>📊 Monthly Report</h2>"
                           "<p>Monthly summary report for this month:</p>"
                           "<div class='report-stats'>"
                           "<p>📈 Total Logins: 1,234</p>"
                           "<p>👥 Total Users: 156</p>"
                           "<p>📊 Total Activities: 4,567</p>"
                           "<p>✅ Success Rate: 98.5%</p>"
                           "</div>");
    } else {
        auto contentText = contentArea_->addWidget(std::make_unique<Wt::WText>());
        contentText->setTextFormat(Wt::TextFormat::UnsafeXHTML);
        contentText->setText("<h2>Content Not Found</h2><p>Selected menu item is not implemented yet.</p>");
    }
}

void DashboardWidget::handleLogout() {
    std::cout << "Logout handled in DashboardWidget" << std::endl;
    logoutRequested_.emit();
}


void DashboardWidget::setActiveSection(const std::string& section) {
    showContent(section);
}