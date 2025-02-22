#ifndef NETWORK_H
#define NETWORK_H

#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <string>

using json = nlohmann::json;

class Network {
private:
    CURL* curl;
public:
    Network(std::string url);
    ~Network();

    std::string getRaw();
    json getJson(std::string data);
};

#endif // NETWORK_H