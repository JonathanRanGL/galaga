#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>

int main()
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Jefe3", sf::Style::Default);
    window.setFramerateLimit(60);

    sf::Texture textureJ3;
    if (!textureJ3.loadFromFile("./assets/images/jefe/jefe3.png"))
    {
        return -1;
    }

    sf::Sprite spriteJ3;
    spriteJ3.setTexture(textureJ3);
    spriteJ3.setPosition(400, 300);
    spriteJ3.setColor(sf::Color::Yellow);

    while (window.isOpen())
    {
        sf::Event eventJ3;
        while (window.pollEvent(eventJ3))
        {
            switch (eventJ3.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }
        }

        window.clear();
        window.draw(spriteJ3);
        window.display();
    }

    return EXIT_SUCCESS;
}