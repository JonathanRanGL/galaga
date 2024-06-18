#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>

int main()
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Abeja6", sf::Style::Default);
    window.setFramerateLimit(60);

    sf::Texture textureA6;
    if (!textureA6.loadFromFile("./assets/images/abeja/abeja6.png"))
    {
        return -1;
    }

    sf::Sprite spriteA6;
    spriteA6.setTexture(textureA6);
    spriteA6.setPosition(400, 300);
    spriteA6.setColor(sf::Color::Yellow);

    while (window.isOpen())
    {
        sf::Event eventA6;
        while (window.pollEvent(eventA6))
        {
            switch (eventA6.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }
        }

        window.clear();
        window.draw(spriteA6);
        window.display();
    }

    return EXIT_SUCCESS;
}