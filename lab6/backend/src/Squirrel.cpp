// backend/src/Squirrel.cpp

#include "Squirrel.h"
#include "NPCVisitor.h"
#include <random>
#include <algorithm>

Squirrel::Squirrel(const std::string& name, double x, double y)
    : name(name), x(x), y(y), alive(true) {}

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
    static std::uniform_real_distribution<double> dist(-25.0, 25.0);
    x = std::clamp(x + dist(eng), 0.0, 500.0);
    y = std::clamp(y + dist(eng), 0.0, 500.0);
}

void Squirrel::moveTowards(double targetX, double targetY) {
    double dx = targetX - x;
    double dy = targetY - y;
    double dist = std::hypot(dx, dy);
    if (dist > 0) {
        x = std::clamp(x + dx / dist * 5.0, 0.0, 500.0);
        y = std::clamp(y + dy / dist * 5.0, 0.0, 500.0);
    }
}
