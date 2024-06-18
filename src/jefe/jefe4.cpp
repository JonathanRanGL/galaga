#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>

int main()
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Jefe4", sf::Style::Default);
    window.setFramerateLimit(60);

    sf::Texture textureJ4;
    if (!textureJ4.loadFromFile("./assets/images/jefe/jefe4.png"))
    {
        return -1;
    }

    sf::Sprite spriteJ4;
    sprite4.setTexture(textureJ1);
    sprite4.setPosition(400, 300);
    sprite4.setColor(sf::Color::Yellow);

    while (window.isOpen())
    {
        sf::Event eventJ4;
        while (window.pollEvent(eventJ4))
        {
            switch (eventJ4.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }
        }

        window.clear();
        window.draw(spriteJ4);
        window.display();
    }

    return EXIT_SUCCESS;
}