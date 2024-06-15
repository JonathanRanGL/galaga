#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <Proyectil.hpp>
#include <vector>

class Enemigo
{
private:
    //Variables

protected:
    //Variables
    sf::RectangleShape enemigo;
    double speed;
    int tipo;
    float moveTimer;

    

public:
    
    //Funciones
    void innitVariables()
    {
        this->speed = 1.f;
        this->tipo = rand() % 3 + 1; //Genera un tipo de enemigo aleatorio (1, 2 o 3)
        this->moveTimer = 0.f;

    }

    void innitShape()
    {
        /*
        FUNCION TEMPORAL, SE CAMBIARÁ A UN SPRITE EN EL FUTURO
        */
        this->enemigo.setSize(sf::Vector2f(40.f, 40.f));
        
        switch(this->tipo)
        {
            case 1:
                this->enemigo.setFillColor(sf::Color::Magenta); 
                break;
            case 2:
                this->enemigo.setFillColor(sf::Color::Blue);
                break;
            case 3:
                this->enemigo.setFillColor(sf::Color::Yellow);
                break;
        }
        
    }

    void trajectory1()
    {
      
    }

    void update()
    {
        this->enemigo.move(0.f, this->speed);
    }

    void render(sf::RenderTarget *target)
    {
        target->draw(this->enemigo);
    }

    //Constructor y Destructor
    Enemigo(float posX = 0.f, float posY = 0.f)
    {
        this->innitVariables();
        this->innitShape();

        this->enemigo.setPosition(posX, posY);
    }
    ~Enemigo() {}
};