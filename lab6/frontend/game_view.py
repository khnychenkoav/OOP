import pygame
import sys
import time
import math
import random
from controllers.game_controller import GameController
from utils.constants import SCREEN_WIDTH, SCREEN_HEIGHT, BG_COLOR, FPS

class Button:
    def __init__(self, text, rect, inactive_color, active_color, action=None, font=None):
        self.text = text
        self.rect = pygame.Rect(rect)
        self.initial_rect = self.rect.copy()
        self.inactive_color = inactive_color
        self.active_color = active_color
        self.color = inactive_color
        self.action = action
        self.font = font
        self.hovered = False
        self.animation_progress = 0
        self.visibility = 1.0
        self.full_width = self.rect.width
        self.hidden_width = 20
        self.visible_x = SCREEN_WIDTH - self.full_width
        self.hidden_x = SCREEN_WIDTH - self.hidden_width
        self.rect.x = self.hidden_x

    def draw(self, surface):
        self.update()
        shadow_offset = 5
        shadow_surface = pygame.Surface((self.rect.width, self.rect.height), pygame.SRCALPHA)
        shadow_color = (0, 0, 0, int(100 * self.visibility))
        pygame.draw.rect(shadow_surface, shadow_color, shadow_surface.get_rect(), border_radius=10)
        surface.blit(shadow_surface, (self.rect.x + shadow_offset, self.rect.y + shadow_offset))

        color_with_alpha = (*self.color[:3], int(255 * self.visibility))
        button_surface = pygame.Surface(self.rect.size, pygame.SRCALPHA)
        pygame.draw.rect(button_surface, color_with_alpha, button_surface.get_rect(), border_radius=10)
        if self.font:
            text_surf = self.font.render(self.text, True, (255, 255, 255))
            text_surf.set_alpha(int(255 * self.visibility))
            text_rect = text_surf.get_rect(center=button_surface.get_rect().center)
            button_surface.blit(text_surf, text_rect)
        surface.blit(button_surface, self.rect.topleft)

    def update(self):
        mouse_pos = pygame.mouse.get_pos()
        if self.rect.collidepoint(mouse_pos):
            self.hovered = True
            self.animation_progress = min(self.animation_progress + 0.1, 1)
        else:
            self.hovered = False
            self.animation_progress = max(self.animation_progress - 0.1, 0)

        self.rect.x = self.hidden_x + (self.visible_x - self.hidden_x) * self.ease_in_out(self.animation_progress)

        self.color = self.interpolate_color(self.inactive_color, self.active_color, self.ease_in_out(self.animation_progress))

        self.visibility = 0.7 + 0.3 * self.animation_progress  # От 0.7 до 1.0

    def interpolate_color(self, color_start, color_end, progress):
        return (
            int(color_start[0] + (color_end[0] - color_start[0]) * progress),
            int(color_start[1] + (color_end[1] - color_start[1]) * progress),
            int(color_start[2] + (color_end[2] - color_start[2]) * progress),
        )

    def ease_in_out(self, t):
        return t * t * (3 - 2 * t)

    def handle_event(self, event):
        if event.type == pygame.MOUSEBUTTONDOWN and self.rect.collidepoint(event.pos):
            if self.action:
                self.action()

