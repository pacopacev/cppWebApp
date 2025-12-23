#ifndef WIDGETS_USERSADD_H
#define WIDGETS_USERSADD_H
#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WString.h>
#include <Wt/WText.h>
#include "DatabaseManager.h"

class UsersAdd : public Wt::WContainerWidget {

public:
    UsersAdd();

    
    
private:
    void handleAddButton();
    void processUserCredentials(const Wt::WString& username, 
                               const Wt::WString& email, 
                               const Wt::WString& password);
    
    
    
    // Form widgets
    Wt::WLineEdit* usernameEdit_;
    Wt::WLineEdit* emailEdit_;
    Wt::WLineEdit* passwordEdit_;
    Wt::WText* statusText_;

    
};

#endif // WIDGETS_USERSADD_H