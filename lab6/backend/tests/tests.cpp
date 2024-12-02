// tests/tests.cpp

#include <gtest/gtest.h>

// Включаем необходимые заголовочные файлы
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

// Тесты для Squirrel
TEST(SquirrelTest, ConstructorInitializesFields)
{
    // Arrange
    Squirrel squirrel("TestSquirrel", 10.0, 20.0);

    // Act
    std::string name = squirrel.getName();
    std::string type = squirrel.getType();
    double x = squirrel.getX();
    double y = squirrel.getY();
    int health = squirrel.getHealth();
    int damage = squirrel.getDamage();
    double range = squirrel.getAttackRange();
    bool alive = squirrel.isAlive();

    // Assert
    EXPECT_EQ(name, "TestSquirrel");
    EXPECT_EQ(type, "Squirrel");
    EXPECT_EQ(x, 10.0);
    EXPECT_EQ(y, 20.0);
    EXPECT_EQ(health, 50);
    EXPECT_EQ(damage, 15); // Предположим, что у Squirrel damage = 10
    EXPECT_EQ(range, 30); // Предположим, что у Squirrel attackRange = 5.0
    EXPECT_TRUE(alive);
}

TEST(SquirrelTest, SetAndGetHealth)
{
    // Arrange
    Squirrel squirrel("TestSquirrel", 0.0, 0.0);

    // Act
    squirrel.setHealth(80);
    int health = squirrel.getHealth();

    // Assert
    EXPECT_EQ(health, 80);
}

TEST(SquirrelTest, SetAndGetPosition)
{
    // Arrange
    Squirrel squirrel("TestSquirrel", 0.0, 0.0);

    // Act
    squirrel.setPosition(15.0, 25.0);
    double x = squirrel.getX();
    double y = squirrel.getY();

    // Assert
    EXPECT_EQ(x, 15.0);
    EXPECT_EQ(y, 25.0);
}

TEST(SquirrelTest, DieSetsAliveToFalse)
{
    // Arrange
    Squirrel squirrel("TestSquirrel", 0.0, 0.0);

    // Act
    squirrel.die();
    bool alive = squirrel.isAlive();

    // Assert
    EXPECT_FALSE(alive);
}

TEST(SquirrelTest, AcceptVisitorCallsVisitSquirrel)
{
    // Arrange
    Squirrel squirrel("TestSquirrel", 0.0, 0.0);
    class MockVisitor : public NPCVisitor {
    public:
        bool visited = false;
        void visit(Squirrel& s) override { visited = true; }
        void visit(Elf&) override {}
        void visit(Robber&) override {}
    } visitor;

    // Act
    squirrel.accept(visitor);

    // Assert
    EXPECT_TRUE(visitor.visited);
}

TEST(SquirrelTest, MoveTowardsChangesPosition)
{
    // Arrange
    Squirrel squirrel("TestSquirrel", 0.0, 0.0);

    // Act
    squirrel.moveTowards(10.0, 10.0);
    double x = squirrel.getX();
    double y = squirrel.getY();

    // Assert
    EXPECT_NE(x, 0.0);
    EXPECT_NE(y, 0.0);
}

TEST(SquirrelTest, MoveAwayFromChangesPosition)
{
    // Arrange
    Squirrel squirrel("TestSquirrel", 10.0, 10.0);

    // Act
    squirrel.moveAwayFrom(0.0, 0.0);
    double x = squirrel.getX();
    double y = squirrel.getY();

    // Assert
    EXPECT_NE(x, 10.0);
    EXPECT_NE(y, 10.0);
}

TEST(SquirrelTest, SetAndGetAttackRange)
{
    // Arrange
    Squirrel squirrel("TestSquirrel", 0.0, 0.0);

    // Act
    squirrel.setAttackRange(7.5);
    double range = squirrel.getAttackRange();

    // Assert
    EXPECT_EQ(range, 7.5);
}

