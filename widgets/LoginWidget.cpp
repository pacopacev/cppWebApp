#include "LoginWidget.h"
#include <iostream>
#include "DatabaseManager.h"
#include "Wt/WLabel.h"

LoginWidget::LoginWidget() {

    DatabaseManager dbManager_;

    // Create main container
    auto* main_container = this->addWidget(std::make_unique<Wt::WContainerWidget>());
    main_container->setStyleClass("main-container");

    // Create center container inside main container
    auto* center_container = main_container->addWidget(std::make_unique<Wt::WContainerWidget>());
    center_container->setStyleClass("center-container");

    // Database status row
    auto db_status_content = center_container->setLayout(std::make_unique<Wt::WHBoxLayout>());
    db_status_content->addWidget(std::make_unique<Wt::WText>("DATABASE STATUS: "));
    
    std::string statusText = dbManager_.connect() ? "🟢 Connected" : "🔴 Disconnected";
    // std::cout << statusText << std::endl;
    auto statusIndicator = db_status_content->addWidget(std::make_unique<Wt::WText>(statusText));
    statusIndicator->setStyleClass(dbManager_.isConnected() ? "db-connected" : "db-disconnected");

    

    // Form container
    auto* form_container = main_container->addWidget(std::make_unique<Wt::WContainerWidget>());
    form_container->setStyleClass("form-container");
    auto formLayout = form_container->setLayout(std::make_unique<Wt::WVBoxLayout>());

    auto logo_container = formLayout->addWidget(std::make_unique<Wt::WContainerWidget>());
    logo_container->setStyleClass("logo-container");
    auto logo = logo_container->addWidget(std::make_unique<Wt::WImage>("resources/img/flowbit.png"));
    logo->setStyleClass("logo-image");

    // Username row
    auto userLayout = formLayout->addLayout(std::make_unique<Wt::WHBoxLayout>());
    auto usernameLabel = userLayout->addWidget(std::make_unique<Wt::WLabel>("Username:"));
    usernameEdit_ = userLayout->addWidget(std::make_unique<Wt::WLineEdit>());
    usernameEdit_->setPlaceholderText("Enter your username");
    usernameEdit_->setStyleClass("input-field");
    usernameLabel->setBuddy(usernameEdit_);

    // Password row
    auto* passLayout = formLayout->addLayout(std::make_unique<Wt::WHBoxLayout>());
    auto passwordLabel = passLayout->addWidget(std::make_unique<Wt::WLabel>("Password:"));
    passwordEdit_ = passLayout->addWidget(std::make_unique<Wt::WPasswordEdit>());
    passwordEdit_->setPlaceholderText("Enter your password");
    passwordEdit_->setStyleClass("input-field");
    passwordLabel->setBuddy(passwordEdit_);

    // Button row
    auto* buttonLayout = formLayout->addLayout(std::make_unique<Wt::WHBoxLayout>());
    auto loginButton = buttonLayout->addWidget(std::make_unique<Wt::WPushButton>("Login"));
    loginButton->setStyleClass("login-button");
    loginButton->clicked().connect(this, &LoginWidget::handleLogin);

    // Error container
    auto* error_container = formLayout->addWidget(std::make_unique<Wt::WContainerWidget>());
    error_container->setStyleClass("error_container");
    errorMessage_ = error_container->addWidget(std::make_unique<Wt::WText>());
    errorMessage_->setStyleClass("error-message");
    errorMessage_->hide();
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
        std::cerr << "Failed to connect to the database." << std::endl;
        return;
    }
    
    
    std::cout << username << " " << password << std::endl;

    // Simple validation - replace with your database logic
   if (dbManager_.validateUser(username, password)) {

    errorMessage_->setText("Successfully logged in");
    errorMessage_->show();
    loginSuccess_.emit("Login successful");


            // Redirect or load main application

        } else {
        errorMessage_->setText("Invalid username or password");
        errorMessage_->show();
        loginFailed_.emit("Invalid credentials");
    }
}