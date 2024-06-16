#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>

int main()
{ 
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Jefe", sf::Style::Default);
    window.setFramerateLimit(60); 

    sf::Texture textureJ;
    if (!textureJ.loadFromFile("assets/Jefe.png"))
    {
        return -1;
    }

    sf::Sprite spriteJ; 
    spriteJ.setTexture(textureJ); 
    spriteJ.setPosition(400, 300); 
    spriteJ.setColor(sf::Color::Yellow);
    
    while (window.isOpen())
    {
        sf::Event eventM;
        while (window.pollEvent(eventM))
        {
            switch (eventM.type) 
            {
                case sf::Event::Closed: 
                    window.close();
                    break;
                default:
                    break;
            }
        }

        window.clear();
        window.draw(spriteJ);
        window.display();
    }

    return EXIT_SUCCESS;
}