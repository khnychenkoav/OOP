#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "NPC.h"
#include "Squirrel.h"
#include "Elf.h"
#include "Robber.h"
#include "ConcreteNPCFactory.h"
#include "FightVisitor.h"
#include "ConsoleObserver.h"
#include "FileObserver.h"
#include "NPCManager.h"

namespace py = pybind11;

PYBIND11_MODULE(game_backend, m) {
    py::class_<NPC, std::shared_ptr<NPC>>(m, "NPC")
        .def("accept", &NPC::accept)
        .def("get_name", &NPC::getName)
        .def("get_type", &NPC::getType)
        .def("get_x", &NPC::getX)
        .def("get_y", &NPC::getY)
        .def("get_health", &NPC::getHealth)
        .def("set_health", &NPC::setHealth)
        .def("get_damage", &NPC::getDamage)
        .def("get_attack_range", &NPC::getAttackRange)
        .def("set_attack_range", &NPC::setAttackRange)
        .def("is_alive", &NPC::isAlive)
        .def("die", &NPC::die)
        .def("set_position", &NPC::setPosition)
        .def("move", &NPC::move)
        .def("move_towards", &NPC::moveTowards)
        .def("move_away_from", &NPC::moveAwayFrom);

    py::class_<Squirrel, NPC, std::shared_ptr<Squirrel>>(m, "Squirrel")
        .def(py::init<const std::string&, double, double>())
        .def(py::pickle(
            [](const Squirrel& npc) {
                return py::make_tuple(npc.getName(), npc.getX(), npc.getY(), npc.getHealth(), npc.isAlive());
            },
            [](py::tuple t) {
                if (t.size() != 5)
                    throw std::runtime_error("Invalid state!");
                auto npc = new Squirrel(t[0].cast<std::string>(), t[1].cast<double>(), t[2].cast<double>());
                if (!t[4].cast<bool>()) {
                    npc->die();
                }
                return npc;
            }
        ));

    py::class_<Elf, NPC, std::shared_ptr<Elf>>(m, "Elf")
        .def(py::init<const std::string&, double, double>())
        .def(py::pickle(
            [](const Elf& npc) {
                return py::make_tuple(npc.getName(), npc.getX(), npc.getY(), npc.getHealth(), npc.isAlive());
            },
            [](py::tuple t) {
                if (t.size() != 5)
                    throw std::runtime_error("Invalid state!");
                auto npc = new Elf(t[0].cast<std::string>(), t[1].cast<double>(), t[2].cast<double>());
                if (!t[4].cast<bool>()) {
                    npc->die();
                }
                return npc;
            }
        ));

    py::class_<Robber, NPC, std::shared_ptr<Robber>>(m, "Robber")
        .def(py::init<const std::string&, double, double>())
        .def(py::pickle(
            [](const Robber& npc) {
                return py::make_tuple(npc.getName(), npc.getX(), npc.getY(), npc.getHealth(), npc.isAlive());
            },
            [](py::tuple t) {
                if (t.size() != 5)
                    throw std::runtime_error("Invalid state!");
                auto npc = new Robber(t[0].cast<std::string>(), t[1].cast<double>(), t[2].cast<double>());
                if (!t[4].cast<bool>()) {
                    npc->die();
                }
                return npc;
            }
        ));

    py::class_<NPCFactory, std::shared_ptr<NPCFactory>>(m, "NPCFactory");

    py::class_<ConcreteNPCFactory, NPCFactory, std::shared_ptr<ConcreteNPCFactory>>(m, "ConcreteNPCFactory")
        .def(py::init<>())
        .def("create_npc", &ConcreteNPCFactory::createNPC);

    py::class_<Observer, std::shared_ptr<Observer>>(m, "Observer");

    py::class_<ConsoleObserver, Observer, std::shared_ptr<ConsoleObserver>>(m, "ConsoleObserver")
        .def(py::init<>());

    py::class_<FileObserver, Observer, std::shared_ptr<FileObserver>>(m, "FileObserver")
        .def(py::init<const std::string&>());

    py::class_<NPCVisitor, std::shared_ptr<NPCVisitor>>(m, "NPCVisitor");

    py::class_<NPCManager>(m, "NPCManager")
        .def(py::init<>())
        .def("add_npc", &NPCManager::addNPC)
        .def("get_npcs", &NPCManager::getNPCs, py::return_value_policy::reference_internal)
        .def("remove_dead_npcs", &NPCManager::removeDeadNPCs)
        .def("load_npcs_from_file", &NPCManager::loadNPCsFromFile);

    py::class_<FightVisitor, NPCVisitor, std::shared_ptr<FightVisitor>>(m, "FightVisitor")
        .def(py::init<NPCManager&>(), py::keep_alive<1, 2>())
        .def("add_observer", &FightVisitor::addObserver)
        .def("reset_processed_fights", &FightVisitor::resetProcessedFights)
        .def("get_targets", &FightVisitor::getTargets);
}
