// backend/include/NPCFactory.h

#ifndef NPCFACTORY_H
#define NPCFACTORY_H

#include <string>
#include <memory>
#include "NPC.h"

class NPCFactory {
public:
    virtual ~NPCFactory() = default;
    virtual std::shared_ptr<NPC> createNPC(const std::string& type, const std::string& name, double x, double y) = 0;
};

#endif // NPCFACTORY_H
