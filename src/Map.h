#ifndef MAP_H
#define MAP_H

#include "mainwindow.h"
#include <QPushButton>
#include <string>

class State
{
public:
    QIcon iconEnabled;
    QIcon iconDisabled;

    std::string name;

    bool enabled;

    QPushButton *button;

    State(std::string iconEnabled, std::string iconDisabled, std::string name, MainWindow *window);
    ~State();

    void setStatus(bool status);
};

#endif