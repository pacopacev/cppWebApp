#include "SecuritySettings.h"
#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>

void SecuritySettings::showSecuritySettings(Wt::WContainerWidget* contentArea) {
    if (!contentArea) return;
    auto contentText = contentArea->addWidget(std::make_unique<Wt::WText>());
        contentText->setTextFormat(Wt::TextFormat::UnsafeXHTML);
        contentText->setText("<h2>🔒 Security Settings</h2>"
                           "<p>Manage your security preferences:</p>"
                           "<div class='form-container'>"
                           "<input type='password' placeholder='Current Password' class='input-field'>"
                           "<input type='password' placeholder='New Password' class='input-field'>"
                           "<input type='password' placeholder='Confirm New Password' class='input-field'>"
                           "<button class='btn btn-primary'>Change Password</button>"
                           "</div>");
}