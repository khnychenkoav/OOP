#include "FightVisitor.h"
#include "Squirrel.h"
#include "Elf.h"
#include "Robber.h"
#include <cmath>
#include <algorithm>

FightVisitor::FightVisitor(NPCManager& manager)
    : npcManager(manager) {}

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

void FightVisitor::fight(NPC& attacker, NPC& defender) {
    if (!attacker.isAlive() || !defender.isAlive()) return;
    auto fightPair = std::make_pair(&attacker, &defender);
    if (processedFights.find(fightPair) != processedFights.end()) {
        return;
    }
    processedFights.insert(fightPair);

    double dist = distance(attacker, defender);
    targets[&attacker] = &defender;

    if (dist <= attacker.getAttackRange()) {
        int damage = attacker.getDamage();
        int defenderHealth = defender.getHealth() - damage;
        defender.setHealth(defenderHealth);
        notify(attacker.getType() + " " + attacker.getName() + " attacked " + defender.getType() + " " + defender.getName() + " for " + std::to_string(damage) + " damage");
        if (defenderHealth <= 0) {
            defender.die();
            notify(defender.getType() + " " + defender.getName() + " was defeated");
        }
    }
}

void FightVisitor::visit(Squirrel& squirrel) {
    auto& npcs = npcManager.getNPCs();
    for (auto& npc : npcs) {
        if (npc.get() == &squirrel || !npc->isAlive()) continue;
        if (npc->getType() == "Elf") {
            fight(squirrel, *npc);
        }
    }
}

void FightVisitor::visit(Elf& elf) {
    auto& npcs = npcManager.getNPCs();
    for (auto& npc : npcs) {
        if (npc.get() == &elf || !npc->isAlive()) continue;
        if (npc->getType() == "Robber") {
            fight(elf, *npc);
        }
    }
}

void FightVisitor::visit(Robber& robber) {
    auto& npcs = npcManager.getNPCs();
    for (auto& npc : npcs) {
        if (npc.get() == &robber || !npc->isAlive()) continue;
        if (npc->getType() == "Squirrel") {
            fight(robber, *npc);
        }
    }
}

std::unordered_map<NPC*, NPC*> FightVisitor::getTargets() {
    return targets;
}
