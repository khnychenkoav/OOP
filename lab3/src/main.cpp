#include "Figure.hpp"
#include "Triangle.hpp"
#include "Square.hpp"
#include "Octagon.hpp"
#include "MyVector.hpp"
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

int main() {
    MyVector<std::shared_ptr<Figure>> figures;
    std::string command;

    std::cout << "Commands: add, print, area, center, total_area, delete, draw, exit\n";

    while (true) {
        std::cout << "Enter command: ";
        std::cin >> command;

        if (command == "add") {
            std::string type;
            std::cout << "Enter figure type (triangle, square, octagon): ";
            std::cin >> type;

            if (type == "triangle") {
                auto triangle = std::make_shared<Triangle>();
                std::cout << "Enter 3 points (x y):\n";
                std::cin >> *triangle;
                figures.push_back(triangle);
            } else if (type == "square") {
                auto square = std::make_shared<Square>();
                std::cout << "Enter 4 points starting from top right(x y):\n";
                std::cin >> *square;
                figures.push_back(square);
            } else if (type == "octagon") {
                auto octagon = std::make_shared<Octagon>();
                std::cout << "Enter 8 points (x y):\n";
                std::cin >> *octagon;
                figures.push_back(octagon);
            } else {
                std::cout << "Unknown figure type.\n";
            }
        } else if (command == "print") {
            for (const auto& fig : figures) {
                fig->Print(std::cout);
            }
        } else if (command == "area") {
            for (const auto& fig : figures) {
                double area = static_cast<double>(*fig);
                std::cout << "Area: " << area << "\n";
            }
        } else if (command == "center") {
            for (const auto& fig : figures) {
                auto center = fig->GeometricCenter();
                std::cout << "Center: (" << center.first << ", " << center.second << ")\n";
            }
        } else if (command == "total_area") {
            double total_area = 0;
            for (const auto& fig : figures) {
                total_area += static_cast<double>(*fig);
            }
            std::cout << "Total area: " << total_area << "\n";
        } else if (command == "delete") {
            std::size_t index;
            std::cout << "Enter index to delete: ";
            std::cin >> index;
            try {
                figures.erase(index);
                std::cout << "Figure deleted.\n";
            } catch (const std::out_of_range& e) {
                std::cout << "Invalid index.\n";
            }
        } else if (command == "draw") {
            sf::RenderWindow window(sf::VideoMode(800, 600), "Figures");

            while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window.close();
                }

                window.clear(sf::Color::White);

                for (const auto& fig : figures) {
                    fig->Draw(window);
                }

                window.display();
            }
        } else if (command == "exit") {
            break;
        } else {
            std::cout << "Unknown command.\n";
        }
    }

    return 0;
}
