#include <gtest/gtest.h>

#include "Squirrel.h"
#include "Elf.h"
#include "Robber.h"
#include "ConcreteNPCFactory.h"
#include "FightVisitor.h"
#include "NPCManager.h"
#include "ConsoleObserver.h"
#include "FileObserver.h"
#include "NPC.h"
#include "Observer.h"
#include "NPCVisitor.h"

TEST(SquirrelTest, ConstructorSetsName)
{
    Squirrel squirrel("TestSquirrel", 10.0, 20.0);
    std::string name = squirrel.getName();
    EXPECT_EQ(name, "TestSquirrel");
}

TEST(SquirrelTest, ConstructorSetsType)
{
    Squirrel squirrel("TestSquirrel", 10.0, 20.0);
    std::string type = squirrel.getType();
    EXPECT_EQ(type, "Squirrel");
}

TEST(SquirrelTest, ConstructorSetsX)
{
    Squirrel squirrel("TestSquirrel", 10.0, 20.0);
    double x = squirrel.getX();
    EXPECT_EQ(x, 10.0);
}

TEST(SquirrelTest, ConstructorSetsY)
{
    Squirrel squirrel("TestSquirrel", 10.0, 20.0);
    double y = squirrel.getY();
    EXPECT_EQ(y, 20.0);
}

TEST(SquirrelTest, ConstructorSetsHealth)
{
    Squirrel squirrel("TestSquirrel", 10.0, 20.0);
    int health = squirrel.getHealth();
    EXPECT_EQ(health, 50);
}

TEST(SquirrelTest, ConstructorSetsDamage)
{
    Squirrel squirrel("TestSquirrel", 10.0, 20.0);
    int damage = squirrel.getDamage();
    EXPECT_EQ(damage, 15);
}

TEST(SquirrelTest, ConstructorSetsAttackRange)
{
    Squirrel squirrel("TestSquirrel", 10.0, 20.0);
    double range = squirrel.getAttackRange();
    EXPECT_EQ(range, 30);
}

TEST(SquirrelTest, ConstructorSetsAlive)
{
    Squirrel squirrel("TestSquirrel", 10.0, 20.0);
    bool alive = squirrel.isAlive();
    EXPECT_TRUE(alive);
}

TEST(SquirrelTest, SetAndGetHealth)
{
    Squirrel squirrel("TestSquirrel", 0.0, 0.0);
    squirrel.setHealth(80);
    int health = squirrel.getHealth();
    EXPECT_EQ(health, 80);
}

TEST(SquirrelTest, SetPositionUpdatesX)
{
    Squirrel squirrel("TestSquirrel", 0.0, 0.0);
    squirrel.setPosition(15.0, 25.0);
    double x = squirrel.getX();
    EXPECT_EQ(x, 15.0);
}

TEST(SquirrelTest, SetPositionUpdatesY)
{
    Squirrel squirrel("TestSquirrel", 0.0, 0.0);
    squirrel.setPosition(15.0, 25.0);
    double y = squirrel.getY();
    EXPECT_EQ(y, 25.0);
}

TEST(SquirrelTest, DieSetsAliveToFalse)
{
    Squirrel squirrel("TestSquirrel", 0.0, 0.0);
    squirrel.die();
    bool alive = squirrel.isAlive();
    EXPECT_FALSE(alive);
}

TEST(SquirrelTest, AcceptVisitorCallsVisitSquirrel)
{
    Squirrel squirrel("TestSquirrel", 0.0, 0.0);
    class MockVisitor : public NPCVisitor {
    public:
        bool visited = false;
        void visit(Squirrel& s) override { visited = true; }
        void visit(Elf&) override {}
        void visit(Robber&) override {}
    } visitor;
    squirrel.accept(visitor);
    EXPECT_TRUE(visitor.visited);
}

TEST(SquirrelTest, MoveTowardsChangesX)
{
    Squirrel squirrel("TestSquirrel", 0.0, 0.0);
    squirrel.moveTowards(10.0, 10.0);
    double x = squirrel.getX();
    EXPECT_NE(x, 0.0);
}

TEST(SquirrelTest, MoveTowardsChangesY)
{
    Squirrel squirrel("TestSquirrel", 0.0, 0.0);
    squirrel.moveTowards(10.0, 10.0);
    double y = squirrel.getY();
    EXPECT_NE(y, 0.0);
}

TEST(SquirrelTest, MoveAwayFromChangesX)
{
    Squirrel squirrel("TestSquirrel", 10.0, 10.0);
    squirrel.moveAwayFrom(0.0, 0.0);
    double x = squirrel.getX();
    EXPECT_NE(x, 10.0);
}

