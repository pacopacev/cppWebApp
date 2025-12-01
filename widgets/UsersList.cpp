#include "UsersList.h"
#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WVBoxLayout.h>

void UserList::showUserList(Wt::WContainerWidget* contentArea) {
    if (!contentArea) return;

    auto contentText = contentArea->addWidget(std::make_unique<Wt::WText>());
        contentText->setTextFormat(Wt::TextFormat::UnsafeXHTML);
        contentText->setText("<h2>👥 User List</h2>"
                           "<p>List of all users in the system:</p>"
                           "<ul>"
                           "<li>John Doe (admin)</li>"
                           "<li>Jane Smith (user)</li>"
                           "<li>Bob Johnson (moderator)</li>"
                           "</ul>");
}