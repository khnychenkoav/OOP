// backend/src/Squirrel.cpp

#include "Squirrel.h"
#include "NPCVisitor.h"
#include <random>
#include <algorithm>

Squirrel::Squirrel(const std::string& name, double x, double y)
    : name(name), x(x), y(y), health(50), damage(15), attackRange(30.0), alive(true) {}

void Squirrel::accept(NPCVisitor& visitor) {
    visitor.visit(*this);
}

std::string Squirrel::getName() const {
    return name;
}

std::string Squirrel::getType() const {
    return "Squirrel";
}

double Squirrel::getX() const {
    return x;
}

double Squirrel::getY() const {
    return y;
}

int Squirrel::getHealth() const {
    return health;
}

void Squirrel::setHealth(int health) {
    this->health = std::max(0, health);
        if (this->health <= 0 && alive) {
            die();
        }
}

int Squirrel::getDamage() const {
    return damage;
}

double Squirrel::getAttackRange() const {
    return attackRange;
}

void Squirrel::setAttackRange(double range) {
    attackRange = range;
}

bool Squirrel::isAlive() const {
    return alive;
}

void Squirrel::die() {
    alive = false;
}

void Squirrel::setPosition(double x, double y) {
    this->x = x;
    this->y = y;
}

void Squirrel::move() {
    static std::default_random_engine eng{std::random_device{}()};
    static std::uniform_real_distribution<double> dist(-20.0, 20.0);
    x = std::clamp(x + dist(eng), 0.0, 500.0);
    y = std::clamp(y + dist(eng), 0.0, 500.0);
}

void Squirrel::moveTowards(double targetX, double targetY) {
    double dx = targetX - x;
    double dy = targetY - y;
    double dist = std::hypot(dx, dy);
    if (dist > 0) {
        double speed = 6.0;
        x = std::clamp(x + dx / dist * speed, 0.0, 500.0);
        y = std::clamp(y + dy / dist * speed, 0.0, 500.0);
    }
}

void Squirrel::moveAwayFrom(double targetX, double targetY) {
    double dx = x - targetX;
    double dy = y - targetY;
    double dist = std::hypot(dx, dy);
    if (dist > 0) {
        double speed = 6.0;
        x = std::clamp(x + dx / dist * speed, 0.0, 500.0);
        y = std::clamp(y + dy / dist * speed, 0.0, 500.0);
    }
}