TEST(SquirrelTest, MoveAwayFromChangesY)
{
    Squirrel squirrel("TestSquirrel", 10.0, 10.0);
    squirrel.moveAwayFrom(0.0, 0.0);
    double y = squirrel.getY();
    EXPECT_NE(y, 10.0);
}

TEST(SquirrelTest, SetAndGetAttackRange)
{
    Squirrel squirrel("TestSquirrel", 0.0, 0.0);
    squirrel.setAttackRange(7.5);
    double range = squirrel.getAttackRange();
    EXPECT_EQ(range, 7.5);
}

TEST(ElfTest, ConstructorSetsName)
{
    Elf elf("TestElf", 5.0, 5.0);
    std::string name = elf.getName();
    EXPECT_EQ(name, "TestElf");
}

TEST(ElfTest, ConstructorSetsType)
{
    Elf elf("TestElf", 5.0, 5.0);
    std::string type = elf.getType();
    EXPECT_EQ(type, "Elf");
}

TEST(ElfTest, ConstructorSetsX)
{
    Elf elf("TestElf", 5.0, 5.0);
    double x = elf.getX();
    EXPECT_EQ(x, 5.0);
}

TEST(ElfTest, ConstructorSetsY)
{
    Elf elf("TestElf", 5.0, 5.0);
    double y = elf.getY();
    EXPECT_EQ(y, 5.0);
}

TEST(ElfTest, ConstructorSetsHealth)
{
    Elf elf("TestElf", 5.0, 5.0);
    int health = elf.getHealth();
    EXPECT_EQ(health, 100);
}

TEST(ElfTest, ConstructorSetsDamage)
{
    Elf elf("TestElf", 5.0, 5.0);
    int damage = elf.getDamage();
    EXPECT_EQ(damage, 20);
}

TEST(ElfTest, ConstructorSetsAttackRange)
{
    Elf elf("TestElf", 5.0, 5.0);
    double range = elf.getAttackRange();
    EXPECT_EQ(range, 50);
}

TEST(ElfTest, ConstructorSetsAlive)
{
    Elf elf("TestElf", 5.0, 5.0);
    bool alive = elf.isAlive();
    EXPECT_TRUE(alive);
}

TEST(ElfTest, SetAndGetHealth)
{
    Elf elf("TestElf", 0.0, 0.0);
    elf.setHealth(100);
    int health = elf.getHealth();
    EXPECT_EQ(health, 100);
}

TEST(ElfTest, DieSetsAliveToFalse)
{
    Elf elf("TestElf", 0.0, 0.0);
    elf.die();
    bool alive = elf.isAlive();
    EXPECT_FALSE(alive);
}

TEST(ElfTest, AcceptVisitorCallsVisitElf)
{
    Elf elf("TestElf", 0.0, 0.0);
    class MockVisitor : public NPCVisitor {
    public:
        bool visited = false;
        void visit(Elf& e) override { visited = true; }
        void visit(Squirrel&) override {}
        void visit(Robber&) override {}
    } visitor;
    elf.accept(visitor);
    EXPECT_TRUE(visitor.visited);
}

TEST(ElfTest, MoveTowardsChangesX)
{
    Elf elf("TestElf", 0.0, 0.0);
    elf.moveTowards(10.0, 10.0);
    double x = elf.getX();
    EXPECT_NE(x, 0.0);
}

TEST(ElfTest, MoveTowardsChangesY)
{
    Elf elf("TestElf", 0.0, 0.0);
    elf.moveTowards(10.0, 10.0);
    double y = elf.getY();
    EXPECT_NE(y, 0.0);
}

TEST(ElfTest, MoveAwayFromChangesX)
{
    Elf elf("TestElf", 10.0, 10.0);
    elf.moveAwayFrom(0.0, 0.0);
    double x = elf.getX();
    EXPECT_NE(x, 10.0);
}

TEST(ElfTest, MoveAwayFromChangesY)
{
    Elf elf("TestElf", 10.0, 10.0);
    elf.moveAwayFrom(0.0, 0.0);
    double y = elf.getY();
    EXPECT_NE(y, 10.0);
}

TEST(ElfTest, SetAndGetAttackRange)
{
    Elf elf("TestElf", 0.0, 0.0);
    elf.setAttackRange(12.0);
    double range = elf.getAttackRange();
    EXPECT_EQ(range, 12.0);
}

TEST(RobberTest, ConstructorSetsName)
{
    Robber robber("TestRobber", -5.0, -5.0);
    std::string name = robber.getName();
    EXPECT_EQ(name, "TestRobber");
}

TEST(RobberTest, ConstructorSetsType)
{
    Robber robber("TestRobber", -5.0, -5.0);
    std::string type = robber.getType();
    EXPECT_EQ(type, "Robber");
}

