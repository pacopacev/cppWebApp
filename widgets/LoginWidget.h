#ifndef LOGIN_WIDGET_H
#define LOGIN_WIDGET_H

#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPasswordEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WSignal.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WHBoxLayout.h>
#include "DatabaseManager.h"

class LoginWidget : public Wt::WContainerWidget {
public:
    // Make sure this constructor is properly declared
    LoginWidget(DatabaseManager& dbManager);
    
    // Signals
    Wt::Signal<std::string, int>& loginSuccess() { return loginSuccess_; }
    Wt::Signal<std::string>& loginFailed() { return loginFailed_; }

private:
    DatabaseManager& dbManager_;
    Wt::WLineEdit* usernameEdit_;
    Wt::WPasswordEdit* passwordEdit_;
    Wt::WText* errorMessage_;
    // Wt::WText* statusText_;
    
    Wt::Signal<std::string, int> loginSuccess_;  // Changed to two parameters
    Wt::Signal<std::string> loginFailed_;
    
    void handleLogin();
    void validateCredentials(const std::string& username, const std::string& password);
};

#endif