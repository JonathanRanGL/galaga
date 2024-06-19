#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include <Enemigo.hpp>

class Jefe : public Enemigo
{
private:
    sf::Texture texture;

    float scaleX;
    float scaleY;

    int hitCount;

    sf::SoundBuffer buffer;
    sf::Sound damage;
    sf::Sound death;

    void innitVariables()
    {
        this->tipo = 1;
        this->hitCount = 0;
        this->scaleX = 0.018;
        this->scaleY = 0.018;
    }

public:
    void innitTexture()
    {
        if (!this->texture.loadFromFile("./assets/images/jefe/jefe1.png"))
        {
            std::cout << "ERROR::Jefe::innitTexture::No se pudo cargar la textura del jefe" << std::endl;
        }
    }

    void innitSprite()
    {
        this->enemigo.setTexture(this->texture);
        this->enemigo.scale(scaleX, scaleY);
    }

    void playDeathSound()
    {
        if (!this->buffer.loadFromFile("./assets/music/colisionJ.wav"))
        {
            std::cout << "ERROR::Mariposa::innitSound::No se pudo cargar el sonido de disparo" << std::endl;
        }
        death.setBuffer(buffer);

        death.play();
    }

    void playDamageSound()
    {
        if (!this->buffer.loadFromFile("./assets/music/danoJ.wav"))
        {
            std::cout << "ERROR::Mariposa::innitSound::No se pudo cargar el sonido de disparo" << std::endl;
        }
        damage.setBuffer(buffer);

        damage.play();
    }

    void takeHit()
    {
        this->hitCount++;
    }

    int getHitCount()
    {
        return this->hitCount;
    }

    Jefe(float posX = 0.f, float posY = 0.f)
    {
        this->innitVariables();
        this->innitTexture();
        this->innitSprite();
        this->setProjectilesColor(sf::Color::Red);

        this->enemigo.setPosition(posX, posY);
    }
    ~Jefe() {}
};