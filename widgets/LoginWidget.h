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
    LoginWidget();
    
    // Signals
    Wt::Signal<const std::string&>& loginSuccess() { return loginSuccess_; }
    Wt::Signal<const std::string&>& loginFailed() { return loginFailed_; }

private:

    DatabaseManager dbManager_;
    Wt::WLineEdit* usernameEdit_;
    Wt::WPasswordEdit* passwordEdit_;
    Wt::WText* errorMessage_;
    
    Wt::Signal<const std::string&> loginSuccess_;
    Wt::Signal<const std::string&> loginFailed_;
    
    void handleLogin();
    void validateCredentials(const std::string& username, const std::string& password);

    
};

#endif