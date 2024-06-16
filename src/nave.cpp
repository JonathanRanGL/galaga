#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>

int main()
{ 
    ShowWindow(GetConsoleWindow(), SW_HIDE); // Oculta la ventana de la consola.
    // Se crea la ventana para poder visualizar los sprites de la nave.
    sf::RenderWindow window(sf::VideoMode(800, 600), "Nave", sf::Style::Default);
    window.setFramerateLimit(60); // Limita la cantidad de frames por segundo a 60.

    // Se carga la textura de la nave.
    sf::Texture textureN;
    if (!textureN.loadFromFile("./assets/images/nave.png"))
    {
        return -1;//En caso de que no se pueda cargar la textura, se cierra el programa.
    }
    sf::Sprite spriteN; // Se crea el sprite de la nave.
    spriteN.setTexture(textureN); // Se le asigna la textura a la nave.
    spriteN.setPosition(400, 300); // Se le asigna una posición inicial a la nave.
    spriteN.setColor(sf::Color::Red); // Se le asigna un color a la nave (esto para que de una señal de que fue impactada por un enemigo).
    
    while (window.isOpen())
    {
        sf::Event eventN;
        while (window.pollEvent(eventN))
        {
            switch (eventN.type) 
            {
                case sf::Event::Closed: // Mantiene la ventana abierta hasta que el usuario elija cerrarla.
                    window.close();
                    break;
                default:
                    break;
            }
        }

        window.clear();
        window.draw(spriteN);
        window.display();
    }

    return EXIT_SUCCESS;
}