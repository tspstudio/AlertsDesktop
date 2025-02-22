#include "Network.h"

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

Network::Network(std::string url) {
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    }
}

Network::~Network() {
    curl_easy_cleanup(curl);
}

std::string Network::getRaw() {
    CURLcode res;
    std::string dataBuffer;

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &dataBuffer);

    res = curl_easy_perform(curl);

    if (res == CURLE_OK) {
        return dataBuffer;
    } else {
        std::cerr << "cURL Error: " << curl_easy_strerror(res) << std::endl;
        return "{}";
    }
}

json Network::getJson(std::string data) {
    try {
        return json::parse(data.c_str());

    } catch (json::parse_error& e) {
        std::cerr << "JSON Parsing Error: " << e.what() << std::endl;
        return json{};
    }
}