#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>

int main
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Mariposa1", sf::Style::Default);
    window.setFramerateLimit(60);

    sf::Texture textureM1;
    if (!textureM1.loadFromFile("./assets/images/mariposa/mariposa1.png"))
    {
        return -1;
    }

    sf::Sprite spriteM1;
    spriteM1.setTexture(textureM1);
    spriteM1.setPosition(400, 300);
    spriteM1.setColor(sf::Color::Yellow);

    while (window.isOpen())
    {
        sf::Event eventM1;
        while (window.pollEvent(eventM1))
        {
            switch (eventM1.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }
        }

        window.clear();
        window.draw(spriteM1);
        window.display();
    }

    return EXIT_SUCCESS;
}
