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
#include <Wt/WGridLayout.h>
#include "Utils.h"
#include <Wt/WString.h>

class LoginApplication : public Wt::WApplication {
private:
    // UI widgets (created when showLogin() runs)
    Wt::WLineEdit* usernameEdit_ = nullptr;
    Wt::WPasswordEdit* passwordEdit_ = nullptr;
    Wt::WText* errorMessage_ = nullptr;
    Wt::WContainerWidget* error_container_ = nullptr;
    Wt::WText* version_ = nullptr;

    // DB and status
    DatabaseManager dbManager_;
    Wt::WText* dot_status_ = nullptr; // non-owning raw ptr; owned by widget tree

    // session info
    std::string loggedUser_;

public:
    LoginApplication(const Wt::WEnvironment& env)
        : Wt::WApplication(env)
    {
        enableInternalPaths();
        internalPathChanged().connect(this, &LoginApplication::route);

        useStyleSheet("/style/style.css");

        // Establish DB status text but don't add to root yet
        std::unique_ptr<Wt::WText> dot;
        if (!dbManager_.connect()) {
            std::cerr << "Failed to connect to database!" << std::endl;
            dot = std::make_unique<Wt::WText>("🔴");
        } else {
            std::cout << "Connected to database successfully!" << std::endl;
            dot = std::make_unique<Wt::WText>("🟢");
        }
        // Keep a raw pointer to the text (widget tree will own it once added).
        dot_status_ = dot.get();

        setTitle("Flowbit");

        // Add a top-level footer container now because footer is common
        auto* footer_container = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
        footer_container->setStyleClass("footer");
        auto* footerLayout = footer_container->setLayout(std::make_unique<Wt::WHBoxLayout>());

        std::string currentDate = Utils::getCurrentDate();
        std::string version = Utils::getVersion();

        version_ = footerLayout->addWidget(std::make_unique<Wt::WText>(version + " Flowbit Build: " + currentDate));
        version_->setStyleClass("version-text");

        // Now route to the current internal path (this will build the appropriate view)
        route(internalPath());
    }

private:
    // Router: builds the view depending on path
    void route(const std::string& path) {
        // Clear everything except the footer we added at the end of the constructor.
        // For simplicity, clear root() entirely and rebuild footer inside each view.
        root()->clear();

        // Recreate the footer here so it's always present.
        // (Alternatively store footer separately. Here we rebuild so code stays simple.)
        if (path == "/dashboard") {
            showDashboard();
        } else {
            showLogin();
        }
    }

    // Build login UI (this creates usernameEdit_, passwordEdit_, etc.)
    void showLogin() {
        auto* main_container = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
        main_container->setStyleClass("main-container");

        

        

        // Form container
        auto* form_container = main_container->addWidget(std::make_unique<Wt::WContainerWidget>());
        form_container->setStyleClass("form-container");
        auto* formLayout = form_container->setLayout(std::make_unique<Wt::WVBoxLayout>());

        // Database status row
        auto* center_container = formLayout->addWidget(std::make_unique<Wt::WContainerWidget>());
        center_container->setStyleClass("center-container");
        auto db_status_content = center_container->setLayout(std::make_unique<Wt::WHBoxLayout>());

        db_status_content->addWidget(std::make_unique<Wt::WText>("DATABASE STATUS: "));

        // Add the db status widget we created in ctor (recreate if null)
        if (dot_status_ == nullptr) {
            // fallback
            db_status_content->addWidget(std::make_unique<Wt::WText>("?"));
        } else {
            // We need to create a new WText owned by the widget tree and set its content to current symbol
            // Since dot_status_ points to a WText instance that was never attached, recreate a visual widget
            // (Safer than trying to reparent an existing widget)
            // Determine symbol by checking DB connection:
            std::string sym = dbManager_.isConnected() ? "🟢" : "🔴";
            db_status_content->addWidget(std::make_unique<Wt::WText>(sym));
        }

        // Logo
        auto* logo_container = formLayout->addWidget(std::make_unique<Wt::WContainerWidget>());
        logo_container->setStyleClass("logo-container");
        auto* logo = logo_container->addWidget(std::make_unique<Wt::WImage>("resources/img/flowbit.png"));
        logo->setStyleClass("logo-image");
        logo->setAlternateText("Company Logo");

        // Username row
        auto userLayout = formLayout->addLayout(std::make_unique<Wt::WHBoxLayout>());
        auto usernameLabel = userLayout->addWidget(std::make_unique<Wt::WLabel>("Username:"));
        usernameEdit_ = userLayout->addWidget(std::make_unique<Wt::WLineEdit>());

        // Password row
        auto* passLayout = formLayout->addLayout(std::make_unique<Wt::WHBoxLayout>());
        auto passwordLabel = passLayout->addWidget(std::make_unique<Wt::WLabel>("Password:"));
        passwordEdit_ = passLayout->addWidget(std::make_unique<Wt::WPasswordEdit>());

        // Button row
        auto* buttonLayout = formLayout->addLayout(std::make_unique<Wt::WHBoxLayout>());
        auto loginButton = buttonLayout->addWidget(std::make_unique<Wt::WPushButton>("Login"));
        loginButton->setStyleClass("login-button");
        loginButton->clicked().connect(this, &LoginApplication::handleLogin);

        // Field properties
        usernameEdit_->setPlaceholderText("Enter your username");
        usernameEdit_->setStyleClass("input-field");
        usernameEdit_->setWidth(200);
        usernameEdit_->setHeight(34);
        usernameLabel->setBuddy(usernameEdit_);

        passwordEdit_->setPlaceholderText("Enter your password");
        passwordEdit_->setStyleClass("input-field");
        passwordEdit_->setWidth(200);
        passwordEdit_->setHeight(34);
        passwordEdit_->setNativeControl(true);
        passwordLabel->setBuddy(passwordEdit_);

        // Error container
        error_container_ = formLayout->addWidget(std::make_unique<Wt::WContainerWidget>());
        errorMessage_ = error_container_->addWidget(std::make_unique<Wt::WText>());

        // Footer area (recreate footer so it's present under the login view)
        auto* footer_container = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
        footer_container->setStyleClass("footer");
        auto* footerLayout = footer_container->setLayout(std::make_unique<Wt::WHBoxLayout>());
        version_ = footerLayout->addWidget(std::make_unique<Wt::WText>(Utils::getVersion() + " Flowbit Build: " + Utils::getCurrentDate()));
        version_->setStyleClass("version-text");
    }

