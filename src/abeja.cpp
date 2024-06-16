#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>

int main()
{ 
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Abeja", sf::Style::Default);
    window.setFramerateLimit(60); 

    sf::Texture textureA;
    if (!textureA.loadFromFile("assets/Abeja.png"))
    {
        return -1;
    }

    sf::Sprite spriteA; 
    spriteA.setTexture(textureA); 
    spriteA.setPosition(400, 300); 
    spriteA.setColor(sf::Color::Yellow);
    
    while (window.isOpen())
    {
        sf::Event eventA;
        while (window.pollEvent(eventA))
        {
            switch (eventA.type) 
            {
                case sf::Event::Closed: 
                    window.close();
                    break;
                default:
                    break;
            }
        }

        window.clear();
        window.draw(spriteA);
        window.display();
    }

    return EXIT_SUCCESS;
}