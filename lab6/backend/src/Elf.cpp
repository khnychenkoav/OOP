#include "Elf.h"
#include "NPCVisitor.h"
#include <random>
#include <algorithm>

Elf::Elf(const std::string& name, double x, double y)
    : name(name), x(x), y(y), health(100), damage(20), attackRange(50.0), alive(true) {}

void Elf::accept(NPCVisitor& visitor) {
    visitor.visit(*this);
}

std::string Elf::getName() const {
    return name;
}

std::string Elf::getType() const {
    return "Elf";
}

double Elf::getX() const {
    return x;
}

double Elf::getY() const {
    return y;
}

int Elf::getHealth() const {
    return health;
}

void Elf::setHealth(int health) {
    this->health = std::max(0, health);
        if (this->health <= 0 && alive) {
            die();
        }
}

int Elf::getDamage() const {
    return damage;
}

double Elf::getAttackRange() const {
    return attackRange;
}

void Elf::setAttackRange(double range) {
    attackRange = range;
}

bool Elf::isAlive() const {
    return alive;
}

void Elf::die() {
    alive = false;
}

void Elf::setPosition(double x, double y) {
    this->x = std::clamp(x, 0.0, 500.0);
    this->y = std::clamp(y, 0.0, 500.0);
}

void Elf::move() {
    static std::default_random_engine eng{std::random_device{}()};
    static std::uniform_real_distribution<double> dist(-10.0, 10.0);
    x = std::clamp(x + dist(eng), 0.0, 500.0);
    y = std::clamp(y + dist(eng), 0.0, 500.0);
}

void Elf::moveTowards(double targetX, double targetY) {
    double dx = targetX - x;
    double dy = targetY - y;
    double dist = std::hypot(dx, dy);
    if (dist > 0) {
        double speed = 5.0;
        x = std::clamp(x + dx / dist * speed, 0.0, 500.0);
        y = std::clamp(y + dy / dist * speed, 0.0, 500.0);
    }
}

void Elf::moveAwayFrom(double targetX, double targetY) {
    double dx = x - targetX;
    double dy = y - targetY;
    double dist = std::hypot(dx, dy);
    if (dist > 0) {
        double speed = 5.0;
        x = std::clamp(x + dx / dist * speed, 0.0, 500.0);
        y = std::clamp(y + dy / dist * speed, 0.0, 500.0);
    }
}
