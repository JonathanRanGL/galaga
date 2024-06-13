#include <SFML/Graphics.hpp>

int main()
{
    // Crear una ventana de SFML
    sf::RenderWindow window(sf::VideoMode(768, 1024), "SFML works!",sf::Style::Titlebar | sf::Style::Close);
    

    // Crear una forma circular de SFML
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Red);
    sf::Event event;

    while (window.isOpen())
    {
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::Escape){window.close();}
                    break;

            }
        }

        

        // Renderizar
        window.clear();

        // Dibujar la forma en la ventana
        window.draw(shape);

        // Mostrar la ventana
        window.display();
    }

    return 0;
}