class Notification:
    def __init__(self, text, duration, font, screen_width):
        self.text = text
        self.duration = duration
        self.start_time = time.time()
        self.font = font
        self.alpha = 0
        self.max_alpha = 200
        self.surface = None
        self.screen_width = screen_width

    def update(self):
        elapsed = time.time() - self.start_time
        if elapsed < self.duration:
            self.alpha = min(self.max_alpha, self.alpha + 5)
        else:
            self.alpha = max(0, self.alpha - 5)

        if self.alpha > 0:
            text_surf = self.font.render(self.text, True, (255, 255, 255))
            text_surf.set_alpha(self.alpha)
            self.surface = text_surf
        else:
            self.surface = None

    def draw(self, surface):
        if self.surface:
            rect = self.surface.get_rect(center=(self.screen_width // 2, 50))
            surface.blit(self.surface, rect)

class WeatherEffect:
    def __init__(self, effect_type, screen_size):
        self.effect_type = effect_type
        self.particles = []
        self.screen_width, self.screen_height = screen_size
        self.create_particles()

    def create_particles(self):
        for _ in range(100):
            x = random.randint(0, self.screen_width)
            y = random.randint(-self.screen_height, 0)
            speed = random.uniform(100, 200)
            self.particles.append({'pos': [x, y], 'speed': speed})

    def update(self, dt):
        for particle in self.particles:
            if self.effect_type == 'rain':
                particle['pos'][1] += particle['speed'] * dt
                particle['pos'][0] += random.uniform(-10, 10) * dt
            elif self.effect_type == 'snow':
                particle['pos'][1] += particle['speed'] * dt * 0.5
                particle['pos'][0] += random.uniform(-30, 30) * dt
            if particle['pos'][1] > self.screen_height:
                particle['pos'][1] = random.randint(-self.screen_height, 0)
                particle['pos'][0] = random.randint(0, self.screen_width)

    def draw(self, surface):
        for particle in self.particles:
            if self.effect_type == 'rain':
                pygame.draw.line(surface, (173, 216, 230), particle['pos'], (particle['pos'][0], particle['pos'][1] + 5))
            elif self.effect_type == 'snow':
                pygame.draw.circle(surface, (255, 250, 250), particle['pos'], 3)

class GameView:
    def __init__(self):
        pygame.init()
        self.screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
        pygame.display.set_caption('Balagur Fate 3 Dungeon Editor')
        self.clock = pygame.time.Clock()
        self.controller = GameController()
        self.font = pygame.font.Font('resources/fonts/Roboto-Regular.ttf', 20)
        self.large_font = pygame.font.Font('resources/fonts/Roboto-Bold.ttf', 28)
        self.generate_npc_images()
        self.npc_images = {
            'Squirrel': pygame.image.load('resources/images/generated/squirrel.png').convert_alpha(),
            'Elf': pygame.image.load('resources/images/generated/elf.png').convert_alpha(),
            'Robber': pygame.image.load('resources/images/generated/robber.png').convert_alpha(),
        }
        self.npc_colors = {
            'Squirrel': (255, 0, 0),
            'Elf': (0, 255, 0),
            'Robber': (0, 0, 255),
        }
        self.notifications = []
        self.selected_npc_type = None
        self.setup_ui()
        self.parallax_layers = self.load_parallax_background()
        self.forest_surface = self.generate_forest_background()
        self.time_of_day = 0
        self.weather = None
        self.last_weather_change = time.time()
        self.weather_effect = None

    def setup_ui(self):
        self.buttons = []
        button_y = 50
        button_spacing = 60
        button_data = [
            ('Start', self.start_simulation),
            ('Stop', self.stop_simulation),
            ('Next Step', self.next_step),
            ('Add Squirrel', lambda: self.select_npc('Squirrel')),
            ('Add Elf', lambda: self.select_npc('Elf')),
            ('Add Robber', lambda: self.select_npc('Robber')),
            ('Save', self.save_npcs),
            ('Load', self.load_npcs),
            ('Load From File', self.load_npcs_from_file),
        ]

        for text, action in button_data:
            button = Button(
                text=text,
                rect=(SCREEN_WIDTH - 20, button_y, 250, 50),
                inactive_color=(70, 70, 70),
                active_color=(100, 100, 100),
                action=action,
                font=self.font
            )
            self.buttons.append(button)
            button_y += button_spacing

    def start_simulation(self):
        self.controller.paused = False
        self.add_notification('Simulation Started')

    def stop_simulation(self):
        self.controller.paused = True
        self.add_notification('Simulation Stopped')

    def next_step(self):
        self.controller.next_step()
        self.add_notification('Next Step Executed')

    def select_npc(self, npc_type):
        self.selected_npc_type = npc_type
        self.add_notification(f'{npc_type} Selected')

    def save_npcs(self):
        self.controller.save_npcs('npcs.dat')
        self.add_notification('NPCs Saved')

    def load_npcs(self):
        self.controller.load_npcs('npcs.dat')
        self.add_notification('NPCs Loaded')

    def load_npcs_from_file(self):
        self.controller.load_npcs_from_file('npcs.txt')
        self.add_notification('NPCs Loaded from File')

    def add_notification(self, text):
        notification = Notification(text, duration=2, font=self.large_font, screen_width=SCREEN_WIDTH)
        self.notifications.append(notification)

    def load_parallax_background(self):
        layers = []
        for i in range(1, 4):
            layer = pygame.Surface((SCREEN_WIDTH, SCREEN_HEIGHT), pygame.SRCALPHA)
            green_value = 30 + i * 20
            layer.fill((green_value // 2, green_value, green_value // 2, 100))
            layers.append(layer)
        return layers

    def generate_forest_background(self):
        forest_surface = pygame.Surface((SCREEN_WIDTH, SCREEN_HEIGHT), pygame.SRCALPHA)
        tree_color = (34, 139, 34)
        num_trees = 150
        for _ in range(num_trees):
            x = random.randint(0, SCREEN_WIDTH - 50)
            y = random.randint(0, SCREEN_HEIGHT - 50)
            tree_width = random.randint(20, 40)
            tree_height = random.randint(40, 80)
            sway_offset = random.uniform(-5, 5)
            pygame.draw.rect(forest_surface, (139, 69, 19), (x + tree_width // 2 - 5 + sway_offset, y + tree_height // 2, 10, tree_height // 2))
            pygame.draw.ellipse(forest_surface, tree_color, (x + sway_offset, y, tree_width, tree_height))
        return forest_surface

    def update_forest_animation(self):
        self.forest_surface.scroll(dx=int(math.sin(time.time()) * 1), dy=0)

    def update_time_of_day(self):
        if int(time.time()) % 60 < 30:
            self.time_of_day = 0
        else:
            self.time_of_day = 1

    def update_weather(self):
        current_time = time.time()
        if current_time - self.last_weather_change > 20:
            self.last_weather_change = current_time
            self.weather = random.choice(['rain', 'snow', None])
            if self.weather:
                self.weather_effect = WeatherEffect(self.weather, (SCREEN_WIDTH, SCREEN_HEIGHT))
            else:
                self.weather_effect = None

    def draw_parallax_background(self):
        for i, layer in enumerate(self.parallax_layers):
            offset_x = i * 10
            offset_y = i * 10
            self.screen.blit(layer, (-offset_x, -offset_y))

    def draw_forest_background(self):
        self.screen.blit(self.forest_surface, (0, 0))

    def apply_time_of_day_effect(self):
        overlay = pygame.Surface((SCREEN_WIDTH, SCREEN_HEIGHT), pygame.SRCALPHA)
        if self.time_of_day == 1:
            overlay.fill((0, 0, 30, 100))
        else:
            overlay.fill((255, 255, 224, 30))
        self.screen.blit(overlay, (0, 0))

    def draw_weather_effects(self, dt):
        if self.weather_effect:
            self.weather_effect.update(dt)
            self.weather_effect.draw(self.screen)

    def draw_buttons(self):
        for button in self.buttons:
            button.draw(self.screen)

    def draw_statistics(self):
        counts = {'Squirrel': 0, 'Elf': 0, 'Robber': 0}
        for npc in self.controller.get_npcs():
            if npc.is_alive():
                counts[npc.get_type()] += 1
        y = 10
        for npc_type, count in counts.items():
            bar_length = 150
            max_count = max(counts.values()) or 1
            bar_width = int((count / max_count) * bar_length)
            text_surf = self.font.render(f"{npc_type}s alive: {count}", True, (255, 255, 255))
            self.screen.blit(text_surf, (20, y))
            pygame.draw.rect(self.screen, (100, 100, 100), (200, y + 5, bar_length, 20), border_radius=5)
            pygame.draw.rect(self.screen, (0, 200, 0), (200, y + 5, bar_width, 20), border_radius=5)
            y += 40
    def draw_npcs(self):
        npcs = self.controller.get_npcs()
        targets = getattr(self.controller, 'targets', {})
        for npc in npcs:
            x, y = int(npc.get_x()), int(npc.get_y())
            npc_type = npc.get_type()
            image = self.npc_images[npc_type]
            rect = image.get_rect(center=(x, y))
            shadow = pygame.Surface((rect.width, rect.height), pygame.SRCALPHA)
            pygame.draw.ellipse(shadow, (0, 0, 0, 100), shadow.get_rect())
            self.screen.blit(shadow, (rect.x, rect.y + 10))
            self.screen.blit(image, rect)

            color = self.npc_colors.get(npc_type, (255, 255, 255))
            attack_range = npc.get_attack_range()
            pygame.draw.circle(self.screen, color, (x, y), int(attack_range), 1)

            text = self.font.render(npc.get_name(), True, (255, 255, 255))
            self.screen.blit(text, (x + 10, y - 10))

            health = npc.get_health()
            health_bar_width = 40
            max_health = npc.get_health()
            health_ratio = health / max_health
            health_bar_color = (int(255 * (1 - health_ratio)), int(255 * health_ratio), 0)
            pygame.draw.rect(self.screen, (100, 100, 100), (x - health_bar_width // 2, y - 30, health_bar_width, 5))
            pygame.draw.rect(self.screen, health_bar_color, (x - health_bar_width // 2, y - 30, int(health_bar_width * health_ratio), 5))

            target = targets.get(npc)
            if target and target.is_alive():
                target_x, target_y = int(target.get_x()), int(target.get_y())
                pygame.draw.line(self.screen, color, (x, y), (target_x, target_y), 1)

    def draw_notifications(self):
        for notification in self.notifications[:]:
            notification.update()
            notification.draw(self.screen)
            if notification.alpha == 0:
                self.notifications.remove(notification)

    def draw(self):
        self.draw_parallax_background()
        self.draw_forest_background()
        self.apply_time_of_day_effect()
        self.draw_weather_effects(self.clock.get_time() / 1000)
        self.draw_npcs()
        self.draw_buttons()
        self.draw_statistics()
        self.draw_notifications()
        if self.selected_npc_type:
            text_surf = self.font.render(f"Placing: {self.selected_npc_type}", True, (255, 255, 0))
            self.screen.blit(text_surf, (20, SCREEN_HEIGHT - 40))

    def handle_events(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                self.controller.cleanup()
                pygame.quit()
                sys.exit()
            elif event.type == pygame.MOUSEBUTTONDOWN:
                for button in self.buttons:
                    button.handle_event(event)
                if self.selected_npc_type:
                    x, y = pygame.mouse.get_pos()
                    if x <= SCREEN_WIDTH:
                        npc_name = f"{self.selected_npc_type}_{len(self.controller.get_npcs())+1}"
                        self.controller.add_npc(self.selected_npc_type, npc_name, x, y)
                        self.add_notification(f"{self.selected_npc_type} Added")
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    self.selected_npc_type = None
        for button in self.buttons:
            button.update()

    def update(self):
        if not self.controller.paused:
            self.controller.next_step()
        self.update_forest_animation()
        self.update_time_of_day()
        self.update_weather()

    def main_loop(self):
        while True:
            self.handle_events()
            self.update()
            self.draw()
            pygame.display.flip()
            self.clock.tick(FPS)

    def generate_npc_images(self):
        from generate_images import generate_npc_images
        generate_npc_images()

if __name__ == "__main__":
    game = GameView()
    game.main_loop()
