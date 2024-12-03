#ifndef NPCVISITOR_H
#define NPCVISITOR_H

class Squirrel;
class Elf;
class Robber;

class NPCVisitor {
public:
    virtual ~NPCVisitor() = default;
    virtual void visit(Squirrel& squirrel) = 0;
    virtual void visit(Elf& elf) = 0;
    virtual void visit(Robber& robber) = 0;
};

#endif // NPCVISITOR_H
