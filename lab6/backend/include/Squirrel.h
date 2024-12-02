// backend/include/Squirrel.h

#ifndef SQUIRREL_H
#define SQUIRREL_H

#include "NPC.h"

class Squirrel : public NPC {
public:
    Squirrel(const std::string& name, double x, double y);
    void accept(NPCVisitor& visitor) override;
    std::string getName() const override;
    std::string getType() const override;
    double getX() const override;
    double getY() const override;
    int getHealth() const override;
    void setHealth(int health) override;
    int getDamage() const override;
    double getAttackRange() const override;
    void setAttackRange(double range) override;
    bool isAlive() const override;
    void die() override;
    void setPosition(double x, double y) override;
    void move() override;
    void moveTowards(double targetX, double targetY) override;
    void moveAwayFrom(double targetX, double targetY) override;

private:
    std::string name;
    double x, y;
    int health;
    int damage;
    double attackRange;
    bool alive;
};

#endif // SQUIRREL_H
