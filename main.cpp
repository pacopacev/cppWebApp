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
        setTitle("Test Application");

        auto container = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
        container->setStyleClass("main");
        auto title = container->addWidget(std::make_unique<Wt::WText>("<h2>Login to your account</h2>"));
        // std::string simple_text = "sdfdsfsd";
        // auto simple = container->addWidget(std::make_unique<Wt::WText>(simple_text));
        title->setStyleClass("title");
        auto sub_container = container->addWidget(std::make_unique<Wt::WContainerWidget>());
        sub_container->setStyleClass("sub-container");
        auto player = sub_container->addWidget(std::make_unique<Wt::WAudio>());

        
        player->addSource("https://moshhead-blackmetal.stream.laut.fm/moshhead-blackmetal");//https://www.soundhelix.com/examples/mp3/SoundHelix-Song-1.mp3
        player->setOptions(Wt::PlayerOption::Controls); // Show player controls
        player->setAlternativeContent(std::make_unique<Wt::WText>("Your browser doesn't support audio."));  
        player->setWidth("400px");
        player->setHeight("50px");
        
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