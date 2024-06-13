#pragma once
#include <SFML/Graphics.hpp>

class Game
{
private:
    // Variables
    // Window

    sf::RenderWindow *window;
    sf::VideoMode videoMode;
    sf::Event event;

    //Objetos dentro del juego

    sf::RectangleShape nave;

    // Funciones privadas

    void initVariables()
    {
        this->window = nullptr;
    }

    void initWindow()
    {
        this->videoMode.height = 600;
        this->videoMode.width = 600;

        this->window = new sf::RenderWindow(this->videoMode, "Galaga", sf::Style::Titlebar | sf::Style::Close);

        //this->window->setFramerateLimit(165);
    }

    void initPlayer()
    {
        this->nave.setPosition(250.f, 100.f);
        
        this->nave.setSize(sf::Vector2f(50.f, 50.f));
        this->nave.setFillColor(sf::Color::Red);
    }

public:
    // Constructor y Destructor
    Game(/* args */)
    {
        this->initVariables();
        this->initWindow();
        this->initPlayer();
    }

    ~Game()
    {
        delete this->window;
    }

    // Evaluadores (retornan algo)
    
    const bool running() const
    {
        return this->window->isOpen();
    }

    // Funciones

    void pollEvents()
    {
        while (this->window->pollEvent(this->event)) // Revisa si en la ventana ocurre un evento
        {
            switch (this->event.type) // Determina la acción segun que evento suceda
            {
            case sf::Event::Closed: // Cerrar ventana si se presiona la "X" de la ventana
                this->window->close();
                break;

            case sf::Event::KeyPressed: // Cerrar ventana si se presiona ESC en el teclado
                if (this->event.key.code == sf::Keyboard::Escape)
                {
                    this->window->close();
                }
                break;
            }
        }
    }
    
    void update()
    {
        this->pollEvents();
    }
    
    void render() 
    {
        /*
            Muestra en la ventana del juego todos los elementos
            que sean dibujados previamente según el siguiente orden:

            - Borra el frame anterior
            - Dibuja todos los elementos especificados
            - Muestra el frame
        */
        
        this->window->clear();

        //Dibujar elementos en ventana
        this->window->draw(this->nave);

        this->window->display();
    }

};