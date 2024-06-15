#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <Nave.hpp>
#include <Proyectil.hpp>

class Game
{
private:
    // Variables

    bool endGame;
    

    // Window

    sf::RenderWindow *window;
    sf::VideoMode videoMode;
    sf::Event event;

    //Objetos dentro del juego

    Nave nave;

    // Funciones privadas

    void initVariables()
    {
        this->window = nullptr;
    }

    void initWindow()
    {
        this->videoMode.height = 800;
        this->videoMode.width = 600;
    
        this->window = new sf::RenderWindow(this->videoMode, "Galaga", sf::Style::Titlebar | sf::Style::Close);
        this->window->setFramerateLimit(165);
    }

public:
    
    // Constructor y Destructor
    Game(/* args */)
    {
        this->initVariables();
        this->initWindow();
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

        this->nave.update(this->window);

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
        
        this->nave.render(this->window);

        

        //Una vez dibujados los elementos, se muestra la ventana (Equivale a 1 frame)

        this->window->display();
    }

};