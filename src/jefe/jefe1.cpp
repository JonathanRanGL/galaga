#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>

int main()
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Jefe1", sf::Style::Default);
    window.setFramerateLimit(60);

    sf::Texture textureJ1;
    if (!textureJ1.loadFromFile("./assets/images/jefe/jefe1.png"))
    {
        return -1;
    }

    sf::Sprite spriteJ1;
    spriteJ1.setTexture(textureJ1);
    spriteJ1.setPosition(400, 300);
    spriteJ1.setColor(sf::Color::Yellow);

    while (window.isOpen())
    {
        sf::Event eventJ1;
        while (window.pollEvent(eventJ1))
        {
            switch (eventJ1.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }
        }

        window.clear();
        window.draw(spriteJ1);
        window.display();
    }

    return EXIT_SUCCESS;
}