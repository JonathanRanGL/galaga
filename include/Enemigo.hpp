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
    // Variables

protected:
    // Variables
    sf::RectangleShape enemigo;
    double speed;
    int tipo;

public:
    // Funciones
    void innitVariables()
    {
        this->speed = 2.5;
        this->tipo = rand() % 3 + 1; // Genera un tipo de enemigo aleatorio (1, 2 o 3)
    }

    void innitShape()
    {
        /*
        FUNCION TEMPORAL, SE CAMBIARÁ A UN SPRITE EN EL FUTURO
        */
        this->enemigo.setSize(sf::Vector2f(40.f, 40.f));

        switch (this->tipo)
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

    void setToXY(float posX, float posY)
    {
        this->enemigo.setPosition(posX, posY);
    }

    void moveUp()
    {
        this->enemigo.move(0.f, -this->speed);
    }

    void moveDown()
    {
        this->enemigo.move(0.f, this->speed);
    }

    void moveLeft()
    {
        this->enemigo.move(-this->speed, 0.f);
    }

    void moveRight()
    {
        this->enemigo.move(this->speed, 0.f);
    }

    void moveDiagDownRight(float factorX = 1.f, float factorY = 1.f)
    {
        this->enemigo.move(0.707 * this->speed * factorX, 0.707 * this->speed * factorY);
    }

    void moveDiagDownLeft(float factorX = 1.f, float factorY = 1.f)
    {
        this->enemigo.move(-0.707 * this->speed * factorX, 0.707 * this->speed * factorY);
    }

    void moveDiagUpRight(float factorX = 1.f, float factorY = 1.f)
    {
        this->enemigo.move(0.707 * this->speed * factorX, -0.707 * this->speed * factorY);
    }

    void moveDiagUpLeft(float factorX = 1.f, float factorY = 1.f)
    {
        this->enemigo.move(-0.707 * this->speed * factorX, -0.707 * this->speed * factorY);
    }

    void update()
    {
    }

    void render(sf::RenderTarget *target)
    {
        target->draw(this->enemigo);
    }

    // Accesores
    float getXPos()
    {
        return this->enemigo.getPosition().x;
    }

    float getYPos()
    {
        return this->enemigo.getPosition().y;
    }

    int getType()
    {
        return this->tipo;
    }

    // Constructor y Destructor
    Enemigo(float posX = 0.f, float posY = 0.f)
    {
        this->innitVariables();
        this->innitShape();

        this->enemigo.setPosition(posX, posY);
    }
    ~Enemigo() {}
};