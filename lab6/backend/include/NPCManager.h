// backend/include/NPCManager.h

#ifndef NPCMANAGER_H
#define NPCMANAGER_H

#include "NPC.h"
#include <vector>
#include <memory>

class NPCManager {
public:
    NPCManager();
    void addNPC(std::shared_ptr<NPC> npc);
    std::vector<std::shared_ptr<NPC>>& getNPCs();
    void removeDeadNPCs();

private:
    std::vector<std::shared_ptr<NPC>> npcs;
};

#endif // NPCMANAGER_H
