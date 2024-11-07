#ifndef STRUCT_HPP
#define STRUCT_HPP

#include <string>

struct Struct {
    int id;
    std::string name;
    double value;

    Struct(int i, const std::string& n, double v)
        : id(i), name(n), value(v) {}
};

#endif
