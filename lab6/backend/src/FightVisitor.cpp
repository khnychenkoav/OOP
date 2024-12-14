#include "FightVisitor.h"
#include "Squirrel.h"
#include "Elf.h"
#include "Robber.h"
#include <cmath>
#include <algorithm>
#include <random>
#include <mutex>
#include <thread>
#include <shared_mutex>


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
    std::lock_guard<std::shared_mutex> lock(fightMutex);
    processedFights.clear();
    targets.clear();
}

void FightVisitor::fight(NPC& attacker, NPC& defender) {
    npcManager.logStatus("Fight started: " + attacker.getName() + " vs " + defender.getName());

    if (!attacker.isAlive() || !defender.isAlive()){
            npcManager.logStatus("Aborting fight: one of the participants is dead.");

            return;
        }
        auto fightPair = std::make_pair(&attacker, &defender);
        if (processedFights.find(fightPair) != processedFights.end()) {
            npcManager.logStatus("Fight already processed: " + attacker.getName() + " vs " + defender.getName());
            return;
        }
        processedFights.insert(fightPair);

    while (defender.getHealth() > 0 && attacker.getHealth() > 0) {
        
        

        double dist = distance(attacker, defender);
        targets[&attacker] = &defender;

        if (dist <= attacker.getAttackRange()) {
            npcManager.logStatus("Attack range met: " + attacker.getName() + " vs " + defender.getName());
            int attackRoll = rand() % 6 + 1;
            int defenseRoll = rand() % 6 + 1;
            npcManager.logStatus("Attack roll: " + std::to_string(attackRoll) + ", defense roll: " + std::to_string(defenseRoll));
            int damage = attackRoll - defenseRoll + attacker.getDamage();
            npcManager.logStatus("Damage: " + std::to_string(damage));
            int defenderHealth = defender.getHealth() - damage;
            npcManager.logStatus("Defender health: " + std::to_string(defenderHealth));
            defender.setHealth(defenderHealth);
            npcManager.logStatus("Defender health set to: " + std::to_string(defender.getHealth()));
            notify(attacker.getType() + " " + attacker.getName() + " attacked " + defender.getType() + " " + defender.getName() + " for " + std::to_string(damage) + " damage");
            if (defenderHealth <= 0) {
                defender.die();
                notify(defender.getType() + " " + defender.getName() + " was defeated");
            }
        }
    }
}

void FightVisitor::visit(Squirrel& squirrel) {
    auto& npcs = npcManager.getNPCs();
    for (auto& npc : npcs) {
        if (npc.get() == &squirrel || !npc->isAlive() || distance(squirrel, *npc) > squirrel.getAttackRange()) continue;
        if (npc->getType() == "Elf") {
            fight(squirrel, *npc);
        }
    }
}

void FightVisitor::visit(Elf& elf) {
    auto& npcs = npcManager.getNPCs();
    for (auto& npc : npcs) {
        if (npc.get() == &elf || !npc->isAlive() || distance(elf, *npc) > elf.getAttackRange()) continue;
        if (npc->getType() == "Robber") {
            fight(elf, *npc);
        }
    }
}

void FightVisitor::visit(Robber& robber) {
    auto& npcs = npcManager.getNPCs();
    for (auto& npc : npcs) {
        if (npc.get() == &robber || !npc->isAlive() || distance(robber, *npc) > robber.getAttackRange()) continue;
        if (npc->getType() == "Squirrel") {
            fight(robber, *npc);
        }
    }
}

std::unordered_map<NPC*, NPC*> FightVisitor::getTargets() {
    std::lock_guard<std::shared_mutex> lock(fightMutex);
    return targets;
}

Generator<std::monostate> FightVisitor::runCorutines() {
    while (npcManager.isRunning()) {
        npcManager.logStatus("RunCoroutines step started.");

        auto npcs = npcManager.getNPCs();
        npcManager.logStatus("Alive NPCs: " + std::to_string(npcs.size()));
        {
            std::lock_guard<std::shared_mutex> lock(movementMutex);

            for (auto& npc : npcs) {
                if (!npc->isAlive()) {
                    npcManager.logStatus(npc->getName() + " is dead.");
                    continue;
                }

                NPC* target = nullptr;
                NPC* threat = nullptr;
                double minTargetDistance = std::numeric_limits<double>::max();
                double minThreatDistance = std::numeric_limits<double>::max();

                for (auto& otherNpc : npcs) {
                    if (npc.get() == otherNpc.get() || !otherNpc->isAlive()) continue;

                    double distanceToOther = distance(*npc, *otherNpc);

                    if ((npc->getType() == "Elf" && otherNpc->getType() == "Robber") ||
                        (npc->getType() == "Robber" && otherNpc->getType() == "Squirrel") ||
                        (npc->getType() == "Squirrel" && otherNpc->getType() == "Elf")) {
                        if (distanceToOther < minTargetDistance) {
                            target = otherNpc.get();
                            minTargetDistance = distanceToOther;
                        }
                    }

                    if ((npc->getType() == "Elf" && otherNpc->getType() == "Squirrel") ||
                        (npc->getType() == "Robber" && otherNpc->getType() == "Elf") ||
                        (npc->getType() == "Squirrel" && otherNpc->getType() == "Robber")) {
                        if (distanceToOther < minThreatDistance) {
                            threat = otherNpc.get();
                            minThreatDistance = distanceToOther;
                        }
                    }
                }

                npcManager.logStatus(npc->getName() + " is processing.");
                if (target) {
                    npc->moveTowards(target->getX(), target->getY());
                    npcManager.logStatus(npc->getName() + " moves towards " + target->getName());
                } else if (threat) {
                    npc->moveAwayFrom(threat->getX(), threat->getY());
                    npcManager.logStatus(npc->getName() + " moves away from " + threat->getName());
                } else {
                    npc->move();
                    npcManager.logStatus(npc->getName() + " moves randomly.");
                }
            }
        }

        npcManager.logStatus("RunCoroutines step completed.");

        co_yield std::monostate{};
    }
    npcManager.logStatus("RunCoroutines finished.");
}
