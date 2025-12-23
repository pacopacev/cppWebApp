#include "UsersAdd.h"
#include "PasswordUtils.h"
#include <Wt/WVBoxLayout.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WLabel.h>
#include <Wt/WBreak.h>
#include <Wt/WRegExpValidator.h>
#include <Wt/WLengthValidator.h>
#include <Wt/WAny.h>
#include <iostream>
#include <memory>

UsersAdd::UsersAdd() 
    : usernameEdit_(nullptr)
    , emailEdit_(nullptr)
    , passwordEdit_(nullptr)
    , statusText_(nullptr) {
    
    // Create main container with vertical layout
    auto container = this->setLayout(std::make_unique<Wt::WVBoxLayout>());
    
    // Title
    auto title = container->addWidget(std::make_unique<Wt::WText>("<h2>➕ Add User</h2>"));
    title->setTextFormat(Wt::TextFormat::XHTML);
    
    auto description = container->addWidget(std::make_unique<Wt::WText>(
        "<p>Add a new user to the system:</p>"
    ));
    description->setTextFormat(Wt::TextFormat::XHTML);
    
    // Form container
    auto formContainer = container->addWidget(std::make_unique<Wt::WContainerWidget>());
    formContainer->setStyleClass("form-container");
    auto formLayout = formContainer->setLayout(std::make_unique<Wt::WVBoxLayout>());
    
    // Username field
    auto usernameContainer = formLayout->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto usernameLayout = usernameContainer->setLayout(std::make_unique<Wt::WHBoxLayout>());
    
    auto usernameLabel = usernameLayout->addWidget(std::make_unique<Wt::WLabel>("Username:"));
    usernameEdit_ = usernameLayout->addWidget(std::make_unique<Wt::WLineEdit>(), 1);
    usernameEdit_->setPlaceholderText("Enter username");
    usernameEdit_->setStyleClass("input-field");
    usernameLabel->setBuddy(usernameEdit_);
    
    // Email field
    formLayout->addWidget(std::make_unique<Wt::WBreak>());
    auto emailContainer = formLayout->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto emailLayout = emailContainer->setLayout(std::make_unique<Wt::WHBoxLayout>());
    
    auto emailLabel = emailLayout->addWidget(std::make_unique<Wt::WLabel>("Email:"));
    emailEdit_ = emailLayout->addWidget(std::make_unique<Wt::WLineEdit>(), 1);
    emailEdit_->setPlaceholderText("Enter email address");
    emailEdit_->setStyleClass("input-field");
    
    // Email validator
    auto emailValidator = std::make_shared<Wt::WRegExpValidator>(
        "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$"
    );
    emailValidator->setMandatory(true);
    emailEdit_->setValidator(emailValidator);
    emailLabel->setBuddy(emailEdit_);
    
    // Password field
    formLayout->addWidget(std::make_unique<Wt::WBreak>());
    auto passwordContainer = formLayout->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto passwordLayout = passwordContainer->setLayout(std::make_unique<Wt::WHBoxLayout>());
    
    auto passwordLabel = passwordLayout->addWidget(std::make_unique<Wt::WLabel>("Password:"));
    passwordEdit_ = passwordLayout->addWidget(std::make_unique<Wt::WLineEdit>(), 1);
    passwordEdit_->setPlaceholderText("Enter password");
    passwordEdit_->setEchoMode(Wt::EchoMode::Password);
    passwordEdit_->setStyleClass("input-field");
    
    // Password validator (minimum 8 characters)
    auto passwordValidator = std::make_shared<Wt::WLengthValidator>(8, 100);
    passwordValidator->setMandatory(true);
    passwordEdit_->setValidator(passwordValidator);
    passwordLabel->setBuddy(passwordEdit_);
    
    // Add User button
    formLayout->addWidget(std::make_unique<Wt::WBreak>());
    auto addButton = formLayout->addWidget(std::make_unique<Wt::WPushButton>("Add User"));
    addButton->setStyleClass("btn btn-primary");
    
    // Status message area
    statusText_ = formLayout->addWidget(std::make_unique<Wt::WText>());
    statusText_->setStyleClass("status-message");
    
    // Connect button click
    addButton->clicked().connect([this]() {
        handleAddButton();
    });
    
    // Connect enter key press on each field
    usernameEdit_->enterPressed().connect([this]() {
        handleAddButton();
    });
    emailEdit_->enterPressed().connect([this]() {
        handleAddButton();
    });
    passwordEdit_->enterPressed().connect([this]() {
        handleAddButton();
    });
}

