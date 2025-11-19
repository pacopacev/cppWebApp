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

    


class LoginApplication : public Wt::WApplication {
public:
    LoginApplication(const Wt::WEnvironment& env)
        : Wt::WApplication(env)
    {

        useStyleSheet("/style/style.css");
        setTitle("Login Page");

        auto container = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
        auto title = container->addWidget(std::make_unique<Wt::WText>("<h2>LOGIN</h2>"));
        auto sub_container = container->addWidget(std::make_unique<Wt::WContainerWidget>());
        container->setStyleClass("main");
        

        auto user_name = sub_container->addWidget(std::make_unique<Wt::WText>("<h3>Username</h3>"));
        auto user_name_input = sub_container->addWidget(std::make_unique<Wt::WLineEdit>());
        user_name_input->setWidth(300);
        user_name_input->setHeight(50);
        auto password = sub_container->addWidget(std::make_unique<Wt::WText>("<h3>Password</h3>"));
        auto password_input = sub_container->addWidget(std::make_unique<Wt::WLineEdit>());
        password_input->setWidth(300);
        password_input->setHeight(50);
        auto login = sub_container->addWidget(std::make_unique<Wt::WPushButton>("Login"));
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