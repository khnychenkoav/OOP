#include "NPCManager.h"
#include "FightVisitor.h"
#include "ConcreteNPCFactory.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

void NPCManager::addNPC(std::shared_ptr<NPC> npc) {
    std::lock_guard<std::shared_mutex> lock(mutex);
    npcs.push_back(npc);
}

std::vector<std::shared_ptr<NPC>>& NPCManager::getNPCs() {
    std::shared_lock<std::shared_mutex> lock(mutex);
    return npcs;
}

void NPCManager::removeDeadNPCs() {
    std::lock_guard<std::shared_mutex> lock(mutex);
    auto initialSize = npcs.size();
    npcs.erase(
        std::remove_if(npcs.begin(), npcs.end(), [](const std::shared_ptr<NPC>& npc) {
            return !npc->isAlive();
        }),
        npcs.end());
    logStatus("Removed dead NPCs. Count: " + std::to_string(initialSize - npcs.size()));
}


void NPCManager::logStatus(const std::string& message) {
    std::lock_guard<std::mutex> lock(logMutex);
    std::cout << message << std::endl;
}

NPCManager::NPCManager() : running(false), activeThreads(0){
    visitor = new FightVisitor(*this);
}

void NPCManager::startThreads() {
    running = true;
    movementThread = std::thread([this]() {
        ++activeThreads;
        logStatus("Movement thread started");
        auto coroutine = visitor->runCorutines();
        while (isRunning()) {
            try {
                if (!coroutine.done()) {
                    coroutine.next();
                }
            } catch (const std::exception& e) {
                logStatus(std::string("Error in movement thread: ") + e.what());
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
        }
        logStatus("Movement thread stopped");
        --activeThreads;
    });

    combatThread = std::thread([this]() {
        ++activeThreads;
        logStatus("Combat thread started");
        FightVisitor visitor(*this);
        while (isRunning()) {
            auto npcs = getNPCs();
            for (auto& npc : npcs) {
                if (npc->isAlive()) npc->accept(visitor);
            }
            removeDeadNPCs();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        logStatus("Combat thread stopped");
        --activeThreads;
    });
    renderThread = std::thread([this]() {
        ++activeThreads;
        logStatus("Render thread started");
        while (isRunning()) {
            logStatus("Rendering map...");
            auto npcs = getNPCs();
            for (const auto& npc : npcs) {
                if (npc->isAlive()) {
                    logStatus(npc->getType() + " at (" + std::to_string(npc->getX()) + ", " + std::to_string(npc->getY()) + ")");
                }
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        logStatus("Render thread stopped");
        --activeThreads;
    });
}

void NPCManager::stopThreads() {
    running = false;
    if (movementThread.joinable()) movementThread.join();
    if (combatThread.joinable()) combatThread.join();
    if (renderThread.joinable()) renderThread.join();
    logStatus("All threads stopped.");
}

bool NPCManager::isRunning() const {
    return running.load();
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

int NPCManager::getActiveThreadsCount() const {
    return activeThreads.load();
}


NPCManager::~NPCManager() {
    delete visitor;
}
