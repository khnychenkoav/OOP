// backend/include/NPC.h

#ifndef NPC_H
#define NPC_H

#include <string>
#include "NPCVisitor.h"

class NPC {
public:
    virtual ~NPC() = default;
    virtual void accept(NPCVisitor& visitor) = 0;
    virtual std::string getName() const = 0;
    virtual std::string getType() const = 0;
    virtual double getX() const = 0;
    virtual double getY() const = 0;
    virtual int getHealth() const = 0;
    virtual void setHealth(int health) = 0;
    virtual int getDamage() const = 0;
    virtual double getAttackRange() const = 0;
    virtual void setAttackRange(double range) = 0;
    virtual bool isAlive() const = 0;
    virtual void die() = 0;
    virtual void setPosition(double x, double y) = 0;
    virtual void move() = 0;
    virtual void moveTowards(double targetX, double targetY) = 0;
    virtual void moveAwayFrom(double targetX, double targetY) = 0; // Новый метод
};

#endif // NPC_H
