// backend/include/FightVisitor.h

#ifndef FIGHTVISITOR_H
#define FIGHTVISITOR_H

#include "NPCVisitor.h"
#include "NPC.h"
#include "Observer.h"
#include "NPCManager.h"
#include <vector>
#include <memory>
#include <unordered_set>
#include <utility>
#include <unordered_map>

// Define a custom hash for std::pair<NPC*, NPC*>
struct pair_hash {
    std::size_t operator()(const std::pair<NPC*, NPC*>& p) const {
        // A simple combination of hashes; consider using a better combination if needed
        return std::hash<NPC*>()(p.first) ^ (std::hash<NPC*>()(p.second) << 1);
    }
};

class FightVisitor : public NPCVisitor {
public:
    FightVisitor(NPCManager& manager, double fightDistance);
    void visit(Squirrel& squirrel) override;
    void visit(Elf& elf) override;
    void visit(Robber& robber) override;
    void addObserver(std::shared_ptr<Observer> observer);
    void resetProcessedFights();
    std::unordered_map<NPC*, NPC*> getTargets();

private:
    NPCManager& npcManager;
    double fightDistance;
    std::vector<std::shared_ptr<Observer>> observers;
    void notify(const std::string& message);
    void fight(NPC& attacker, NPC& defender, bool canBothDie);
    double distance(NPC& a, NPC& b);
    std::unordered_set<std::pair<NPC*, NPC*>, pair_hash> processedFights;  // Uses custom hash
    std::unordered_map<NPC*, NPC*> targets;  // Map from attacker to target
};

#endif // FIGHTVISITOR_H
