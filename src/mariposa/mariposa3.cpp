#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>

int main
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Mariposa3", sf::Style::Default);
    window.setFramerateLimit(60);

    sf::Texture textureM3;
    if (!textureM3.loadFromFile("./assets/images/mariposa/mariposa3.png"))
    {
        return -1;
    }

    sf::Sprite spriteM3;
    spriteM3.setTexture(textureM3);
    spriteM3.setPosition(400, 300);
    spriteM3.setColor(sf::Color::Yellow);

    while (window.isOpen())
    {
        sf::Event eventM3;
        while (window.pollEvent(eventM3))
        {
            switch (eventM3.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }
        }

        window.clear();
        window.draw(spriteM3);
        window.display();
    }

    return EXIT_SUCCESS;
}