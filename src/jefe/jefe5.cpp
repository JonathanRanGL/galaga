#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>

int main()
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Jefe5", sf::Style::Default);
    window.setFramerateLimit(60);

    sf::Texture textureJ5;
    if (!textureJ5.loadFromFile("./assets/images/jefe/jefe5.png"))
    {
        return -1;
    }

    sf::Sprite spriteJ5;
    spriteJ5.setTexture(textureJ5);
    spriteJ5.setPosition(400, 300);
    spriteJ5.setColor(sf::Color::Yellow);

    while (window.isOpen())
    {
        sf::Event eventJ5;
        while (window.pollEvent(eventJ5))
        {
            switch (eventJ5.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }
        }

        window.clear();
        window.draw(spriteJ5);
        window.display();
    }

    return EXIT_SUCCESS;
}