#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>

int main()
{ 
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Mariposa", sf::Style::Default);
    window.setFramerateLimit(60); 

    sf::Texture textureM;
    if (!textureM.loadFromFile("assets/Mariposa.png"))
    {
        return -1;
    }

    sf::Sprite spriteM; 
    spriteM.setTexture(textureM); 
    spriteM.setPosition(400, 300); 
    spriteM.setColor(sf::Color::Yellow);
    
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
        window.draw(spriteM);
        window.display();
    }

    return EXIT_SUCCESS;
}