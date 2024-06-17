#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>

int main
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Mariposa5", sf::Style::Default);
    window.setFramerateLimit(60);

    sf::Texture textureM5;
    if (!textureM5.loadFromFile("./assets/images/mariposa/mariposa5.png"))
    {
        return -1;
    }

    sf::Sprite spriteM5;
    spriteM5.setTexture(textureM5);
    spriteM5.setPosition(400, 300);
    spriteM5.setColor(sf::Color::Yellow);

    while (window.isOpen())
    {
        sf::Event eventM5;
        while (window.pollEvent(eventM5))
        {
            switch (eventM5.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }
        }

        window.clear();
        window.draw(spriteM5);
        window.display();
    }

    return EXIT_SUCCESS;
}
