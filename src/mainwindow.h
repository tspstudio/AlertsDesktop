#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <iostream>
#include <QSvgWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSvgItem>
#include <QSvgRenderer>
#include <QPainter>
#include <QFile>
#include <QRegularExpression>
#include "Status.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, std::string* state = nullptr, bool *stateChanged = nullptr, bool *mustReload = nullptr);
    ~MainWindow();

    void setStatus(Status status);
    void setTimer(int time);
    void setStateStatus();

    QIcon noData;
    QIcon airRaid;
    QIcon dissmisal;

    std::string *state;

    bool *stateChanged;
    bool *mustReload;

    Ui::MainWindow *ui;

private slots:
    void stateMenuIndexChanged(int index);
    void reloadButtonClicked();
};
#endif // MAINWINDOW_H