TEST(RobberTest, ConstructorSetsX)
{
    Robber robber("TestRobber", -5.0, -5.0);
    double x = robber.getX();
    EXPECT_EQ(x, -5.0);
}

TEST(RobberTest, ConstructorSetsY)
{
    Robber robber("TestRobber", -5.0, -5.0);
    double y = robber.getY();
    EXPECT_EQ(y, -5.0);
}

TEST(RobberTest, ConstructorSetsHealth)
{
    Robber robber("TestRobber", -5.0, -5.0);
    int health = robber.getHealth();
    EXPECT_EQ(health, 80);
}

TEST(RobberTest, ConstructorSetsDamage)
{
    Robber robber("TestRobber", -5.0, -5.0);
    int damage = robber.getDamage();
    EXPECT_EQ(damage, 25);
}

TEST(RobberTest, ConstructorSetsAttackRange)
{
    Robber robber("TestRobber", -5.0, -5.0);
    double range = robber.getAttackRange();
    EXPECT_EQ(range, 40);
}

TEST(RobberTest, ConstructorSetsAlive)
{
    Robber robber("TestRobber", -5.0, -5.0);
    bool alive = robber.isAlive();
    EXPECT_TRUE(alive);
}

TEST(RobberTest, SetAndGetHealth)
{
    Robber robber("TestRobber", 0.0, 0.0);
    robber.setHealth(70);
    int health = robber.getHealth();
    EXPECT_EQ(health, 70);
}

TEST(RobberTest, DieSetsAliveToFalse)
{
    Robber robber("TestRobber", 0.0, 0.0);
    robber.die();
    bool alive = robber.isAlive();
    EXPECT_FALSE(alive);
}

TEST(RobberTest, AcceptVisitorCallsVisitRobber)
{
    Robber robber("TestRobber", 0.0, 0.0);
    class MockVisitor : public NPCVisitor {
    public:
        bool visited = false;
        void visit(Robber& r) override { visited = true; }
        void visit(Squirrel&) override {}
        void visit(Elf&) override {}
    } visitor;
    robber.accept(visitor);
    EXPECT_TRUE(visitor.visited);
}

TEST(RobberTest, MoveTowardsChangesX)
{
    Robber robber("TestRobber", 0.0, 0.0);
    robber.moveTowards(10.0, 10.0);
    double x = robber.getX();
    EXPECT_NE(x, 0.0);
}

TEST(RobberTest, MoveTowardsChangesY)
{
    Robber robber("TestRobber", 0.0, 0.0);
    robber.moveTowards(10.0, 10.0);
    double y = robber.getY();
    EXPECT_NE(y, 0.0);
}

TEST(RobberTest, MoveAwayFromChangesX)
{
    Robber robber("TestRobber", 10.0, 10.0);
    robber.moveAwayFrom(0.0, 0.0);
    double x = robber.getX();
    EXPECT_NE(x, 10.0);
}

TEST(RobberTest, MoveAwayFromChangesY)
{
    Robber robber("TestRobber", 10.0, 10.0);
    robber.moveAwayFrom(0.0, 0.0);
    double y = robber.getY();
    EXPECT_NE(y, 10.0);
}

TEST(RobberTest, SetAndGetAttackRange)
{
    Robber robber("TestRobber", 0.0, 0.0);
    robber.setAttackRange(9.0);
    double range = robber.getAttackRange();
    EXPECT_EQ(range, 9.0);
}

TEST(ConcreteNPCFactoryTest, CreateSquirrelReturnsNonNullptr)
{
    ConcreteNPCFactory factory;
    auto npc = factory.createNPC("Squirrel", "TestSquirrel", 0.0, 0.0);
    EXPECT_NE(npc, nullptr);
}

TEST(ConcreteNPCFactoryTest, CreateSquirrelSetsType)
{
    ConcreteNPCFactory factory;
    auto npc = factory.createNPC("Squirrel", "TestSquirrel", 0.0, 0.0);
    EXPECT_EQ(npc->getType(), "Squirrel");
}

TEST(ConcreteNPCFactoryTest, CreateElfReturnsNonNullptr)
{
    ConcreteNPCFactory factory;
    auto npc = factory.createNPC("Elf", "TestElf", 0.0, 0.0);
    EXPECT_NE(npc, nullptr);
}

TEST(ConcreteNPCFactoryTest, CreateElfSetsType)
{
    ConcreteNPCFactory factory;
    auto npc = factory.createNPC("Elf", "TestElf", 0.0, 0.0);
    EXPECT_EQ(npc->getType(), "Elf");
}

