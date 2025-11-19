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

    


class LoginApplication : public Wt::WApplication {

private:
    Wt::WLineEdit* usernameEdit_;
    Wt::WLineEdit* passwordEdit_;
    Wt::WText* errorMessage_; 

public:
    LoginApplication(const Wt::WEnvironment& env)
        : Wt::WApplication(env)
    {

        useStyleSheet("/style/style.css");
        setTitle("Login Page");

        auto main_container = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
        main_container->setStyleClass("login-form");
        auto title = main_container->addWidget(std::make_unique<Wt::WText>("<h2>LOGIN</h2>"));
        title->setStyleClass("login-title");

        
        auto sub_container = main_container->addWidget(std::make_unique<Wt::WContainerWidget>());
        
        

        auto usernameLabel = sub_container->addWidget(std::make_unique<Wt::WLabel>("Username:"));
        
    
        usernameEdit_ = sub_container->addWidget(std::make_unique<Wt::WLineEdit>());
        usernameEdit_->setPlaceholderText("Enter your username");
        usernameEdit_->setStyleClass("input-field");
        usernameEdit_->setWidth(300);
        usernameEdit_->setHeight(50);
        usernameLabel->setBuddy(usernameEdit_);  // Associate label with input





        auto passwordLabel = sub_container->addWidget(std::make_unique<Wt::WLabel>("Password:"));
        auto password_input = sub_container->addWidget(std::make_unique<Wt::WLineEdit>());
        password_input->setWidth(300);
        password_input->setHeight(50);

        auto loginButton = sub_container->addWidget(std::make_unique<Wt::WPushButton>("Login"));
        loginButton->setStyleClass("login-button");
       
        // std::string simple_text = "sdfdsfsd";
        // auto simple = container->addWidget(std::make_unique<Wt::WText>(simple_text));
        title->setStyleClass("title");
        
        sub_container->setStyleClass("sub-container");
       
        
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