    // Validate credentials & route on success
    void handleLogin() {
    std::cout << "Login button clicked" << std::endl;

    if (!usernameEdit_ || !passwordEdit_) {
        showError("Internal error: login form not initialized.");
        return;
    }

    std::string username = usernameEdit_->text().toUTF8();
    std::string password = passwordEdit_->text().toUTF8();

    if (username.empty() || password.empty()) {
        showError("Please enter both username and password");
        return;
    }

    // Clear password FIRST before any navigation
    passwordEdit_->setText("");

    // Simple validation - no database
    if (username == "admin" && password == "admin123") {
        loggedUser_ = username;
        std::cout << "DEBUG: Login successful, username: " << loggedUser_ << std::endl;
        setInternalPath("/dashboard", true);
    } else {
        errorMessage_->setText("Invalid credentials");
        std::cout << "DEBUG: Login failed" << std::endl;
    }
}

    void showError(const std::string& message) {
        if (!errorMessage_) {
            // fallback: add a small notification
            root()->addWidget(std::make_unique<Wt::WText>(message));
            return;
        }
        errorMessage_->setText(message);
        error_container_->setStyleClass("error_container");
        errorMessage_->setStyleClass("error-message");
        errorMessage_->show();
    }

    void showSuccess(const std::string& message) {
        if (!errorMessage_) {
            root()->addWidget(std::make_unique<Wt::WText>(message));
            return;
        }
        errorMessage_->setText(message);
        errorMessage_->setStyleClass("success-message");
        errorMessage_->show();
    }

    // Dashboard view: uses loggedUser_ (not usernameEdit_)


// Utility to escape user input


void showDashboard() {
    root()->clear();  // clears all previous widgets

    auto container = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
    container->setStyleClass("dashboard-container");

    container->addWidget(std::make_unique<Wt::WText>("<h2>Dashboard</h2>", Wt::TextFormat::XHTML));
    container->addWidget(std::make_unique<Wt::WBreak>());

    std::string user = loggedUser_.empty() ? "Guest" : loggedUser_;
    container->addWidget(std::make_unique<Wt::WText>("Welcome, " + user));

    auto buttonRow = container->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto rowLayout = buttonRow->setLayout(std::make_unique<Wt::WHBoxLayout>());

    auto *openSystemBtn = rowLayout->addWidget(std::make_unique<Wt::WPushButton>("Open System"));
    openSystemBtn->clicked().connect([=] {
        Wt::log("info") << "Open System clicked";
    });

    auto *logoutBtn = rowLayout->addWidget(std::make_unique<Wt::WPushButton>("Logout"));
    logoutBtn->clicked().connect([=] {
        loggedUser_.clear();
        setInternalPath("/login", true);  // safely go back to login
    });

    // Optional footer
    auto *footer = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
    footer->setStyleClass("footer");
    auto *footerLayout = footer->setLayout(std::make_unique<Wt::WHBoxLayout>());
    footerLayout->addWidget(std::make_unique<Wt::WText>("Flowbit Dashboard"));
}





};

std::unique_ptr<Wt::WApplication> createApplication(const Wt::WEnvironment& env) {
    return std::make_unique<LoginApplication>(env);
}

int main(int argc, char **argv)
{
    return Wt::WRun(argc, argv, [](const Wt::WEnvironment &env) {
        return std::make_unique<LoginApplication>(env);
    });
}
