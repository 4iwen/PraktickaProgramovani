#include "Application.h"
#include <imgui.h>
#include <nlohmann/json.hpp>
#include <HTTPRequest.hpp>
#include <iostream>

using namespace nlohmann;

Application::Application() {
    m_window = std::make_unique<Window>();
}

#define BUFFER_SIZE 1024

struct Seller {
    std::string uuid;
    bool top = false;
    std::string surname;
    std::vector<std::string> names;
    int sales = 0;
    std::vector<std::string> subordinates;
};

std::string joinNames(const std::vector<std::string> &names) {
    std::string result;

    for (auto nameIt = names.begin(); nameIt != names.end(); ++nameIt) {
        result.append((*nameIt));
        if (nameIt != names.end() - 1) {
            result.append(", ");
        }
    }

    return result;
}

void tree(std::vector<Seller> sellers, std::vector<std::string> subordinates, const std::string &path,
          char searchBuffer[BUFFER_SIZE]) {

    if (subordinates.empty()) {
        ImGui::Text("This seller has no subordinates");

        return;
    }

    for (auto subIter = subordinates.begin(); subIter != subordinates.end(); ++subIter) {
        std::string subUuid = (*subIter);

        for (auto sellerIter = sellers.begin(); sellerIter != sellers.end(); ++sellerIter) {
            if (subUuid == (*sellerIter).uuid) {
                std::string treeName = std::string(
                        (*sellerIter).surname + ", " + joinNames((*sellerIter).names) + " (" +
                        std::to_string((*sellerIter).sales) + " $)"
                );
                std::string newPath = path;
                newPath.append(" => " + (*sellerIter).surname + ", " + joinNames((*sellerIter).names));

                if (ImGui::TreeNode(treeName.c_str())) {
                    tree(sellers, (*sellerIter).subordinates, newPath, searchBuffer);

                    ImGui::TreePop();
                }
                if (ImGui::IsItemHovered()) {
                    ImGui::SetTooltip("%s", newPath.c_str());
                }
            }
        }
    }
}

void Application::run() {
    http::Request request("http://maturita.delta-www.cz/prakticka/2024-obchodnici/network");
    auto response = request.send("GET");

    if (response.status.code != 200) {
        return;
    }

    json json = json::parse(response.body);

    std::cout << json.dump(4) << std::endl;

    int setId = json["setId"];
    auto network = json["networkJSON"];

    std::vector<Seller> sellers;
    std::vector<Seller> filteredSellers;

    for (auto it = network.begin(); it != network.end(); ++it) {
        std::string uuid = (*it)["UUID"];
        bool top = false;
        if ((*it).contains("top")) {
            top = (*it)["top"];
        }
        std::string surname = (*it)["surname"];
        auto names = (*it)["names"];
        int sales = (*it)["sales"];
        auto subordinates = (*it)["subordinates"];

        std::vector<std::string> namesVec;
        for (auto nameIt = names.begin(); nameIt != names.end(); ++nameIt) {
            namesVec.push_back(nameIt.value());
        }

        std::vector<std::string> subordinatesVec;
        for (auto subordinatesIt = subordinates.begin(); subordinatesIt != subordinates.end(); ++subordinatesIt) {
            subordinatesVec.push_back(subordinatesIt.value());
        }

        sellers.push_back({uuid, top, surname, namesVec, sales, subordinatesVec});
    }

    while (m_window->isOpen()) {
        m_window->begin();

        m_window->beginUI();

        ImGui::ShowDemoWindow();

        ImGui::Begin("Sit MLM");
        ImGui::Text("setId: %d", setId);

        static char searchBuffer[BUFFER_SIZE];
        ImGui::InputText("Search", searchBuffer, BUFFER_SIZE);

        Seller topSeller;
        filteredSellers.clear();
        for (auto it = sellers.begin(); it != sellers.end(); ++it) {
            bool top = (*it).top;
            if (top) {
                topSeller = (*it);
            }

            std::string uuid = (*it).uuid;
            std::string surname = (*it).surname;
            std::vector<std::string> names = (*it).names;
            int sales = (*it).sales;
            std::vector<std::string> subordinates = (*it).subordinates;

            // filtrovani / hledani funguje jen castecne - nefunguje do hloubky
            if (uuid.find(searchBuffer, 0) != std::string::npos ||
                surname.find(searchBuffer, 0) != std::string::npos) {
                filteredSellers.push_back((*it));

                /*for (auto sellIter = sellers.begin(); sellIter != sellers.end(); ++sellIter) {
                    if ((*sellIter).uuid == (*it).uuid) {
                        filteredSellers.push_back((*it));
                    }
                }*/
            }
        }

        std::string nameStr = joinNames(topSeller.names);
        std::string treeName = std::string(
                topSeller.surname + ", " + nameStr + " (" + std::to_string(topSeller.sales) + " $)"
        );

        if (ImGui::TreeNode(treeName.c_str())) {
            std::string path = topSeller.surname + ", " + nameStr;
            tree(filteredSellers, topSeller.subordinates, path, searchBuffer);

            ImGui::TreePop();
        }

        const char *sellersCStr[1] = {
                // nacist jen jména obchodníků na výběr
        };
        static int selected = 0;
        ImGui::Combo("Select seller", &selected, sellersCStr, IM_ARRAYSIZE(sellersCStr));
        // projit rekurzivne vsechny podobchodníky -> suma vsech jejich prodeju + vybrany obchodnik prodeje

        // int salesSum = 0;
        // ImGui::Text("Combined sales: %d", salesSum);

        ImGui::End();

        m_window->endUI();

        m_window->end();
    }
}