void UsersAdd::handleAddButton() {
    // Clear previous status
    statusText_->setText("");
    statusText_->removeStyleClass("text-danger");
    statusText_->removeStyleClass("text-success");
    
    // Step 1: Validate all fields
    bool valid = true;
    
    // Validate username
    if (usernameEdit_->text().empty()) {
        statusText_->setText("Please enter a username.");
        statusText_->addStyleClass("text-danger");
        valid = false;
    }
    
    // Validate email using validator
    if (emailEdit_->validate() != Wt::ValidationState::Valid) {
        statusText_->setText("Please enter a valid email address.");
        statusText_->addStyleClass("text-danger");
        valid = false;
    }
    
    // Validate password length
    if (passwordEdit_->validate() != Wt::ValidationState::Valid) {
        statusText_->setText("Password must be at least 8 characters long.");
        statusText_->addStyleClass("text-danger");
        valid = false;
    }
    
    if (!valid) {
        return;
    }
    
    // Step 2: Get form values
    std::string username = usernameEdit_->text().toUTF8();
    std::string email = emailEdit_->text().toUTF8();
    std::string password = passwordEdit_->text().toUTF8();
    
    // Step 3: Check password strength
    if (!PasswordUtils::isPasswordStrong(password)) {
        statusText_->setText("Password too weak! Use 8+ chars with mix of uppercase, lowercase, numbers, and symbols.");
        statusText_->addStyleClass("text-danger");
        return;
    }
    
    // Step 4: Hash the password
    std::string hashedPassword = PasswordUtils::hashPassword(password);
    
    // Step 5: Create DatabaseManager and connect
    DatabaseManager dbManager;
    
    // Debug output
    std::cout << "=== DEBUG: User Creation ===" << std::endl;
    std::cout << "Username: " << username << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Password hash (first 30 chars): " << hashedPassword.substr(0, 30) << "..." << std::endl;
    
    std::cout << "Attempting to connect to database..." << std::endl;
    if (!dbManager.connect()) {
        std::cerr << "ERROR: Database connection failed!" << std::endl;
        statusText_->setText("✗ Cannot connect to database. Please check database settings.");
        statusText_->addStyleClass("text-danger");
        return;
    }
    
    std::cout << "Database connected. Creating user..." << std::endl;
    
    // Step 6: Create user in database
    bool success = dbManager.createUser(username, email, hashedPassword);
    
    // Step 7: Show result
    if (success) {
        std::cout << "✓ User created successfully in database" << std::endl;
        statusText_->setText("✓ User added successfully!");
        statusText_->addStyleClass("text-success");
        
        // Clear form on success
        usernameEdit_->setText("");
        emailEdit_->setText("");
        passwordEdit_->setText("");
    } else {
        std::cerr << "✗ Failed to create user in database" << std::endl;
        statusText_->setText("✗ Failed to add user. Username or email might already exist.");
        statusText_->addStyleClass("text-danger");
    }
}

void UsersAdd::processUserCredentials(const Wt::WString& username, 
                                     const Wt::WString& email, 
                                     const Wt::WString& password) {
    // This function can be used if you want to process credentials differently
    // For now, it's called from handleAddButton
    
    std::cout << "Processing credentials for: " << username.toUTF8() << std::endl;
    std::cout << "Email: " << email.toUTF8() << std::endl;
    std::cout << "Password (plain): " << password.toUTF8() << std::endl;
    
    // Convert to std::string
    std::string usernameStr = username.toUTF8();
    std::string emailStr = email.toUTF8();
    std::string passwordStr = password.toUTF8();
    
    // Hash password
    std::string hashedPassword = PasswordUtils::hashPassword(passwordStr);
    
    // Store in database
    DatabaseManager dbManager;
    if (dbManager.connect()) {
        dbManager.createUser(usernameStr, emailStr, hashedPassword);
    }
}