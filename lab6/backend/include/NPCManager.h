#ifndef NPCMANAGER_H
#define NPCMANAGER_H

#include "NPC.h"
#include <vector>
#include <memory>
#include <string>

class NPCManager {
public:
    NPCManager();
    void addNPC(std::shared_ptr<NPC> npc);
    std::vector<std::shared_ptr<NPC>>& getNPCs();
    void removeDeadNPCs();
    void loadNPCsFromFile(const std::string& filename);

private:
    std::vector<std::shared_ptr<NPC>> npcs;
};

#endif // NPCMANAGER_H
