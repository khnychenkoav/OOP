// backend/src/NPCManager.cpp

#include "NPCManager.h"
#include "ConcreteNPCFactory.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

NPCManager::NPCManager() {}

void NPCManager::addNPC(std::shared_ptr<NPC> npc) {
    npcs.push_back(npc);
}

std::vector<std::shared_ptr<NPC>>& NPCManager::getNPCs() {
    return npcs;
}

void NPCManager::removeDeadNPCs() {
    npcs.erase(
        std::remove_if(npcs.begin(), npcs.end(), [](const std::shared_ptr<NPC>& npc) {
            return !npc->isAlive();
        }),
        npcs.end());
}

void NPCManager::loadNPCsFromFile(const std::string& filename) {
    npcs.clear();
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Failed to open NPCs file: " << filename << std::endl;
        return;
    }

    ConcreteNPCFactory factory;
    std::string line;
    while (std::getline(infile, line)) {
        std::stringstream ss(line);
        std::string type, name;
        double x, y;
        int health;
        if (ss >> type >> name >> x >> y >> health) {
            auto npc = factory.createNPC(type, name, x, y);
            if (npc) {
                npc->setHealth(health);
                addNPC(npc);
            }
        }
    }
    infile.close();
}
