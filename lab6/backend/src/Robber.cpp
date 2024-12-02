// backend/src/Robber.cpp

#include "Robber.h"
#include "NPCVisitor.h"
#include <random>
#include <algorithm>


Robber::Robber(const std::string& name, double x, double y)
    : name(name), x(x), y(y), alive(true) {}

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
    static std::uniform_real_distribution<double> dist(-25.0, 25.0);
    x = std::clamp(x + dist(eng), 0.0, 500.0);
    y = std::clamp(y + dist(eng), 0.0, 500.0);
}

void Robber::moveTowards(double targetX, double targetY) {
    double dx = targetX - x;
    double dy = targetY - y;
    double dist = std::hypot(dx, dy);
    if (dist > 0) {
        x = std::clamp(x + dx / dist * 5.0, 0.0, 500.0);
        y = std::clamp(y + dy / dist * 5.0, 0.0, 500.0);
    }
}
