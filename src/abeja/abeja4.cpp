#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>

int main()
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Abeja4", sf::Style::Default);
    window.setFramerateLimit(60);

    sf::Texture textureA4;
    if (!textureA4.loadFromFile("./assets/images/abeja/abeja4.png"))
    {
        return -1;
    }

    sf::Sprite spriteA4;
    spriteA4.setTexture(textureA4);
    spriteA4.setPosition(400, 300);
    spriteA4.setColor(sf::Color::Yellow);

    while (window.isOpen())
    {
        sf::Event eventA4;
        while (window.pollEvent(eventA4))
        {
            switch (eventA4.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }
        }

        window.clear();
        window.draw(spriteA4);
        window.display();
    }

    return EXIT_SUCCESS;
}