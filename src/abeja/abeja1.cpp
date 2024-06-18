#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>

int main()
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Abeja1", sf::Style::Default);
    window.setFramerateLimit(60);

    sf::Texture textureA1;
    if (!textureA1.loadFromFile("./assets/images/abeja/abeja1.png"))
    {
        return -1;
    }

    sf::Sprite spriteA1;
    spriteA1.setTexture(textureA1);
    spriteA1.setPosition(400, 300);
    spriteA1.setColor(sf::Color::Yellow);

    while (window.isOpen())
    {
        sf::Event eventA1;
        while (window.pollEvent(eventA1))
        {
            switch (eventA1.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }
        }

        window.clear();
        window.draw(spriteA1);
        window.display();
    }

    return EXIT_SUCCESS;
}