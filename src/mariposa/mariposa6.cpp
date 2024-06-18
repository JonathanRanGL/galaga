#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>

int main
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Mariposa6", sf::Style::Default);
    window.setFramerateLimit(60);

    sf::Texture textureM6;
    if (!textureM6.loadFromFile("./assets/images/mariposa/mariposa6.png"))
    {
        return -1;
    }

    sf::Sprite spriteM6;
    spriteM6.setTexture(textureM6);
    spriteM6.setPosition(400, 300);
    spriteM6.setColor(sf::Color::Yellow);

    while (window.isOpen())
    {
        sf::Event eventM6;
        while (window.pollEvent(eventM6))
        {
            switch (eventM6.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }
        }

        window.clear();
        window.draw(spriteM6);
        window.display();
    }

    return EXIT_SUCCESS;
}
