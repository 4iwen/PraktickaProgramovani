#include <HTTPRequest.hpp>
#include <string>
#include <cstdio>
#include <iostream>
#include <nlohmann/json.hpp>

int main() {
    http::Request request("http://maturita.delta-www.cz/prakticka/2023-map/mapData/");

    auto response = request.send("GET");

    printf("Status: %d\n", response.status.code);

    nlohmann::json json = nlohmann::json::parse(response.body);

    std::cout << json.dump(4) << std::endl;

    return 0;
}