#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>

int main()
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Abeja2", sf::Style::Default);
    window.setFramerateLimit(60);

    sf::Texture textureA2;
    if (!textureA2.loadFromFile("./assets/images/abeja/abeja2.png"))
    {
        return -1;
    }

    sf::Sprite spriteA2;
    spriteA2.setTexture(textureA2);
    spriteA2.setPosition(400, 300);
    spriteA2.setColor(sf::Color::Yellow);

    while (window.isOpen())
    {
        sf::Event eventA2;
        while (window.pollEvent(eventA2))
        {
            switch (eventA2.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }
        }

        window.clear();
        window.draw(spriteA2);
        window.display();
    }

    return EXIT_SUCCESS;
}