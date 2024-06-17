#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>

int main
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Mariposa2", sf::Style::Default);
    window.setFramerateLimit(60);

    sf::Texture textureM2;
    if (!textureM2.loadFromFile("./assets/images/mariposa/mariposa2.png"))
    {
        return -1;
    }

    sf::Sprite spriteM2;
    spriteM2.setTexture(textureM2);
    spriteM2.setPosition(400, 300);
    spriteM2.setColor(sf::Color::Yellow);

    while (window.isOpen())
    {
        sf::Event eventM2;
        while (window.pollEvent(eventM2))
        {
            switch (eventM2.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }
        }

        window.clear();
        window.draw(spriteM2);
        window.display();
    }

    return EXIT_SUCCESS;
}
