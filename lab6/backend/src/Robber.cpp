#include "Robber.h"
#include "NPCVisitor.h"
#include <random>
#include <algorithm>

Robber::Robber(const std::string& name, double x, double y)
    : name(name), x(x), y(y), health(80), damage(25), attackRange(40.0), alive(true) {}

void Robber::accept(NPCVisitor& visitor) {
    visitor.visit(*this);
}

std::string Robber::getName() const {
    return name;
}

std::string Robber::getType() const {
    return "Robber";
}

double Robber::getX() const {
    return x;
}

double Robber::getY() const {
    return y;
}

int Robber::getHealth() const {
    return health;
}

void Robber::setHealth(int health) {
    this->health = std::max(0, health);
        if (this->health <= 0 && alive) {
            die();
        }
}

int Robber::getDamage() const {
    return damage;
}

double Robber::getAttackRange() const {
    return attackRange;
}

void Robber::setAttackRange(double range) {
    attackRange = range;
}

bool Robber::isAlive() const {
    return alive;
}

void Robber::die() {
    alive = false;
}

void Robber::setPosition(double x, double y) {
    this->x = x;
    this->y = y;
}

void Robber::move() {
    static std::default_random_engine eng{std::random_device{}()};
    static std::uniform_real_distribution<double> dist(-15.0, 15.0);
    x = std::clamp(x + dist(eng), 0.0, 500.0);
    y = std::clamp(y + dist(eng), 0.0, 500.0);
}

void Robber::moveTowards(double targetX, double targetY) {
    double dx = targetX - x;
    double dy = targetY - y;
    double dist = std::hypot(dx, dy);
    if (dist > 0) {
        double speed = 7.0;
        x = std::clamp(x + dx / dist * speed, 0.0, 500.0);
        y = std::clamp(y + dy / dist * speed, 0.0, 500.0);
    }
}

void Robber::moveAwayFrom(double targetX, double targetY) {
    double dx = x - targetX;
    double dy = y - targetY;
    double dist = std::hypot(dx, dy);
    if (dist > 0) {
        double speed = 7.0;
        x = std::clamp(x + dx / dist * speed, 0.0, 500.0);
        y = std::clamp(y + dy / dist * speed, 0.0, 500.0);
    }
}
