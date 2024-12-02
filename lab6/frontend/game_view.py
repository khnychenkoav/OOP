import pygame
import sys
from controllers.game_controller import GameController
from utils.constants import SCREEN_WIDTH, SCREEN_HEIGHT, BG_COLOR, FPS

class GameView:
    def __init__(self):
        pygame.init()
        self.screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
        pygame.display.set_caption('Balagur Fate 3 Dungeon Editor')
        self.clock = pygame.time.Clock()
        self.controller = GameController()
        self.font = pygame.font.Font(None, 24)
        self.npc_images = {
            'Squirrel': pygame.image.load('resources/images/squirrel.png').convert_alpha(),
            'Elf': pygame.image.load('resources/images/elf.png').convert_alpha(),
            'Robber': pygame.image.load('resources/images/robber.png').convert_alpha(),
        }
        self.npc_colors = {
            'Squirrel': (255, 0, 0),
            'Elf': (0, 255, 0),
            'Robber': (0, 0, 255),
        }
        self.setup_ui()
        self.selected_npc_type = None

    def setup_ui(self):
        self.buttons = {
            'Start': {'rect': pygame.Rect(650, 50, 150, 40), 'color': (0, 200, 0)},
            'Stop': {'rect': pygame.Rect(650, 110, 150, 40), 'color': (200, 0, 0)},
            'Next Step': {'rect': pygame.Rect(650, 170, 150, 40), 'color': (0, 0, 200)},
            'Add Squirrel': {'rect': pygame.Rect(650, 230, 150, 40), 'color': (100, 100, 100)},
            'Add Elf': {'rect': pygame.Rect(650, 290, 150, 40), 'color': (100, 100, 100)},
            'Add Robber': {'rect': pygame.Rect(650, 350, 150, 40), 'color': (100, 100, 100)},
            'Save': {'rect': pygame.Rect(650, 410, 150, 40), 'color': (100, 100, 0)},
            'Load': {'rect': pygame.Rect(650, 470, 150, 40), 'color': (0, 100, 100)},
        }

    def draw_buttons(self):
        mouse_pos = pygame.mouse.get_pos()
        for name, button in self.buttons.items():
            rect = button['rect']
            color = button['color']
            hover = rect.collidepoint(mouse_pos)
            pygame.draw.rect(self.screen, color, rect, border_radius=10)
            if hover:
                pygame.draw.rect(self.screen, (255, 255, 255), rect, 3, border_radius=10)
            text_surf = self.font.render(name, True, (255, 255, 255))
            text_rect = text_surf.get_rect(center=rect.center)
            self.screen.blit(text_surf, text_rect)

    def draw_statistics(self):
        counts = {'Squirrel': 0, 'Elf': 0, 'Robber': 0}
        for npc in self.controller.get_npcs():
            if npc.is_alive():
                counts[npc.get_type()] += 1
        y = 10
        for npc_type, count in counts.items():
            bar_length = 100
            max_count = max(counts.values()) or 1  # Avoid division by zero
            bar_width = int((count / max_count) * bar_length)
            text_surf = self.font.render(f"{npc_type}s alive: {count}", True, (255, 255, 255))
            self.screen.blit(text_surf, (10, y))
            pygame.draw.rect(self.screen, (255, 255, 255), (150, y + 5, bar_length, 10), 1)
            pygame.draw.rect(self.screen, (0, 255, 0), (150, y + 5, bar_width, 10))
            y += 30

    def draw_panel(self):
        pygame.draw.rect(self.screen, (50, 50, 50), (600, 0, 200, SCREEN_HEIGHT))  # Панель управления
        pygame.draw.line(self.screen, (255, 255, 255), (600, 0), (600, SCREEN_HEIGHT), 3)  # Разделитель

    def draw_npcs(self):
        npcs = self.controller.get_npcs()
        targets = getattr(self.controller, 'targets', {})
        for npc in npcs:
            if npc.is_alive():
                x, y = int(npc.get_x()), int(npc.get_y())
                npc_type = npc.get_type()
                image = self.npc_images[npc.get_type()]
                rect = image.get_rect(center=(x, y))
                self.screen.blit(image, rect)

                color = self.npc_colors.get(npc_type, (255, 255, 255))
                # Draw attack radius
                fight_distance = self.controller.fight_distance
                pygame.draw.circle(self.screen, color, (x, y), int(fight_distance), 1)

                # Draw NPC name
                text = self.font.render(npc.get_name(), True, (255, 255, 255))
                self.screen.blit(text, (x + 10, y - 10))

                # Draw line to target
                target = targets.get(npc)
                if target and target.is_alive():
                    target_x, target_y = int(target.get_x()), int(target.get_y())
                    pygame.draw.line(self.screen, color, (x, y), (target_x, target_y))

    def draw(self):
        self.screen.fill(BG_COLOR)
        self.draw_panel()
        self.draw_npcs()
        self.draw_buttons()
        self.draw_statistics()
        if self.selected_npc_type:
            text_surf = self.font.render(f"Placing: {self.selected_npc_type}", True, (255, 255, 0))
            self.screen.blit(text_surf, (10, SCREEN_HEIGHT - 30))

    def handle_events(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                self.controller.cleanup()
                pygame.quit()
                sys.exit()
            elif event.type == pygame.MOUSEBUTTONDOWN:
                mouse_pos = event.pos
                for name, button in self.buttons.items():
                    if button['rect'].collidepoint(mouse_pos):
                        self.handle_button_click(name)
                if self.selected_npc_type:
                    x, y = mouse_pos
                    if x <= 500 and y <= 500:
                        npc_name = f"{self.selected_npc_type}_{len(self.controller.get_npcs())+1}"
                        self.controller.add_npc(self.selected_npc_type, npc_name, x, y)
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    self.selected_npc_type = None

    def handle_button_click(self, name):
        if name == 'Start':
            self.controller.paused = False
        elif name == 'Stop':
            self.controller.paused = True
        elif name == 'Next Step':
            self.controller.next_step()
        elif name == 'Add Squirrel':
            self.selected_npc_type = 'Squirrel'
        elif name == 'Add Elf':
            self.selected_npc_type = 'Elf'
        elif name == 'Add Robber':
            self.selected_npc_type = 'Robber'
        elif name == 'Save':
            self.controller.save_npcs('npcs.dat')
        elif name == 'Load':
            self.controller.load_npcs('npcs.dat')

    def update(self):
        if not self.controller.paused:
            self.controller.next_step()

    def main_loop(self):
        while True:
            self.handle_events()
            self.update()
            self.draw()
            pygame.display.flip()
            self.clock.tick(FPS)

if __name__ == "__main__":
    game = GameView()
    game.main_loop()
