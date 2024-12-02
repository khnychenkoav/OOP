# generate_images.py

import os
import random
from PIL import Image, ImageDraw
import numpy as np

def generate_npc_images(output_dir='resources/images/generated', image_size=(128, 128)):
    os.makedirs(output_dir, exist_ok=True)
    npc_types = ['Squirrel', 'Elf', 'Robber']
    for npc_type in npc_types:
        style = random.choice(['standard', 'pixel', 'geometric'])
        image_path = os.path.join(output_dir, f'{npc_type.lower()}.png')
        if style == 'standard':
            generate_standard_image(npc_type, image_path, image_size)
        elif style == 'pixel':
            generate_pixel_art_image(npc_type, image_path, image_size)
        elif style == 'geometric':
            generate_geometric_image(npc_type, image_path, image_size)

def generate_standard_image(npc_type, image_path, image_size):
    if npc_type == 'Squirrel':
        generate_standard_squirrel_image(image_path, image_size)
    elif npc_type == 'Elf':
        generate_standard_elf_image(image_path, image_size)
    elif npc_type == 'Robber':
        generate_standard_robber_image(image_path, image_size)

def generate_pixel_art_image(npc_type, image_path, image_size):
    pixel_size = random.choice([8, 16])
    small_image_size = (image_size[0] // pixel_size, image_size[1] // pixel_size)
    small_image = Image.new('RGBA', small_image_size, (0, 0, 0, 0))
    draw = ImageDraw.Draw(small_image)
    if npc_type == 'Squirrel':
        draw_pixel_squirrel(draw, small_image_size)
    elif npc_type == 'Elf':
        draw_pixel_elf(draw, small_image_size)
    elif npc_type == 'Robber':
        draw_pixel_robber(draw, small_image_size)
    pixel_image = small_image.resize(image_size, Image.NEAREST)
    pixel_image.save(image_path, 'PNG')

def generate_geometric_image(npc_type, image_path, image_size):
    image = Image.new('RGBA', image_size, (255, 255, 255, 0))
    draw = ImageDraw.Draw(image)
    if npc_type == 'Squirrel':
        draw_geometric_squirrel(draw, image_size)
    elif npc_type == 'Elf':
        draw_geometric_elf(draw, image_size)
    elif npc_type == 'Robber':
        draw_geometric_robber(draw, image_size)
    image.save(image_path, 'PNG')

def generate_standard_squirrel_image(image_path, image_size):
    image = Image.new('RGBA', image_size, (0, 0, 0, 0))
    draw = ImageDraw.Draw(image)
    width, height = image_size
    body_color = random_color(base_color=(139, 69, 19), variance=30)
    body_coords = [width * 0.3, height * 0.5, width * 0.7, height * 0.9]
    draw.ellipse(body_coords, fill=body_color)
    head_radius = width * 0.15
    head_center = (width * 0.5, height * 0.35)
    head_color = random_color(base_color=(160, 82, 45), variance=30)
    draw.ellipse([
        head_center[0] - head_radius, head_center[1] - head_radius,
        head_center[0] + head_radius, head_center[1] + head_radius
    ], fill=head_color)
    ear_size = width * random.uniform(0.04, 0.06)
    left_ear_coords = [
        (head_center[0] - ear_size, head_center[1] - head_radius),
        (head_center[0] - ear_size * 2, head_center[1] - head_radius - ear_size * 2),
        (head_center[0], head_center[1] - head_radius - ear_size)
    ]
    right_ear_coords = [
        (head_center[0] + ear_size, head_center[1] - head_radius),
        (head_center[0] + ear_size * 2, head_center[1] - head_radius - ear_size * 2),
        (head_center[0], head_center[1] - head_radius - ear_size)
    ]
    draw.polygon(left_ear_coords, fill=head_color)
    draw.polygon(right_ear_coords, fill=head_color)
    tail_variation = random.uniform(-0.1, 0.1)
    tail_coords = [
        width * (0.65 + tail_variation), height * (0.3 + tail_variation),
        width * (0.9 + tail_variation), height * (0.8 + tail_variation)
    ]
    tail_color = random_color(base_color=(205, 133, 63), variance=30)
    draw.ellipse(tail_coords, fill=tail_color)
    draw_eyes(draw, head_center, head_radius, width)
    add_squirrel_accessory(draw, width, height)
    image.save(image_path, 'PNG')

def add_squirrel_accessory(draw, width, height):
    accessory_type = random.choice(['acorn', 'scarf', 'hat', 'none'])
    if accessory_type == 'acorn':
        acorn_center = (width * random.uniform(0.4, 0.6), height * random.uniform(0.65, 0.75))
        acorn_radius = width * random.uniform(0.03, 0.05)
        draw.ellipse([
            acorn_center[0] - acorn_radius, acorn_center[1] - acorn_radius,
            acorn_center[0] + acorn_radius, acorn_center[1] + acorn_radius
        ], fill=(139, 69, 19))
    elif accessory_type == 'scarf':
        scarf_color = random_color()
        scarf_coords = [
            width * 0.4, height * 0.45,
            width * 0.6, height * 0.5
        ]
        draw.rectangle(scarf_coords, fill=scarf_color)
    elif accessory_type == 'hat':
        hat_color = random_color()
        hat_coords = [
            (width * 0.4, height * 0.2),
            (width * 0.5, height * 0.1),
            (width * 0.6, height * 0.2)
        ]
        draw.polygon(hat_coords, fill=hat_color)

def generate_standard_elf_image(image_path, image_size):
    image = Image.new('RGBA', image_size, (0, 0, 0, 0))
    draw = ImageDraw.Draw(image)
    width, height = image_size
    body_color = random_color(base_color=(34, 139, 34), variance=40)
    body_coords = [width * 0.4, height * 0.6, width * 0.6, height * 0.9]
    draw.rectangle(body_coords, fill=body_color)
    head_radius = width * 0.12
    head_center = (width * 0.5, height * 0.45)
    skin_tone = random_skin_tone()
    draw.ellipse([
        head_center[0] - head_radius, head_center[1] - head_radius,
        head_center[0] + head_radius, head_center[1] + head_radius
    ], fill=skin_tone)
    hat_color = random_color(base_color=(0, 100, 0), variance=30)
    hat_coords = [
        (head_center[0], head_center[1] - head_radius * 1.5),
        (head_center[0] - head_radius * 1.2, head_center[1] - head_radius * 0.2),
        (head_center[0] + head_radius * 1.2, head_center[1] - head_radius * 0.2)
    ]
    draw.polygon(hat_coords, fill=hat_color)
    ear_size = width * random.uniform(0.03, 0.05)
    left_ear_coords = [
        (head_center[0] - head_radius, head_center[1]),
        (head_center[0] - head_radius - ear_size, head_center[1] - ear_size * 2),
        (head_center[0] - head_radius - ear_size, head_center[1] + ear_size * 2)
    ]
    right_ear_coords = [
        (head_center[0] + head_radius, head_center[1]),
        (head_center[0] + head_radius + ear_size, head_center[1] - ear_size * 2),
        (head_center[0] + head_radius + ear_size, head_center[1] + ear_size * 2)
    ]
    draw.polygon(left_ear_coords, fill=skin_tone)
    draw.polygon(right_ear_coords, fill=skin_tone)
    draw_eyes(draw, head_center, head_radius, width)
    add_elf_accessory(draw, width, height)
    image.save(image_path, 'PNG')

def add_elf_accessory(draw, width, height):
    accessory_type = random.choice(['sword', 'bow', 'shield', 'none'])
    if accessory_type == 'sword':
        sword_coords = [
            width * 0.55, height * 0.7,
            width * 0.57, height * 0.9
        ]
        draw.rectangle(sword_coords, fill=(192, 192, 192))
        handle_coords = [
            width * 0.54, height * 0.9,
            width * 0.58, height * 0.92
        ]
        draw.rectangle(handle_coords, fill=(139, 69, 19))
    elif accessory_type == 'bow':
        bow_color = random_color()
        bow_coords = [
            width * 0.45, height * 0.6,
            width * 0.47, height * 0.8
        ]
        draw.arc(bow_coords, start=0, end=180, fill=bow_color, width=2)
        draw.line([width * 0.46, height * 0.6, width * 0.46, height * 0.8], fill=(0, 0, 0), width=1)
    elif accessory_type == 'shield':
        shield_color = random_color()
        shield_coords = [
            width * 0.4, height * 0.7,
            width * 0.45, height * 0.85
        ]
        draw.ellipse(shield_coords, fill=shield_color)

def generate_standard_robber_image(image_path, image_size):
    image = Image.new('RGBA', image_size, (0, 0, 0, 0))
    draw = ImageDraw.Draw(image)
    width, height = image_size
    body_color = random_color(base_color=(105, 105, 105), variance=30)
    body_coords = [width * 0.4, height * 0.6, width * 0.6, height * 0.9]
    draw.rectangle(body_coords, fill=body_color)
    head_radius = width * 0.12
    head_center = (width * 0.5, height * 0.45)
    skin_tone = random_skin_tone()
    draw.ellipse([
        head_center[0] - head_radius, head_center[1] - head_radius,
        head_center[0] + head_radius, head_center[1] + head_radius
    ], fill=skin_tone)
    mask_height = head_radius * random.uniform(0.4, 0.6)
    mask_coords = [
        head_center[0] - head_radius, head_center[1] - mask_height / 2,
        head_center[0] + head_radius, head_center[1] + mask_height / 2
    ]
    draw.rectangle(mask_coords, fill=(0, 0, 0, 255))
    draw_eyes(draw, head_center, head_radius, width, eye_color=(255, 255, 255, 255))
    add_robber_accessory(draw, width, height)
    image.save(image_path, 'PNG')

def add_robber_accessory(draw, width, height):
    accessory_type = random.choice(['bag', 'dagger', 'hat', 'none'])
    if accessory_type == 'bag':
        bag_coords = [
            width * 0.55, height * 0.75,
            width * 0.65, height * 0.85
        ]
        draw.ellipse(bag_coords, fill=(139, 69, 19))
        draw.line([width * 0.6, height * 0.75, width * 0.6, height * 0.8], fill=(0, 0, 0), width=1)
    elif accessory_type == 'dagger':
        dagger_coords = [
            width * 0.45, height * 0.8,
            width * 0.47, height * 0.9
        ]
        draw.polygon([
            (dagger_coords[0], dagger_coords[1]),
            (dagger_coords[0] + (width * 0.01), dagger_coords[1] + (height * 0.1)),
            (dagger_coords[0] - (width * 0.01), dagger_coords[1] + (height * 0.1))
        ], fill=(192, 192, 192))
        handle_coords = [
            dagger_coords[0] - (width * 0.01), dagger_coords[1] + (height * 0.1),
            dagger_coords[0] + (width * 0.01), dagger_coords[1] + (height * 0.12)
        ]
        draw.rectangle(handle_coords, fill=(139, 69, 19))
    elif accessory_type == 'hat':
        hat_color = random_color()
        hat_coords = [
            (head_center[0] - head_radius, head_center[1] - head_radius * 1.2),
            (head_center[0] + head_radius, head_center[1] - head_radius * 1.2),
            (head_center[0] + head_radius, head_center[1] - head_radius),
            (head_center[0] - head_radius, head_center[1] - head_radius)
        ]
        draw.polygon(hat_coords, fill=hat_color)

def draw_pixel_squirrel(draw, size):
    width, height = size
    body_color = random_color(base_color=(139, 69, 19), variance=30)
    tail_color = random_color(base_color=(160, 82, 45), variance=30)
    eye_color = (0, 0, 0, 255)
    draw.rectangle([width // 4, height // 2, width // 2, height - 1], fill=body_color)
    draw.rectangle([width // 4, height // 4, width // 2, height // 2], fill=body_color)
    draw.rectangle([width // 2, height // 3, width // 2 + width // 4, height - 1], fill=tail_color)
    draw.point((width // 3, height // 3), fill=eye_color)
    accessory = random.choice(['acorn', 'none'])
    if accessory == 'acorn':
        draw.point((width // 2, height // 2), fill=(139, 69, 19))

def draw_pixel_elf(draw, size):
    width, height = size
    body_color = random_color(base_color=(34, 139, 34), variance=40)
    skin_color = random_skin_tone()
    eye_color = (255, 255, 255, 255)
    hat_color = random_color(base_color=(0, 100, 0), variance=30)
    draw.rectangle([width // 3, height // 2, width // 3 + 1, height - 1], fill=body_color)
    draw.rectangle([width // 3, height // 3, width // 3 + 1, height // 2], fill=skin_color)
    draw.point((width // 3, height // 3 - 1), fill=hat_color)
    draw.point((width // 3, height // 3), fill=eye_color)
    accessory = random.choice(['sword', 'none'])
    if accessory == 'sword':
        draw.line((width // 2, height // 2, width // 2, height - 1), fill=(192, 192, 192))

def draw_pixel_robber(draw, size):
    width, height = size
    body_color = random_color(base_color=(105, 105, 105), variance=30)
    skin_color = random_skin_tone()
    eye_color = (255, 255, 255, 255)
    mask_color = (0, 0, 0, 255)
    draw.rectangle([width // 3, height // 2, width // 3 + 1, height - 1], fill=body_color)
    draw.rectangle([width // 3, height // 3, width // 3 + 1, height // 2], fill=skin_color)
    draw.point((width // 3, height // 3), fill=mask_color)
    draw.point((width // 3, height // 3), fill=eye_color)
    accessory = random.choice(['bag', 'none'])
    if accessory == 'bag':
        draw.point((width // 3 + 1, height // 2 + 1), fill=(139, 69, 19))

def draw_geometric_squirrel(draw, size):
    width, height = size
    colors = generate_color_palette()
    body_coords = [
        (width * random.uniform(0.25, 0.35), height * random.uniform(0.5, 0.6)),
        (width * 0.5, height * random.uniform(0.8, 0.9)),
        (width * random.uniform(0.65, 0.75), height * random.uniform(0.5, 0.6))
    ]
    draw.polygon(body_coords, fill=colors[0])
    draw.ellipse([
        width * random.uniform(0.4, 0.45), height * random.uniform(0.25, 0.35),
        width * random.uniform(0.55, 0.6), height * random.uniform(0.4, 0.5)
    ], fill=colors[1])
    tail_coords = [
        (width * random.uniform(0.65, 0.75), height * random.uniform(0.5, 0.6)),
        (width * random.uniform(0.85, 0.95), height * random.uniform(0.3, 0.4)),
        (width * random.uniform(0.85, 0.95), height * random.uniform(0.6, 0.7))
    ]
    draw.polygon(tail_coords, fill=colors[2])

def draw_geometric_elf(draw, size):
    width, height = size
    colors = generate_color_palette()
    body_coords = [
        (width * 0.5, height * random.uniform(0.8, 0.9)),
        (width * random.uniform(0.3, 0.4), height * random.uniform(0.5, 0.6)),
        (width * random.uniform(0.6, 0.7), height * random.uniform(0.5, 0.6))
    ]
    draw.polygon(body_coords, fill=colors[0])
    draw.rectangle([
        width * random.uniform(0.4, 0.45), height * random.uniform(0.4, 0.45),
        width * random.uniform(0.55, 0.6), height * random.uniform(0.5, 0.55)
    ], fill=colors[1])
    hat_coords = [
        (width * 0.5, height * random.uniform(0.2, 0.3)),
        (width * random.uniform(0.4, 0.45), height * random.uniform(0.4, 0.45)),
        (width * random.uniform(0.55, 0.6), height * random.uniform(0.4, 0.45))
    ]
    draw.polygon(hat_coords, fill=colors[2])
    draw.polygon([
        (width * random.uniform(0.4, 0.45), height * random.uniform(0.45, 0.5)),
        (width * random.uniform(0.35, 0.4), height * random.uniform(0.4, 0.45)),
        (width * random.uniform(0.4, 0.45), height * random.uniform(0.35, 0.4))
    ], fill=colors[1])
    draw.polygon([
        (width * random.uniform(0.55, 0.6), height * random.uniform(0.45, 0.5)),
        (width * random.uniform(0.6, 0.65), height * random.uniform(0.4, 0.45)),
        (width * random.uniform(0.55, 0.6), height * random.uniform(0.35, 0.4))
    ], fill=colors[1])

def draw_geometric_robber(draw, size):
    width, height = size
    colors = generate_color_palette()
    draw.rectangle([
        width * random.uniform(0.4, 0.45), height * random.uniform(0.6, 0.65),
        width * random.uniform(0.55, 0.6), height * random.uniform(0.85, 0.9)
    ], fill=colors[0])
    draw.rectangle([
        width * random.uniform(0.4, 0.45), height * random.uniform(0.45, 0.5),
        width * random.uniform(0.55, 0.6), height * random.uniform(0.6, 0.65)
    ], fill=colors[1])
    draw.rectangle([
        width * random.uniform(0.4, 0.45), height * random.uniform(0.5, 0.55),
        width * random.uniform(0.55, 0.6), height * random.uniform(0.55, 0.6)
    ], fill=colors[2])

def draw_eyes(draw, head_center, head_radius, width, eye_color=(0, 0, 0, 255)):
    eye_radius = width * 0.015
    eye_offset_x = head_radius * 0.4
    eye_offset_y = -head_radius * 0.2
    left_eye_center = (head_center[0] - eye_offset_x, head_center[1] + eye_offset_y)
    draw.ellipse([
        left_eye_center[0] - eye_radius, left_eye_center[1] - eye_radius,
        left_eye_center[0] + eye_radius, left_eye_center[1] + eye_radius
    ], fill=eye_color)
    right_eye_center = (head_center[0] + eye_offset_x, head_center[1] + eye_offset_y)
    draw.ellipse([
        right_eye_center[0] - eye_radius, right_eye_center[1] - eye_radius,
        right_eye_center[0] + eye_radius, right_eye_center[1] + eye_radius
    ], fill=eye_color)

def random_color(base_color=(255, 255, 255), variance=50):
    r = clamp(base_color[0] + random.randint(-variance, variance), 0, 255)
    g = clamp(base_color[1] + random.randint(-variance, variance), 0, 255)
    b = clamp(base_color[2] + random.randint(-variance, variance), 0, 255)
    return (r, g, b, 255)

def random_skin_tone():
    base_skin_tones = [
        (255, 224, 189),
        (241, 194, 125),
        (224, 172, 105),
        (198, 134, 66),
        (141, 85, 36),
    ]
    base_color = random.choice(base_skin_tones)
    return random_color(base_color=base_color, variance=20)

def clamp(value, min_value, max_value):
    return max(min_value, min(value, max_value))

def generate_color_palette():
    base_hue = random.uniform(0, 360)
    colors = []
    for i in range(3):
        hue = (base_hue + i * 120) % 360
        color = hsv_to_rgb(hue, random.uniform(0.5, 1.0), random.uniform(0.5, 1.0))
        colors.append(color)
    return colors

def hsv_to_rgb(h, s, v):
    h = float(h)
    s = float(s)
    v = float(v)
    h = h % 360
    c = v * s
    x = c * (1 - abs(((h / 60) % 2) - 1))
    m = v - c
    if h < 60:
        r, g, b = c, x, 0
    elif h < 120:
        r, g, b = x, c, 0
    elif h < 180:
        r, g, b = 0, c, x
    elif h < 240:
        r, g, b = 0, x, c
    elif h < 300:
        r, g, b = x, 0, c
    else:
        r, g, b = c, 0, x
    r = int((r + m) * 255)
    g = int((g + m) * 255)
    b = int((b + m) * 255)
    return (r, g, b, 255)

if __name__ == '__main__':
    generate_npc_images()
