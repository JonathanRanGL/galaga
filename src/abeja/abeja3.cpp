#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>

int main()
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Abeja3", sf::Style::Default);
    window.setFramerateLimit(60);

    sf::Texture textureA3;
    if (!textureA3.loadFromFile("./assets/images/abeja/abeja3.png"))
    {
        return -1;
    }

    sf::Sprite spriteA3;
    spriteA3.setTexture(textureA3);
    spriteA3.setPosition(400, 300);
    spriteA3.setColor(sf::Color::Yellow);

    while (window.isOpen())
    {
        sf::Event eventA3;
        while (window.pollEvent(eventA3))
        {
            switch (eventA3.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }
        }

        window.clear();
        window.draw(spriteA3);
        window.display();
    }

    return EXIT_SUCCESS;
}