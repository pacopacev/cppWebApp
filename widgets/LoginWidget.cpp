#include "LoginWidget.h"
#include <iostream>
#include "DatabaseManager.h"
#include "Wt/WLabel.h"
#include "Utils.h"

LoginWidget::LoginWidget(DatabaseManager& dbManager) 
    : dbManager_(dbManager) {

    // Create main container
    auto* main_container = this->addWidget(std::make_unique<Wt::WContainerWidget>());
    main_container->setStyleClass("main-container");

   

    

    // Form container
    auto* form_container = main_container->addWidget(std::make_unique<Wt::WContainerWidget>());
    form_container->setStyleClass("form-container");
    auto formLayout = form_container->setLayout(std::make_unique<Wt::WVBoxLayout>());

    

     // Create center container inside main container
    auto* center_container = formLayout->addWidget(std::make_unique<Wt::WContainerWidget>());
    center_container->setStyleClass("center-container");

    auto devider_container = formLayout->addWidget(std::make_unique<Wt::WContainerWidget>());
    devider_container->setStyleClass("devider-container");

    // Database status row
    auto db_status_content = center_container->setLayout(std::make_unique<Wt::WHBoxLayout>());
    db_status_content->addWidget(std::make_unique<Wt::WText>("DATABASE STATUS: "));
    

    
    std::string statusText = dbManager_.connect() ? "🟢 Connected" : "🔴 Disconnected";
    // std::cout << statusText << std::endl;
    auto statusIndicator = db_status_content->addWidget(std::make_unique<Wt::WText>(statusText));
    
    statusIndicator->setStyleClass(dbManager_.isConnected() ? "db-connected" : "db-disconnected");

    // Logo
    auto logo_container = formLayout->addWidget(std::make_unique<Wt::WContainerWidget>());
    logo_container->setStyleClass("logo-container");
    auto logo = logo_container->addWidget(std::make_unique<Wt::WImage>("resources/img/flowbit.png"));
    logo->setStyleClass("logo-image");

    // Username row
    // auto userLayout = formLayout->addLayout(std::make_unique<Wt::WHBoxLayout>());
    auto usernameContainer = formLayout->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto usernameLabel = usernameContainer->addWidget(std::make_unique<Wt::WLabel>("Username:"));
    usernameContainer->setStyleClass("username-container");
    usernameEdit_ = usernameContainer->addWidget(std::make_unique<Wt::WLineEdit>());
    usernameEdit_->setPlaceholderText("Enter your username");
    usernameEdit_->setStyleClass("input-field");
    usernameLabel->setBuddy(usernameEdit_);

    // userLayout->setStretchFactor(usernameEdit_, 1);

    // Password row
    // auto* passLayout = formLayout->addLayout(std::make_unique<Wt::WHBoxLayout>());
    auto passWordContainer = formLayout->addWidget(std::make_unique<Wt::WContainerWidget>());
    passWordContainer->setStyleClass("password-container");
    // auto* passLayout = passWordContainer->setLayout(std::make_unique<Wt::WHBoxLayout>());
    auto passwordLabel = passWordContainer->addWidget(std::make_unique<Wt::WLabel>("Password:"));
    passwordEdit_ = passWordContainer->addWidget(std::make_unique<Wt::WPasswordEdit>());
    passwordEdit_->setPlaceholderText("Enter your password");
    passwordEdit_->setStyleClass("input-field");
    passwordEdit_->setReadOnly(false);
    passwordEdit_->setNativeControl(true);
    passwordLabel->setBuddy(passwordEdit_);
    // passLayout->setStretchFactor(passwordEdit_, 1);

    // Button row
    auto* buttonLayout = formLayout->addLayout(std::make_unique<Wt::WHBoxLayout>());
    auto loginButton = buttonLayout->addWidget(std::make_unique<Wt::WPushButton>("Login"));
    loginButton->setStyleClass("stat-card");
    loginButton->clicked().connect(this, &LoginWidget::handleLogin);

    // Error container
    auto* error_container = formLayout->addWidget(std::make_unique<Wt::WContainerWidget>());
    error_container->setStyleClass("error_container");
    errorMessage_ = error_container->addWidget(std::make_unique<Wt::WText>());
    errorMessage_->setStyleClass("error-message");
    errorMessage_->hide();

    auto version_container = formLayout->addWidget(std::make_unique<Wt::WContainerWidget>());
    version_container->setStyleClass("version-container");
    std::string versionText = Utils::getVersion();
    // std::cout << versionText << std::endl;
    auto version_text = version_container->addWidget(std::make_unique<Wt::WText>("Version: " + versionText));
}


void LoginWidget::handleLogin() {
    std::cout << "Login button clicked" << std::endl;
    std::string username = usernameEdit_->text().toUTF8();
    std::string password = passwordEdit_->text().toUTF8();
    
    // Clear password for security
    passwordEdit_->setText("");
    
    if (username.empty() || password.empty()) {
        errorMessage_->setText("Please enter both username and password");
        errorMessage_->show();
        return;
    }

    
    
    validateCredentials(username, password);
}

void LoginWidget::validateCredentials(const std::string& username, const std::string& password) {

    DatabaseManager dbManager_;
    if (!dbManager_.connect()) {
        std::cout << "Failed to connect to the database." << std::endl;
        return;
    }
    
    
    // std::cout << username << " " << password << std::endl;
    int userId = -1;
    // Simple validation - replace with your database logic
   if (dbManager_.validateUser(username, password, userId)) {
        std::cout << "User validated! Username: " << username << ", ID: " << userId << std::endl;
        errorMessage_->setText("Successfully logged in");
        errorMessage_->show();
        // Send a signal to the application that the user has been logged in successfully with their user ID
        loginSuccess_.emit(username, userId);


            // Redirect or load main application

        } else {
        errorMessage_->setText("Invalid username or password");
        errorMessage_->show();
        loginFailed_.emit("Invalid credentials");
    }
}