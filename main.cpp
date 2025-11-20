#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WEnvironment.h>
#include <Wt/WTemplate.h>
#include <Wt/WAudio.h>
#include <iostream>
#include <string>
#include <memory>
#include <Wt/WLabel.h>
#include "DatabaseManager.h"
#include <Wt/WVBoxLayout.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WString.h>
#include <Wt/WPasswordEdit.h>

    


class LoginApplication : public Wt::WApplication {

private:
    Wt::WLineEdit* usernameEdit_;
    // Wt::WLineEdit* passwordEdit_;
    Wt::WText* errorMessage_;
    Wt::WText* version_; 
    DatabaseManager dbManager_;
    Wt::WPasswordEdit *passwordEdit_;

public:
    LoginApplication(const Wt::WEnvironment& env)
        : Wt::WApplication(env)
    {

        useStyleSheet("/style/style.css");
        if (!dbManager_.connect()) {
            std::cerr << "Failed to connect to database!" << std::endl;
        }
        else {
            std::cout << "Connected to database successfully!" << std::endl;
        }


        
        setTitle("Flowbit Login");

        auto* main_container = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
        main_container->setStyleClass("main-container");

        

        // auto* title = main_container->addWidget(std::make_unique<Wt::WText>("<h3>LOGIN</h3>"));
        // title->setStyleClass("login-title");


        auto* form_container = main_container->addWidget(std::make_unique<Wt::WContainerWidget>());
        form_container->setStyleClass("form-container");  

        auto* formLayout = form_container->setLayout(std::make_unique<Wt::WVBoxLayout>());
        
        auto* logo_container = formLayout->addWidget(std::make_unique<Wt::WContainerWidget>());
        logo_container->setStyleClass("logo-container");
        auto* logo = logo_container->addWidget(std::make_unique<Wt::WImage>("resources/img/flowbit.png"));
        logo->setStyleClass("logo-image");
        logo->setAlternateText("Company Logo");

        auto userLayout = formLayout->addLayout(std::make_unique<Wt::WHBoxLayout>());
        auto usernameLabel = userLayout->addWidget(std::make_unique<Wt::WLabel>("Username:"));
        usernameEdit_ = userLayout->addWidget(std::make_unique<Wt::WLineEdit>());

// Password row - add another horizontal layout
        auto* passLayout = formLayout->addLayout(std::make_unique<Wt::WHBoxLayout>());
        auto passwordLabel = passLayout->addWidget(std::make_unique<Wt::WLabel>("Password:"));
        passwordEdit_ = passLayout->addWidget(std::make_unique<Wt::WPasswordEdit>());

        auto* buttonLayout = formLayout->addLayout(std::make_unique<Wt::WHBoxLayout>());
        auto loginButton = buttonLayout->addWidget(std::make_unique<Wt::WPushButton>("Login"));
        loginButton->setStyleClass("login-button");
        loginButton->clicked().connect(this, &LoginApplication::handleLogin);

















        usernameEdit_->setPlaceholderText("Enter your username");
        usernameEdit_->setStyleClass("input-field");
        usernameLabel->setBuddy(usernameEdit_);
        
        usernameEdit_->setPlaceholderText("Enter your username");
        usernameEdit_->setStyleClass("input-field");
        usernameEdit_->setWidth(300);
        usernameEdit_->setHeight(34);
        usernameLabel->setBuddy(usernameEdit_); 

        
    
        passwordEdit_->setPlaceholderText("Enter your password");
        passwordEdit_->setStyleClass("input-field");
        passwordEdit_->setWidth(300);
        passwordEdit_->setHeight(34);
        passwordLabel->setBuddy(passwordEdit_); 

        auto* error_container = formLayout->addLayout(std::make_unique<Wt::WHBoxLayout>());
        errorMessage_ = error_container->addWidget(std::make_unique<Wt::WText>());
        errorMessage_->setStyleClass("error-message");
        errorMessage_->hide();

        // Create footer container
    auto* footer_container = main_container->addWidget(std::make_unique<Wt::WContainerWidget>());
    footer_container->setStyleClass("footer");

// Set horizontal layout for the footer
    auto* footerLayout = footer_container->setLayout(std::make_unique<Wt::WHBoxLayout>());

// Add version text to the footer layout
    version_ = footerLayout->addWidget(std::make_unique<Wt::WText>("Version 0.0.1 - Flowbit Cpyright 2025"));
    }

private:
    void handleLogin() {
        std::cout << "Login button clicked" << std::endl;
        
        // Get input values
        std::string username = usernameEdit_->text().toUTF8();
        std::string password = passwordEdit_->text().toUTF8();
        
        // Simple validation
        if (username.empty() || password.empty()) {
            showError("Please enter both username and password");
            return;
        }
        
        if (!dbManager_.isConnected()) {
            showError("Database connection failed. Please try again later.");
            return;
        }
        
        // Validate against database
        if (dbManager_.validateUser(username, password)) {
            showSuccess("Login successful! Welcome, " + username);
            // Redirect or load main application
        } else {
            showError("Invalid username or password");
        }
        
        // Clear password for security
        passwordEdit_->setText("");

    }
    void showError(const std::string& message) {
        errorMessage_->setText(message);
        errorMessage_->setStyleClass("error-message");
        errorMessage_->show();
    }
    
    void showSuccess(const std::string& message) {
        errorMessage_->setText(message);
        errorMessage_->setStyleClass("success-message");
        errorMessage_->show();
    }

    
};

std::unique_ptr<Wt::WApplication> createApplication(const Wt::WEnvironment& env) {
    auto app = std::make_unique<LoginApplication>(env);
    return app;
}


int main(int argc, char **argv)
{
    auto t = std::make_unique<std::string>("test");
    std::cout << *t << std::endl;
    std::cout << &t << std::endl;
    return Wt::WRun(argc, argv, [](const Wt::WEnvironment &env) {
        return std::make_unique<LoginApplication>(env);
    });
}