// backend/src/NPCManager.cpp

#include "NPCManager.h"
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
