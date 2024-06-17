#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>

int main
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Mariposa4", sf::Style::Default);
    window.setFramerateLimit(60);

    sf::Texture textureM4;
    if (!textureM4.loadFromFile("./assets/images/mariposa/mariposa4.png"))
    {
        return -1;
    }

    sf::Sprite spriteM4;
    spriteM4.setTexture(textureM4);
    spriteM4.setPosition(400, 300);
    spriteM4.setColor(sf::Color::Yellow);

    while (window.isOpen())
    {
        sf::Event eventM4;
        while (window.pollEvent(eventM4))
        {
            switch (eventM4.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }
        }

        window.clear();
        window.draw(spriteM4);
        window.display();
    }

    return EXIT_SUCCESS;
}