// Тесты для Elf
TEST(ElfTest, ConstructorInitializesFields)
{
    // Arrange
    Elf elf("TestElf", 5.0, 5.0);

    // Act
    std::string name = elf.getName();
    std::string type = elf.getType();
    double x = elf.getX();
    double y = elf.getY();
    int health = elf.getHealth();
    int damage = elf.getDamage();
    double range = elf.getAttackRange();
    bool alive = elf.isAlive();

    // Assert
    EXPECT_EQ(name, "TestElf");
    EXPECT_EQ(type, "Elf");
    EXPECT_EQ(x, 5.0);
    EXPECT_EQ(y, 5.0);
    EXPECT_EQ(health, 100);
    EXPECT_EQ(damage, 20); // Предположим, что у Elf damage = 15
    EXPECT_EQ(range, 50); // Предположим, что у Elf attackRange = 10.0
    EXPECT_TRUE(alive);
}

TEST(ElfTest, SetAndGetHealth)
{
    // Arrange
    Elf elf("TestElf", 0.0, 0.0);

    // Act
    elf.setHealth(100);
    int health = elf.getHealth();

    // Assert
    EXPECT_EQ(health, 100);
}

TEST(ElfTest, DieSetsAliveToFalse)
{
    // Arrange
    Elf elf("TestElf", 0.0, 0.0);

    // Act
    elf.die();
    bool alive = elf.isAlive();

    // Assert
    EXPECT_FALSE(alive);
}

TEST(ElfTest, AcceptVisitorCallsVisitElf)
{
    // Arrange
    Elf elf("TestElf", 0.0, 0.0);
    class MockVisitor : public NPCVisitor {
    public:
        bool visited = false;
        void visit(Elf& e) override { visited = true; }
        void visit(Squirrel&) override {}
        void visit(Robber&) override {}
    } visitor;

    // Act
    elf.accept(visitor);

    // Assert
    EXPECT_TRUE(visitor.visited);
}

TEST(ElfTest, MoveTowardsChangesPosition)
{
    // Arrange
    Elf elf("TestElf", 0.0, 0.0);

    // Act
    elf.moveTowards(10.0, 10.0);
    double x = elf.getX();
    double y = elf.getY();

    // Assert
    EXPECT_NE(x, 0.0);
    EXPECT_NE(y, 0.0);
}

TEST(ElfTest, MoveAwayFromChangesPosition)
{
    // Arrange
    Elf elf("TestElf", 10.0, 10.0);

    // Act
    elf.moveAwayFrom(0.0, 0.0);
    double x = elf.getX();
    double y = elf.getY();

    // Assert
    EXPECT_NE(x, 10.0);
    EXPECT_NE(y, 10.0);
}

TEST(ElfTest, SetAndGetAttackRange)
{
    // Arrange
    Elf elf("TestElf", 0.0, 0.0);

    // Act
    elf.setAttackRange(12.0);
    double range = elf.getAttackRange();

    // Assert
    EXPECT_EQ(range, 12.0);
}

// Тесты для Robber
TEST(RobberTest, ConstructorInitializesFields)
{
    // Arrange
    Robber robber("TestRobber", -5.0, -5.0);

    // Act
    std::string name = robber.getName();
    std::string type = robber.getType();
    double x = robber.getX();
    double y = robber.getY();
    int health = robber.getHealth();
    int damage = robber.getDamage();
    double range = robber.getAttackRange();
    bool alive = robber.isAlive();

    // Assert
    EXPECT_EQ(name, "TestRobber");
    EXPECT_EQ(type, "Robber");
    EXPECT_EQ(x, -5.0);
    EXPECT_EQ(y, -5.0);
    EXPECT_EQ(health, 80);
    EXPECT_EQ(damage, 25); // Предположим, что у Robber damage = 20
    EXPECT_EQ(range, 40); // Предположим, что у Robber attackRange = 8.0
    EXPECT_TRUE(alive);
}

TEST(RobberTest, SetAndGetHealth)
{
    // Arrange
    Robber robber("TestRobber", 0.0, 0.0);

    // Act
    robber.setHealth(70);
    int health = robber.getHealth();

    // Assert
    EXPECT_EQ(health, 70);
}

TEST(RobberTest, DieSetsAliveToFalse)
{
    // Arrange
    Robber robber("TestRobber", 0.0, 0.0);

    // Act
    robber.die();
    bool alive = robber.isAlive();

    // Assert
    EXPECT_FALSE(alive);
}

