#include "ConcreteNPCFactory.h"
#include "Squirrel.h"
#include "Elf.h"
#include "Robber.h"

std::shared_ptr<NPC> ConcreteNPCFactory::createNPC(const std::string& type, const std::string& name, double x, double y) {
    if (type == "Squirrel") {
        return std::make_shared<Squirrel>(name, x, y);
    } else if (type == "Elf") {
        return std::make_shared<Elf>(name, x, y);
    } else if (type == "Robber") {
        return std::make_shared<Robber>(name, x, y);
    }
    return nullptr;
}
