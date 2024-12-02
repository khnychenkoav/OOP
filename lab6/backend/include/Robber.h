// backend/include/Robber.h

#ifndef ROBBER_H
#define ROBBER_H

#include "NPC.h"

class Robber : public NPC {
public:
    Robber(const std::string& name, double x, double y);
    void accept(NPCVisitor& visitor) override;
    std::string getName() const override;
    std::string getType() const override;
    double getX() const override;
    double getY() const override;
    bool isAlive() const override;
    void die() override;
    void setPosition(double x, double y) override;
    void move() override;
    void moveTowards(double targetX, double targetY) override;

private:
    std::string name;
    double x, y;
    bool alive;
};

#endif // ROBBER_H