TEST(RobberTest, AcceptVisitorCallsVisitRobber)
{
    // Arrange
    Robber robber("TestRobber", 0.0, 0.0);
    class MockVisitor : public NPCVisitor {
    public:
        bool visited = false;
        void visit(Robber& r) override { visited = true; }
        void visit(Squirrel&) override {}
        void visit(Elf&) override {}
    } visitor;

    // Act
    robber.accept(visitor);

    // Assert
    EXPECT_TRUE(visitor.visited);
}

TEST(RobberTest, MoveTowardsChangesPosition)
{
    // Arrange
    Robber robber("TestRobber", 0.0, 0.0);

    // Act
    robber.moveTowards(10.0, 10.0);
    double x = robber.getX();
    double y = robber.getY();

    // Assert
    EXPECT_NE(x, 0.0);
    EXPECT_NE(y, 0.0);
}

TEST(RobberTest, MoveAwayFromChangesPosition)
{
    // Arrange
    Robber robber("TestRobber", 10.0, 10.0);

    // Act
    robber.moveAwayFrom(0.0, 0.0);
    double x = robber.getX();
    double y = robber.getY();

    // Assert
    EXPECT_NE(x, 10.0);
    EXPECT_NE(y, 10.0);
}

TEST(RobberTest, SetAndGetAttackRange)
{
    // Arrange
    Robber robber("TestRobber", 0.0, 0.0);

    // Act
    robber.setAttackRange(9.0);
    double range = robber.getAttackRange();

    // Assert
    EXPECT_EQ(range, 9.0);
}

// Тесты для ConcreteNPCFactory
TEST(ConcreteNPCFactoryTest, CreateSquirrelReturnsSquirrel)
{
    // Arrange
    ConcreteNPCFactory factory;

    // Act
    auto npc = factory.createNPC("Squirrel", "TestSquirrel", 0.0, 0.0);

    // Assert
    EXPECT_NE(npc, nullptr);
    EXPECT_EQ(npc->getType(), "Squirrel");
}

TEST(ConcreteNPCFactoryTest, CreateElfReturnsElf)
{
    // Arrange
    ConcreteNPCFactory factory;

    // Act
    auto npc = factory.createNPC("Elf", "TestElf", 0.0, 0.0);

    // Assert
    EXPECT_NE(npc, nullptr);
    EXPECT_EQ(npc->getType(), "Elf");
}

TEST(ConcreteNPCFactoryTest, CreateRobberReturnsRobber)
{
    // Arrange
    ConcreteNPCFactory factory;

    // Act
    auto npc = factory.createNPC("Robber", "TestRobber", 0.0, 0.0);

    // Assert
    EXPECT_NE(npc, nullptr);
    EXPECT_EQ(npc->getType(), "Robber");
}

TEST(ConcreteNPCFactoryTest, CreateUnknownTypeReturnsNullptr)
{
    // Arrange
    ConcreteNPCFactory factory;

    // Act
    auto npc = factory.createNPC("Unknown", "TestUnknown", 0.0, 0.0);

    // Assert
    EXPECT_EQ(npc, nullptr);
}

// Тесты для FightVisitor
TEST(FightVisitorTest, VisitSquirrelProcessesFight)
{
    // Arrange
    NPCManager manager;
    FightVisitor visitor(manager);
    Squirrel squirrel("Attacker", 0.0, 0.0);
    Elf elf("Defender", 1.0, 1.0);

    manager.addNPC(std::make_shared<Squirrel>(squirrel));
    manager.addNPC(std::make_shared<Elf>(elf));

    // Act
    visitor.visit(squirrel);
    auto targets = visitor.getTargets();

    // Assert
    EXPECT_EQ(targets.size(), 1);
    EXPECT_EQ(targets.begin()->first->getName(), "Attacker");
    EXPECT_EQ(targets.begin()->second->getName(), "Defender");
}

