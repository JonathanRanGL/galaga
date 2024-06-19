#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

class Proyectil
{
private:
    // Variables
    sf::RectangleShape proyectil;
    sf::Vector2f direction;

    float muzzleVelocity;

public:
    // Funciones

    void innitVariables()
    {
        this->muzzleVelocity = 7.f;
    }

    void innitProyectil()
    {
        this->proyectil.setSize(sf::Vector2f(4.f, 10.f));
        this->proyectil.setFillColor(sf::Color::White);
    }

    void update()
    {
        this->proyectil.move(this->direction * this->muzzleVelocity);
    }

    void render(sf::RenderTarget *target)
    {
        target->draw(this->proyectil);
    }

    // Getters

    const sf::FloatRect getBounds() const
    {
        return this->proyectil.getGlobalBounds();
    }

    //Setters

    void setColor(sf::Color color)
    {
        this->proyectil.setFillColor(color);
    }

    //Constructor y destructor

    Proyectil(float dirX, float dirY, float posX, float posY)
    {
        this->innitVariables();
        this->innitProyectil();

        this->proyectil.setPosition(posX, posY);
        this->direction.x = dirX;
        this->direction.y = dirY;
    }
    ~Proyectil() {}
};