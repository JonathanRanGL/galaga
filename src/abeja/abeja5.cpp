#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>

int main()
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Abeja5", sf::Style::Default);
    window.setFramerateLimit(60);

    sf::Texture textureA5;
    if (!textureA5.loadFromFile("./assets/images/abeja/abeja5.png"))
    {
        return -1;
    }

    sf::Sprite spriteA5;
    spriteA5.setTexture(textureA5);
    spriteA5.setPosition(400, 300);
    spriteA5.setColor(sf::Color::Yellow);

    while (window.isOpen())
    {
        sf::Event eventA5;
        while (window.pollEvent(eventA5))
        {
            switch (eventA5.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }
        }

        window.clear();
        window.draw(spriteA5);
        window.display();
    }

    return EXIT_SUCCESS;
}