TEST(FightVisitorTest, VisitElfProcessesFight)
{
    // Arrange
    NPCManager manager;
    FightVisitor visitor(manager);
    Elf elf("Attacker", 0.0, 0.0);
    Robber robber("Defender", 1.0, 1.0);

    manager.addNPC(std::make_shared<Elf>(elf));
    manager.addNPC(std::make_shared<Robber>(robber));

    // Act
    visitor.visit(elf);
    auto targets = visitor.getTargets();

    // Assert
    EXPECT_EQ(targets.size(), 1);
    EXPECT_EQ(targets.begin()->first->getName(), "Attacker");
    EXPECT_EQ(targets.begin()->second->getName(), "Defender");
}

TEST(FightVisitorTest, VisitRobberProcessesFight)
{
    // Arrange
    NPCManager manager;
    FightVisitor visitor(manager);
    Robber robber("Attacker", 0.0, 0.0);
    Squirrel squirrel("Defender", 1.0, 1.0);

    manager.addNPC(std::make_shared<Robber>(robber));
    manager.addNPC(std::make_shared<Squirrel>(squirrel));

    // Act
    visitor.visit(robber);
    auto targets = visitor.getTargets();

    // Assert
    EXPECT_EQ(targets.size(), 1);
    EXPECT_EQ(targets.begin()->first->getName(), "Attacker");
    EXPECT_EQ(targets.begin()->second->getName(), "Defender");
}

// Тесты для NPCManager
TEST(NPCManagerTest, AddNPCIncreasesCount)
{
    // Arrange
    NPCManager manager;
    auto npc = std::make_shared<Squirrel>("TestSquirrel", 0.0, 0.0);

    // Act
    manager.addNPC(npc);
    auto count = manager.getNPCs().size();

    // Assert
    EXPECT_EQ(count, 1);
}

TEST(NPCManagerTest, RemoveDeadNPCsRemovesDeadNPCs)
{
    // Arrange
    NPCManager manager;
    auto npc1 = std::make_shared<Squirrel>("AliveSquirrel", 0.0, 0.0);
    auto npc2 = std::make_shared<Squirrel>("DeadSquirrel", 0.0, 0.0);
    npc2->die();
    manager.addNPC(npc1);
    manager.addNPC(npc2);

    // Act
    manager.removeDeadNPCs();
    auto count = manager.getNPCs().size();

    // Assert
    EXPECT_EQ(count, 1);
    EXPECT_EQ(manager.getNPCs()[0]->getName(), "AliveSquirrel");
}

TEST(NPCManagerTest, LoadNPCsFromFileLoadsCorrectly)
{
    // Arrange
    NPCManager manager;
    std::string filename = "test_npcs.txt";

    // Создаем тестовый файл
    std::ofstream file(filename);
    file << "Squirrel Squirrel1 100 100 50\n";
    file << "Elf Elf1 200 200 100\n";
    file << "Robber Robber1 300 300 80\n";
    file.close();

    // Act
    manager.loadNPCsFromFile(filename);
    auto npcs = manager.getNPCs();

    // Assert
    EXPECT_EQ(npcs.size(), 3);
    EXPECT_EQ(npcs[0]->getType(), "Squirrel");
    EXPECT_EQ(npcs[1]->getType(), "Elf");
    EXPECT_EQ(npcs[2]->getType(), "Robber");

    // Удаляем тестовый файл
    std::remove(filename.c_str());
}

// Тесты для Observer
TEST(ObserverTest, ConsoleObserverReceivesUpdate)
{
    // Arrange
    class TestConsoleObserver : public ConsoleObserver {
    public:
        std::string lastMessage;
        void update(const std::string& message) override {
            lastMessage = message;
        }
    };

    auto observer = std::make_shared<TestConsoleObserver>();
    observer->update("Test message");

    // Assert
    EXPECT_EQ(observer->lastMessage, "Test message");
}

TEST(ObserverTest, FileObserverWritesToFile)
{
    // Arrange
    std::string filename = "test_log.txt";
    auto observer = std::make_shared<FileObserver>(filename);

    // Act
    observer->update("Test message");

    // Assert
    std::ifstream file(filename);
    std::string content;
    std::getline(file, content);
    EXPECT_EQ(content, "Test message");

    // Удаляем тестовый файл
    std::remove(filename.c_str());
}

// Функция main для запуска тестов
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
