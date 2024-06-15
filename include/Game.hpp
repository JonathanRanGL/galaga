#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include <Nave.hpp>
#include <Proyectil.hpp>
#include <Enemigo.hpp>

class Game
{
private:
    // Variables

    bool endGame;
    
    float waveTimer;
    float waveTimerMax;

    float spawnTimer;
    float spawnTimerMax;

    // Window

    sf::RenderWindow *window;
    sf::VideoMode videoMode;
    sf::Event event;

    // Objetos dentro del juego

    Nave nave;
    std::vector<Enemigo *> enemigos;

    // Funciones privadas

    void initVariables()
    {
        this->window = nullptr;

        this->spawnTimerMax = 50.f;
        this->spawnTimer = this->spawnTimerMax;

        this->waveTimerMax = 100.f;
        this->waveTimer = this->waveTimerMax;
    }

    void initWindow()
    {
        this->videoMode.height = 800;
        this->videoMode.width = 600;

        this->window = new sf::RenderWindow(this->videoMode, "Galaga", sf::Style::Titlebar | sf::Style::Close);
     
        this->window->setFramerateLimit(165);
    }

    void initEntities()
    {
        //Inicializando enemigos
        //this->enemigo = new Enemigo(this->window->getSize().x / 2, 0.f);
    }

public:
    // Constructor y Destructor
    Game(/* args */)
    {
        this->initVariables();
        this->initWindow();
        this->initEntities();
    }

    ~Game()
    {
        delete this->window;

        // Eliminar enemigos
        for(auto *i : this->enemigos)
        {
            delete i;
        }
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

    void updateEnemigos()
    {
        //this->spawnTimer += 1.f;
        if (this->spawnTimer >= this->spawnTimerMax)
        {
            this->enemigos.push_back(new Enemigo(320.f, 0.f));
            this->spawnTimer = 0.f;
        }
        
        
        for(int i = 0 ; i < this->enemigos.size(); i++)
        {
            this->enemigos[i]->update();
        }
        
    }

    void update()
    {
        //Actualiza los eventos de la ventana
        this->pollEvents();

        //Actualiza todo lo relacionado con la nave, como su posición, proyectiles, etc.
        this->nave.update(this->window);

        //Actualiza todo lo relacionado con los enemigos, como su posición, movimiento, estado, etc.
        this->updateEnemigos();
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

        // Dibujar elementos en ventana

        this->nave.render(this->window);

        for(auto *Enemigo : this->enemigos)
        {
            Enemigo->render(this->window);
        }

        // Una vez dibujados los elementos, se muestra la ventana (Equivale a 1 frame)

        this->window->display();
    }
};