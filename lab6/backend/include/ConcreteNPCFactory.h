#ifndef CONCRETENPCFACTORY_H
#define CONCRETENPCFACTORY_H

#include "NPCFactory.h"

class ConcreteNPCFactory : public NPCFactory {
public:
    std::shared_ptr<NPC> createNPC(const std::string& type, const std::string& name, double x, double y) override;
};

#endif // CONCRETENPCFACTORY_H
