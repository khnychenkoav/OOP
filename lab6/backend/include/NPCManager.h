#ifndef NPCMANAGER_H
#define NPCMANAGER_H

#include "NPC.h"
#include "CustomGenerator.h"
#include "FightVisitor.h"
#include <vector>
#include <memory>
#include <string>
#include <shared_mutex>
#include <mutex>
#include <atomic>
#include <coroutine>
#include <iostream>
#include <thread>
#include <functional>
#include <generator>

class FightVisitor;

class NPCManager {
public:
    NPCManager();
    ~NPCManager();
    void addNPC(std::shared_ptr<NPC> npc);
    std::vector<std::shared_ptr<NPC>>& getNPCs();
    void removeDeadNPCs();
    void loadNPCsFromFile(const std::string& filename);
    void logStatus(const std::string& message);
    void startThreads();
    void stopThreads();
    bool isRunning() const;
    int getActiveThreadsCount() const;


private:
    std::vector<std::shared_ptr<NPC>> npcs;
    mutable std::shared_mutex mutex;
    std::atomic<bool> running;
    std::thread movementThread;
    std::thread combatThread;
    std::thread renderThread;
    std::atomic<int> activeThreads;
    std::mutex logMutex;
    FightVisitor* visitor;
    
};

#endif // NPCMANAGER_H
