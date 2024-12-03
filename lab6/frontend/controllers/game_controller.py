import pickle
import game_backend
import os

class GameController:
    def __init__(self):
        self.factory = game_backend.ConcreteNPCFactory()
        self.npc_manager = game_backend.NPCManager()
        self.paused = True
        self.visitor = game_backend.FightVisitor(self.npc_manager)
        self.console_observer = game_backend.ConsoleObserver()
        self.file_observer = game_backend.FileObserver('logs/log.txt')
        self.observers_added = False

        if not self.observers_added:
            self.visitor.add_observer(self.console_observer)
            self.visitor.add_observer(self.file_observer)
            self.observers_added = True

        os.makedirs('logs', exist_ok=True)

    def add_npc(self, npc_type, name, x, y):
        if 0 <= x <= 500 and 0 <= y <= 500:
            npc = self.factory.create_npc(npc_type, name, x, y)
            if npc:
                self.npc_manager.add_npc(npc)

    def get_npcs(self):
        return self.npc_manager.get_npcs()

    def save_npcs(self, filename):
        with open(filename, 'wb') as f:
            pickle.dump(self.npc_manager.get_npcs(), f)

    def load_npcs(self, filename):
        with open(filename, 'rb') as f:
            npcs = pickle.load(f)
            self.npc_manager = game_backend.NPCManager()
            for npc in npcs:
                self.npc_manager.add_npc(npc)
        self.visitor = game_backend.FightVisitor(self.npc_manager)
        self.visitor.add_observer(self.console_observer)
        self.visitor.add_observer(self.file_observer)

    def next_step(self):
        npcs = self.npc_manager.get_npcs()
        for npc in npcs:
            if npc.is_alive():
                target = self.find_target(npc, npcs)
                threat = self.find_threat(npc, npcs)
                if target:
                    npc.move_towards(target.get_x(), target.get_y())
                elif threat:
                    npc.move_away_from(threat.get_x(), threat.get_y())
                else:
                    npc.move()
        self.visitor.reset_processed_fights()
        self.targets = {}
        for npc in npcs:
            if npc.is_alive():
                npc.accept(self.visitor)
                target = self.visitor.get_targets().get(npc)
                if target:
                    self.targets[npc] = target
        self.npc_manager.remove_dead_npcs()

    def find_target(self, npc, npcs):
        npc_type = npc.get_type()
        for other_npc in npcs:
            if other_npc == npc or not other_npc.is_alive():
                continue
            if npc_type == "Elf" and other_npc.get_type() == "Robber":
                return other_npc
            elif npc_type == "Robber" and other_npc.get_type() == "Squirrel":
                return other_npc
            elif npc_type == "Squirrel" and other_npc.get_type() == "Elf":
                return other_npc
        return None

    def find_threat(self, npc, npcs):
        npc_type = npc.get_type()
        for other_npc in npcs:
            if other_npc == npc or not other_npc.is_alive():
                continue
            if (npc_type == "Elf" and other_npc.get_type() == "Squirrel") or \
               (npc_type == "Robber" and other_npc.get_type() == "Elf") or \
               (npc_type == "Squirrel" and other_npc.get_type() == "Robber"):
                return other_npc
        return None

    def load_npcs_from_file(self, filename):
        self.npc_manager.load_npcs_from_file(filename)
        self.visitor = game_backend.FightVisitor(self.npc_manager)
        self.visitor.add_observer(self.console_observer)
        self.visitor.add_observer(self.file_observer)

    def cleanup(self):
        pass
