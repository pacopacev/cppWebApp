#include"UsersAdd.h"
#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WVBoxLayout.h>

void usersAdd::showUsersAdd(Wt::WContainerWidget* contentArea) {
    if (!contentArea) return;

    auto contentText = contentArea->addWidget(std::make_unique<Wt::WText>());
        contentText->setTextFormat(Wt::TextFormat::UnsafeXHTML);
        contentText->setText("<h2>➕ Add User</h2>"
                           "<p>Add a new user to the system:</p>"
                           "<div class='form-container'>"
                           "<input type='text' placeholder='Username' class='input-field'>"
                           "<input type='email' placeholder='Email' class='input-field'>"
                           "<input type='password' placeholder='Password' class='input-field'>"
                           "<button class='btn btn-primary'>Add User</button>"
                           "</div>");
}