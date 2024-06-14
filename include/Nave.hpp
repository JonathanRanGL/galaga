#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

class Nave
{
private:
    // Variables
    sf::RectangleShape nave;
    double speed;

public:
    
    // Funciones

    void innitVariables()
    {
        this->speed = 3.f;
    }

    void innitShape()
    {
        /*
        FUNCION TEMPORAL, SE CAMBIARÁ A UN SPRITE EN EL FUTURO
        */
        this->nave.setSize(sf::Vector2f(40.f, 40.f));
        this->nave.setFillColor(sf::Color::Red);
    }

    void updateInput()
    {
        /*
        Función que se encarga de constantemente revisar la tecla que se presione
        con relación a la nave, según la telca presionada, esta puede:
        - Moverse a la izquierda (LEFT)
        - Moverse a la derecha (RIGHT)
        - Disparar (SPACE)

        No confundir con pollEvents, ya que la mencionada actúa en función de los eventos
        ocurridos en la ventana completa y no sobre la nave.
        */

        // Movimiento de la nave con telcado
        // Izquierda (LEFT)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            this->nave.move(-this->speed, 0.f);
        }
        // Derecha (RIGHT)
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            this->nave.move(this->speed, 0.f);
        }
    }

    void updateBoundCollsion(const sf::RenderTarget *target)
    {
        
        
        sf::Vector2 posNave = this->nave.getPosition();

        //Izquierda
        if(this->nave.getGlobalBounds().left <= 0.f)
        {
            this->nave.setPosition(0.f, posNave.y);
        }
        //Derecha
        else if(this->nave.getGlobalBounds().left + this->nave.getGlobalBounds().width >= target->getSize().x)
        {
            this->nave.setPosition(target->getSize().x - this->nave.getGlobalBounds().width, posNave.y);
        }

            
            
        
    }

    void update(const sf::RenderTarget *target)
    {
        // Actualización de la entrada del usuario (teclado)
        this->updateInput();

        // Colisión con los bordes de la ventana
        this->updateBoundCollsion(target);
    }

    void render(sf::RenderTarget *target)
    {
        /*
        En esta función se dibuja la nave en la ventana, se utiliza un puntero
        para poder dibujar la nave en la ventana que se le pase como argumento,
        para ello se usa un objetivo sobre el cual se dibujará la nave llamado
        RenderTarget.
        */
        target->draw(this->nave);
    }

    // Constructor y Destructor
    Nave(float posX = -1.f, float posY = -1.f)
    {
        this->innitVariables();
        this->innitShape();
        
        if(posX =! -1.f || posY != -1.f)
        {
            this->nave.setPosition(posX, posY);
        }
        else //Posición por defecto centrado automático en función del tamaño de la nave
        {
            this->nave.setPosition(300.f-((this->nave.getSize().x)/2), 700.f);
        }
        
    }
    ~Nave() {}
};