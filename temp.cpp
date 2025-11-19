#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WEnvironment.h>
#include <Wt/WTemplate.h>
#include <Wt/WAudio.h>
#include <Wt/WLabel.h>  // Added missing include
#include <iostream>
#include <string>
#include <memory>

class LoginApplication : public Wt::WApplication {

private:
    Wt::WLineEdit* usernameEdit_;
    Wt::WLineEdit* passwordEdit_;
    Wt::WText* errorMessage_;

public:
    LoginApplication(const Wt::WEnvironment& env)
        : Wt::WApplication(env)
    {
        useStyleSheet("style.css");  // Fixed path - remove leading slash
        setTitle("Login Page");

        auto form = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
        auto title = form->addWidget(std::make_unique<Wt::WText>("<h2>LOGIN</h2>"));
        title->setStyleClass("login-title");
        
        form->setStyleClass("login-form");

        // Username field
        auto usernameContainer = form->addWidget(std::make_unique<Wt::WContainerWidget>());
        usernameContainer->setStyleClass("input-container");
        auto usernameLabel = usernameContainer->addWidget(std::make_unique<Wt::WLabel>("Username:"));
        usernameEdit_ = usernameContainer->addWidget(std::make_unique<Wt::WLineEdit>());
        usernameEdit_->setPlaceholderText("Enter your username");
        usernameEdit_->setStyleClass("input-field");
        usernameLabel->setBuddy(usernameEdit_);  // Associate label with input
        
        // Add break for spacing
        form->addWidget(std::make_unique<Wt::WBreak>());
        
        // Password field
        auto passwordContainer = form->addWidget(std::make_unique<Wt::WContainerWidget>());
        passwordContainer->setStyleClass("input-container");
        auto passwordLabel = passwordContainer->addWidget(std::make_unique<Wt::WLabel>("Password:"));
        passwordEdit_ = passwordContainer->addWidget(std::make_unique<Wt::WLineEdit>());
        passwordEdit_->setEchoMode(Wt::EchoMode::Password);
        passwordEdit_->setPlaceholderText("Enter your password");
        passwordEdit_->setStyleClass("input-field");
        passwordLabel->setBuddy(passwordEdit_);  // Associate label with input
        
        // Add break for spacing
        form->addWidget(std::make_unique<Wt::WBreak>());
        
        // Error message
        errorMessage_ = form->addWidget(std::make_unique<Wt::WText>());
        errorMessage_->setStyleClass("error-message");
        errorMessage_->hide();
        
        // Login button
        auto loginButton = form->addWidget(std::make_unique<Wt::WPushButton>("Login"));
        loginButton->setStyleClass("login-button");
        loginButton->clicked().connect(this, &LoginApplication::handleLogin);
        
        // Enter key support
        usernameEdit_->enterPressed().connect([this]() { handleLogin(); });
        passwordEdit_->enterPressed().connect([this]() { handleLogin(); });
    }

    void handleLogin() {
        std::string username = usernameEdit_->text().toUTF8();
        std::string password = passwordEdit_->text().toUTF8();
        
        // Validate input
        if (username.empty() || password.empty()) {
            showError("Please enter both username and password.");
            return;
        }
        
        // Authenticate user
        if (authenticate(username, password)) {
            onLoginSuccess(username);
        } else {
            onLoginFailure();
        }
    }

private:
    bool authenticate(const std::string& username, const std::string& password) {
        // Replace this with your actual authentication logic
        // This is just a simple example
        return (username == "admin" && password == "password") ||
               (username == "user" && password == "123456");
    }
    
    void onLoginSuccess(const std::string& username) {
        // Store user session
        Wt::WApplication::instance()->setCookie("user_session", username, 3600);
        Wt::WApplication::instance()->setCookie("user_name", username, 3600);
        
        // Redirect to main page
        Wt::WApplication::instance()->redirect("/dashboard");
    }
    
    void onLoginFailure() {
        showError("Invalid username or password. Please try again.");
        passwordEdit_->setText(""); // Clear password field
        passwordEdit_->setFocus(); // Focus back to password field
    }
    
    void showError(const std::string& message) {
        errorMessage_->setText(message);
        errorMessage_->show();
    }
};

int main(int argc, char **argv)
{
    return Wt::WRun(argc, argv, [](const Wt::WEnvironment &env) {
        return std::make_unique<LoginApplication>(env);
    });
}

Enhanced CSS (style.css)
css

/* style.css */
.login-form {
    max-width: 400px;
    margin: 50px auto;
    padding: 30px;
    background-color: #f9f9f9;
    border-radius: 10px;
    box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
    font-family: Arial, sans-serif;
}

.login-title {
    text-align: center;
    color: #333;
    margin-bottom: 30px;
}

.input-container {
    margin-bottom: 20px;
}

.input-container label {
    display: block;
    margin-bottom: 5px;
    color: #555;
    font-weight: bold;
}

.input-field {
    width: 100%;
    padding: 12px;
    border: 2px solid #ddd;
    border-radius: 5px;
    font-size: 16px;
    box-sizing: border-box;
}

.input-field:focus {
    border-color: #4CAF50;
    outline: none;
}

.login-button {
    width: 100%;
    padding: 12px;
    background-color: #4CAF50;
    color: white;
    border: none;
    border-radius: 5px;
    font-size: 16px;
    cursor: pointer;
    transition: background-color 0.3s;
}

.login-button:hover {
    background-color: #45a049;
}

.login-button:active {
    transform: translateY(1px);
}

.error-message {
    color: #d32f2f;
    background-color: #ffebee;
    padding: 12px;
    border-radius: 5px;
    margin: 15px 0;
    border-left: 4px solid #d32f2f;
    text-align: center;
}

/* Responsive design */
@media (max-width: 480px) {
    .login-form {
        margin: 20px;
        padding: 20px;
    }
}