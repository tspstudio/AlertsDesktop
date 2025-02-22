#include "Map.h"

State::State(std::string iconEnabledPath, std::string iconDisabledPath, std::string name, MainWindow *window)
    : iconEnabled(QIcon(iconEnabledPath.c_str()))
    , iconDisabled(QIcon(iconDisabledPath.c_str()))
    , name(name)
    , enabled(false)
    , button(new QPushButton(window))
{
    button->setObjectName("mapState");
    button->setEnabled(false);
    button->setGeometry(0, 0, 1280, 540);
    button->setIcon(iconDisabled);
    button->setIconSize(button->size());
    button->show();
}

State::~State()
{
    //delete this;
}

void State::setStatus(bool status)
{
    button->setIcon(status ? iconEnabled : iconDisabled);
}