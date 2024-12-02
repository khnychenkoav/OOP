// backend/src/Elf.cpp

#include "Elf.h"
#include "NPCVisitor.h"
#include <random>
#include <algorithm>


Elf::Elf(const std::string& name, double x, double y)
    : name(name), x(x), y(y), alive(true) {}

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

bool Elf::isAlive() const {
    return alive;
}

void Elf::die() {
    alive = false;
}

void Elf::setPosition(double x, double y) {
    this->x = x;
    this->y = y;
}

void Elf::move() {
    static std::default_random_engine eng{std::random_device{}()};
    static std::uniform_real_distribution<double> dist(-25.0, 25.0);
    x = std::clamp(x + dist(eng), 0.0, 500.0);
    y = std::clamp(y + dist(eng), 0.0, 500.0);
}

void Elf::moveTowards(double targetX, double targetY) {
    double dx = targetX - x;
    double dy = targetY - y;
    double dist = std::hypot(dx, dy);
    if (dist > 0) {
        x = std::clamp(x + dx / dist * 5.0, 0.0, 500.0);
        y = std::clamp(y + dy / dist * 5.0, 0.0, 500.0);
    }
}

