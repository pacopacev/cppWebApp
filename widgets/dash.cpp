
#include "dash.h"
#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WPushButton.h>

void dash::showdash(Wt::WContainerWidget* contentArea) {
    if (!contentArea) return;

    auto container = contentArea->addWidget(std::make_unique<Wt::WContainerWidget>());
    container->setStyleClass("dashboard-content");

    auto title = container->addWidget(std::make_unique<Wt::WText>("<h2>📊 Dashboard Overview</h2>"));
    title->setTextFormat(Wt::TextFormat::UnsafeXHTML);

    auto description = container->addWidget(std::make_unique<Wt::WText>(
        "<p>Welcome to your main dashboard. Here you can see an overview of your system.</p>"
    ));
    description->setTextFormat(Wt::TextFormat::UnsafeXHTML);

    auto statsContainer = container->addWidget(std::make_unique<Wt::WContainerWidget>());
    statsContainer->setStyleClass("dashboard-stats");

    auto stats1 = statsContainer->addWidget(std::make_unique<Wt::WText>("<div class='stat-card'>Users: 150</div>"));
    stats1->setTextFormat(Wt::TextFormat::UnsafeXHTML);

    auto stats2 = statsContainer->addWidget(std::make_unique<Wt::WText>("<div class='stat-card'>Active: 45</div>"));
    stats2->setTextFormat(Wt::TextFormat::UnsafeXHTML);

    auto stats3 = statsContainer->addWidget(std::make_unique<Wt::WText>("<div class='stat-card'>Reports: 12</div>"));
    stats3->setTextFormat(Wt::TextFormat::UnsafeXHTML);
}