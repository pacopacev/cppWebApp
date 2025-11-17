// main.cpp
#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WEnvironment.h>
#include <iostream>
#include <string>
#include "MemoryMonitor.h"

    


class CalculatorApp : public Wt::WApplication {
public:
    CalculatorApp(const Wt::WEnvironment& env)
        : Wt::WApplication(env)
    {
        useStyleSheet("style/style.css");
        setTitle("Calculator");
        
        auto container = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
        container->addStyleClass("container");

        // Display RAM usage at the top
        memMonitor_ = std::make_unique<MemoryMonitor>();
        std::string memStatus = memMonitor_->getMemoryStatus();
        ramText_ = container->addWidget(std::make_unique<Wt::WText>("RAM Usage: " + memStatus));
        ramText_->addStyleClass("ram-info");
        container->addWidget(std::make_unique<Wt::WBreak>());

        // Number A with proper spacing
        // container->addWidget(std::make_unique<Wt::WBreak>()); // Extra space
        container->addWidget(std::make_unique<Wt::WText>("Number A: "));

        aEdit_ = container->addWidget(std::make_unique<Wt::WLineEdit>());
        aEdit_->setPlaceholderText("Enter first number");
        // container->addWidget(std::make_unique<Wt::WBreak>());
        // container->addWidget(std::make_unique<Wt::WBreak>()); // Extra space

        // Number B with proper spacing
        // container->addWidget(std::make_unique<Wt::WBreak>()); // Extra space

        container->addWidget(std::make_unique<Wt::WText>("Number B: "));
        bEdit_ = container->addWidget(std::make_unique<Wt::WLineEdit>());
        bEdit_->setPlaceholderText("Enter second number");
        // container->addWidget(std::make_unique<Wt::WBreak>());
        // container->addWidget(std::make_unique<Wt::WBreak>()); // Extra space

        resultText_ = container->addWidget(std::make_unique<Wt::WText>("Result will appear here"));
        resultText_->addStyleClass("result");
        // container->addWidget(std::make_unique<Wt::WBreak>());
        // container->addWidget(std::make_unique<Wt::WBreak>()); // Extra space

        // Create operation buttons
        auto addBtn = container->addWidget(std::make_unique<Wt::WPushButton>("+"));
        auto subBtn = container->addWidget(std::make_unique<Wt::WPushButton>("-"));
        auto mulBtn = container->addWidget(std::make_unique<Wt::WPushButton>("*"));
        auto divBtn = container->addWidget(std::make_unique<Wt::WPushButton>("/"));

        // Style buttons
        addBtn->addStyleClass("btn");
        subBtn->addStyleClass("btn");
        mulBtn->addStyleClass("btn");
        divBtn->addStyleClass("btn");

        // Connect button signals
        addBtn->clicked().connect([this](){ compute('+'); });
        subBtn->clicked().connect([this](){ compute('-'); });
        mulBtn->clicked().connect([this](){ compute('*'); });
        divBtn->clicked().connect([this](){ compute('/'); });
    }

private:

    Wt::WLineEdit *aEdit_;
    Wt::WLineEdit *bEdit_;
    Wt::WText *resultText_;
    Wt::WText *ramText_;
    std::unique_ptr<MemoryMonitor> memMonitor_;
    void compute(char op) {
        try {
            double a = std::stod(aEdit_->text().toUTF8());
            double b = std::stod(bEdit_->text().toUTF8());
            double res = 0.0;
            switch (op) {
                case '+': res = a + b; break;
                case '-': res = a - b; break;
                case '*': res = a * b; break;
                case '/':
                    if (b == 0) {
                        resultText_->setText("Error: division by zero");
                        return;
                    }
                    res = a / b; break;
                default:
                    resultText_->setText("Unknown operator");
                    return;
            }
            resultText_->setText("Result: " + std::to_string(res));
        } catch (...) {
            resultText_->setText("Invalid number input");
        }
    }

    
};

std::unique_ptr<Wt::WApplication> createApplication(const Wt::WEnvironment& env) {
    return std::make_unique<CalculatorApp>(env);
}


int main(int argc, char **argv)
{
    auto t = std::make_unique<std::string>("test");
    std::cout << *t << std::endl;
    std::cout << &t << std::endl;
    return Wt::WRun(argc, argv, [](const Wt::WEnvironment &env) {
        return std::make_unique<CalculatorApp>(env);
    });
}