TEST(ConcreteNPCFactoryTest, CreateRobberReturnsNonNullptr)
{
    ConcreteNPCFactory factory;
    auto npc = factory.createNPC("Robber", "TestRobber", 0.0, 0.0);
    EXPECT_NE(npc, nullptr);
}

TEST(ConcreteNPCFactoryTest, CreateRobberSetsType)
{
    ConcreteNPCFactory factory;
    auto npc = factory.createNPC("Robber", "TestRobber", 0.0, 0.0);
    EXPECT_EQ(npc->getType(), "Robber");
}

TEST(ConcreteNPCFactoryTest, CreateUnknownTypeReturnsNullptr)
{
    ConcreteNPCFactory factory;
    auto npc = factory.createNPC("Unknown", "TestUnknown", 0.0, 0.0);
    EXPECT_EQ(npc, nullptr);
}

TEST(FightVisitorTest, VisitSquirrelAddsOneTarget)
{
    NPCManager manager;
    FightVisitor visitor(manager);
    Squirrel squirrel("Attacker", 0.0, 0.0);
    Elf elf("Defender", 1.0, 1.0);
    manager.addNPC(std::make_shared<Squirrel>(squirrel));
    manager.addNPC(std::make_shared<Elf>(elf));
    visitor.visit(squirrel);
    auto targets = visitor.getTargets();
    EXPECT_EQ(targets.size(), 1);
}

TEST(FightVisitorTest, VisitSquirrelAttackerIsCorrect)
{
    NPCManager manager;
    FightVisitor visitor(manager);
    Squirrel squirrel("Attacker", 0.0, 0.0);
    Elf elf("Defender", 1.0, 1.0);
    manager.addNPC(std::make_shared<Squirrel>(squirrel));
    manager.addNPC(std::make_shared<Elf>(elf));
    visitor.visit(squirrel);
    auto targets = visitor.getTargets();
    EXPECT_EQ(targets.begin()->first->getName(), "Attacker");
}

TEST(FightVisitorTest, VisitSquirrelDefenderIsCorrect)
{
    NPCManager manager;
    FightVisitor visitor(manager);
    Squirrel squirrel("Attacker", 0.0, 0.0);
    Elf elf("Defender", 1.0, 1.0);
    manager.addNPC(std::make_shared<Squirrel>(squirrel));
    manager.addNPC(std::make_shared<Elf>(elf));
    visitor.visit(squirrel);
    auto targets = visitor.getTargets();
    EXPECT_EQ(targets.begin()->second->getName(), "Defender");
}

TEST(NPCManagerTest, AddNPCIncreasesCount)
{
    NPCManager manager;
    auto npc = std::make_shared<Squirrel>("TestSquirrel", 0.0, 0.0);
    manager.addNPC(npc);
    auto count = manager.getNPCs().size();
    EXPECT_EQ(count, 1);
}

TEST(NPCManagerTest, RemoveDeadNPCsReducesCount)
{
    NPCManager manager;
    auto npc1 = std::make_shared<Squirrel>("AliveSquirrel", 0.0, 0.0);
    auto npc2 = std::make_shared<Squirrel>("DeadSquirrel", 0.0, 0.0);
    npc2->die();
    manager.addNPC(npc1);
    manager.addNPC(npc2);
    manager.removeDeadNPCs();
    auto count = manager.getNPCs().size();
    EXPECT_EQ(count, 1);
}

TEST(NPCManagerTest, RemoveDeadNPCsLeavesAliveNPC)
{
    NPCManager manager;
    auto npc1 = std::make_shared<Squirrel>("AliveSquirrel", 0.0, 0.0);
    auto npc2 = std::make_shared<Squirrel>("DeadSquirrel", 0.0, 0.0);
    npc2->die();
    manager.addNPC(npc1);
    manager.addNPC(npc2);
    manager.removeDeadNPCs();
    EXPECT_EQ(manager.getNPCs()[0]->getName(), "AliveSquirrel");
}

TEST(ObserverTest, ConsoleObserverReceivesUpdate)
{
    class TestConsoleObserver : public ConsoleObserver {
    public:
        std::string lastMessage;
        void update(const std::string& message) override {
            lastMessage = message;
        }
    };
    auto observer = std::make_shared<TestConsoleObserver>();
    observer->update("Test message");
    EXPECT_EQ(observer->lastMessage, "Test message");
}

TEST(ObserverTest, FileObserverWritesToFile)
{
    std::string filename = "test_log.txt";
    auto observer = std::make_shared<FileObserver>(filename);
    observer->update("Test message");
    std::ifstream file(filename);
    std::string content;
    std::getline(file, content);
    EXPECT_EQ(content, "Test message");
    std::remove(filename.c_str());
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
