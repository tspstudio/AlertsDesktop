#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QVBoxLayout>

std::string stateList[] = {
    "АР Крим",
    "Вінницька область",
    "Волинська область",
    "Дніпропетровська область",
    "Донецька область",
    "Житомирська область",
    "Закарпатська область",
    "Запорізька область",
    "Івано-Франківська область",
    "Київська область",
    "Кіровоградська область",
    "Луганська область",
    "Львівська область",
    "Миколаївська область",
    "Одеська область",
    "Полтавська область",
    "Рівненська область",
    "Сумська область",
    "Тернопільська область",
    "Харківська область",
    "Херсонська область",
    "Хмельницька область",
    "Черкаська область",
    "Чернівецька область",
    "Чернігівська область",
    "м. Київ"
};

MainWindow::MainWindow(QWidget *parent, std::string* state, bool *stateChanged, bool *mustReload)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , noData(QIcon("res/images/noData.png"))
    , dissmisal(QIcon("res/images/dissmisal.png"))
    , airRaid(QIcon("res/images/airRaid.png"))
    , state(state)
    , stateChanged(stateChanged)
    , mustReload(mustReload)
{
    ui->setupUi(this);

    QIcon settingsIcon("res/images/settings.png");
    QIcon reloadIcon("res/images/reload.png");

    ui->settingsButton->setIcon(settingsIcon);
    ui->settingsButton->setIconSize(QSize(20, 20));
    ui->reloadButton->setIcon(reloadIcon);

    for (const std::string &s : stateList)
    {
        ui->stateMenu->addItem(QString::fromStdString(s));
    }
    ui->stateMenu->setCurrentIndex(-1);

    connect(ui->stateMenu, &QComboBox::currentIndexChanged, this, &MainWindow::stateMenuIndexChanged);
    connect(ui->reloadButton, &QPushButton::clicked, this, &MainWindow::reloadButtonClicked);

    
}

void MainWindow::setStatus(Status status)
{
    switch (status)
    {
        case NO_DATA: ui->statusIcon->setIcon(noData); ui->statusLabel->setText("Немає даних"); break;
        case DISSMISAL: ui->statusIcon->setIcon(dissmisal); ui->statusLabel->setText("Немає тривоги"); break;
        case AIR_RAID: ui->statusIcon->setIcon(airRaid); ui->statusLabel->setText("Повітряна тривога"); break;
        default: break;
    }
}

void MainWindow::setTimer(int time)
{
    ui->reloadButton->setText(QString::number(time));
}

void MainWindow::stateMenuIndexChanged(int index)
{
    *state = stateList[index];
    *stateChanged = true;
}

void MainWindow::reloadButtonClicked()
{
    *mustReload = true;
}

MainWindow::~MainWindow()
{
    delete ui;
}
