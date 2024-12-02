#ifndef FIGHTVISITOR_H
#define FIGHTVISITOR_H

#include "NPCVisitor.h"
#include "Observer.h"
#include "NPCManager.h"
#include <vector>
#include <memory>
#include <unordered_set>
#include <unordered_map>

class FightVisitor : public NPCVisitor {
public:
    struct PairHash {
        std::size_t operator()(const std::pair<NPC*, NPC*>& pair) const {
            return std::hash<NPC*>()(pair.first) ^ std::hash<NPC*>()(pair.second);
        }
    };
    FightVisitor(NPCManager& manager);
    void addObserver(std::shared_ptr<Observer> observer);
    void resetProcessedFights();
    void visit(Squirrel& squirrel) override;
    void visit(Elf& elf) override;
    void visit(Robber& robber) override;
    std::unordered_map<NPC*, NPC*> getTargets();

private:
    void fight(NPC& attacker, NPC& defender);
    void notify(const std::string& message);
    double distance(NPC& a, NPC& b);

    NPCManager& npcManager;
    std::vector<std::shared_ptr<Observer>> observers;
    std::unordered_set<std::pair<NPC*, NPC*>, PairHash> processedFights;
    std::unordered_map<NPC*, NPC*> targets;

    
};

#endif // FIGHTVISITOR_H
