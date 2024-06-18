#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>

int main()
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Jefe2", sf::Style::Default);
    window.setFramerateLimit(60);

    sf::Texture textureJ2;
    if (!textureJ2.loadFromFile("./assets/images/jefe/jefe2.png"))
    {
        return -1;
    }

    sf::Sprite spriteJ2;
    spriteJ2.setTexture(textureJ2);
    spriteJ2.setPosition(400, 300);
    spriteJ2.setColor(sf::Color::Yellow);

    while (window.isOpen())
    {
        sf::Event eventJ2;
        while (window.pollEvent(eventJ2))
        {
            switch (eventJ2.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }
        }

        window.clear();
        window.draw(spriteJ2);
        window.display();
    }

    return EXIT_SUCCESS;
}