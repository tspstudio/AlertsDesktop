#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <libnotify/notify.h>
#include <chrono>
#include <atomic>
#include <thread>
#include <QApplication>
#include <QSvgWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSvgItem>

#include "Network.h"
#include "mainwindow.h"
#include "ReadFile.h"
#include "Status.h"
#include "Map.h"

using json = nlohmann::json;
bool stateChanged = false;
bool mustReload = false;
std::vector<State> _states;

std::string _stateList[] = {
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

void networkWorker(std::atomic<bool> &running, Network &network, json &states, std::string &state, MainWindow &window)
{
    bool lastState = false;

    int timer = 10;

    std::cout << "Network worker started" << std::endl;

    

    while (running) {
        std::string airRaidMessage = "Оголошено повітряну тривогу у " + state;
        NotifyNotification* airRaid = notify_notification_new ("Повітряна тривога", 
                                    airRaidMessage.c_str(),
                                    "res/images/airRaid.png");
        
        std::string dissmisalMessage = "Відбій повітряної тривоги у " + state;
        NotifyNotification* dissmisal = notify_notification_new ("Відбій повтіряної тривоги", 
            dissmisalMessage.c_str(),
            "res/images/dissmisal.png");
        if (timer == 1 || mustReload)
        {   
            if (state != "Не вибрано") {
                if (!stateChanged)
                {
                    json data = network.getJson(network.getRaw());
                    if (data == json{})
                    {
                        states = json{};
                        break;
                    }
                    if (lastState != data["states"][state]["enabled"])
                    {
                        if (data["states"][state]["enabled"])
                        {
                            notify_notification_show(airRaid, 0);
                        } else {
                            notify_notification_show(dissmisal, 0);
                        }
                    } else {
                        //std::cout << "Nothing changed after last check!" << lastState << std::endl;
                    }
                    window.setStatus(data["states"][state]["enabled"] ? Status::AIR_RAID : Status::DISSMISAL);
                    lastState = data["states"][state]["enabled"];
                    states = data;
                } else {
                    json data = network.getJson(network.getRaw());
                    if (data == json{})
                    {
                        states = json{};
                        break;
                    }
                    if (data["states"][state]["enabled"])
                    {
                        notify_notification_show(airRaid, 0);
                    }
                    window.setStatus(data["states"][state]["enabled"] ? Status::AIR_RAID : Status::DISSMISAL);
                    lastState = data["states"][state]["enabled"];
                    states = data;
                    stateChanged = false;
                }
                
                timer = 10;
                mustReload = false;
                for (int i = 0; i <= 25; i++)
                {
                    _states[i].setStatus(states["states"][_stateList[i]]["enabled"]);
                }
            } else {
                json data = network.getJson(network.getRaw());
                if (data == json{})
                {
                    states = json{};
                    break;
                }
                timer = 10;
                mustReload = false;
                states = data;
                for (int i = 0; i <= 25; i++)
                {
                    _states[i].setStatus(states["states"][_stateList[i]]["enabled"]);
                }
            }
        } else {
            timer--;
        }
        window.setTimer(timer);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

int main(int argc, char *argv[]) {
    notify_init("Alerts Desktop");

    std::string state = "Не вибрано";

    Network network("https://vadimklimenko.com/map/statuses.json");

    QApplication a(argc, argv);

    a.setStyleSheet(QString(readFile("res/window.css").c_str())); // fuck this code

    MainWindow w(nullptr, &state, &stateChanged, &mustReload);
    w.show();
    
    std::atomic<bool> running(true);

    json states;

    std::thread networkThread(networkWorker, std::ref(running), std::ref(network), std::ref(states), std::ref(state), std::ref(w));

    w.setStatus(Status::NO_DATA);

    
    for (size_t i = 0; i < std::size(_stateList); ++i) {
        std::string activeImage = "res/images/states/" + std::to_string(i) + "-1.png";
        std::string inactiveImage = "res/images/states/" + std::to_string(i) + "-0.png";
        _states.emplace_back(activeImage, inactiveImage, _stateList[i], &w);
    }

    while (!w.isHidden()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        a.processEvents();
    }

    running = false;
    networkThread.join();

    return 0;
}