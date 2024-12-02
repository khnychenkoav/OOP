// backend/src/FightVisitor.cpp

#include "FightVisitor.h"
#include "Squirrel.h"
#include "Elf.h"
#include "Robber.h"
#include <cmath>
#include <algorithm>
#include <iostream>


FightVisitor::FightVisitor(NPCManager& manager, double fightDistance)
    : npcManager(manager), fightDistance(fightDistance) {}

void FightVisitor::addObserver(std::shared_ptr<Observer> observer) {
    observers.push_back(observer);
}

void FightVisitor::notify(const std::string& message) {
    for (auto& observer : observers) {
        observer->update(message);
    }
}

double FightVisitor::distance(NPC& a, NPC& b) {
    double dx = a.getX() - b.getX();
    double dy = a.getY() - b.getY();
    return std::hypot(dx, dy);
}

void FightVisitor::resetProcessedFights() {
    processedFights.clear();
    targets.clear();
}

void FightVisitor::fight(NPC& attacker, NPC& defender, bool canBothDie) {
    if (!attacker.isAlive() || !defender.isAlive()) return;
    auto fightPair = std::make_pair(&attacker, &defender);
    if (processedFights.find(fightPair) != processedFights.end()) {
        return;  // Fight already processed
    }
    processedFights.insert(fightPair);

    double dist = distance(attacker, defender);
    std::cout << "Attempting fight between " << attacker.getType() << " " << attacker.getName()
              << " and " << defender.getType() << " " << defender.getName()
              << " at distance " << dist << std::endl;

    // Store the target for visualization
    targets[&attacker] = &defender;

    if (dist <= fightDistance) {
        defender.die();
        notify(attacker.getType() + " " + attacker.getName() + " killed " + defender.getType() + " " + defender.getName());
        if (canBothDie && rand() % 2 == 0) {
            attacker.die();
            notify(defender.getType() + " " + defender.getName() + " also killed " + attacker.getType() + " " + attacker.getName());
        }
    }
}

void FightVisitor::visit(Squirrel& squirrel) {
    auto& npcs = npcManager.getNPCs();
    for (auto& npc : npcs) {
        if (npc.get() == &squirrel || !npc->isAlive()) continue;
        if (npc->getType() == "Elf") {
            fight(squirrel, *npc, true);  // Squirrel attacks Elf
        }
    }
}

void FightVisitor::visit(Elf& elf) {
    auto& npcs = npcManager.getNPCs();
    for (auto& npc : npcs) {
        if (npc.get() == &elf || !npc->isAlive()) continue;
        if (npc->getType() == "Robber") {
            fight(elf, *npc, false);  // Elf attacks Robber
        }
    }
}

void FightVisitor::visit(Robber& robber) {
    auto& npcs = npcManager.getNPCs();
    for (auto& npc : npcs) {
        if (npc.get() == &robber || !npc->isAlive()) continue;
        if (npc->getType() == "Squirrel") {
            fight(robber, *npc, false);  // Robber attacks Squirrel
        }
    }
}

std::unordered_map<NPC*, NPC*> FightVisitor::getTargets() {
    return targets;
}
