#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include <Enemigo.hpp>

class Abeja : public Enemigo
{
private:
    sf::Texture texture;

    float scaleX;
    float scaleY;

    sf::SoundBuffer buffer;
    sf::Sound death;

    void innitVariables()
    {
        this->tipo = 3;
        scaleX = 0.014;
        scaleY = 0.014;
    }

public:
    
    void innitTexture()
    {
        if (!this->texture.loadFromFile("./assets/images/abeja/abeja1.png"))
        {
            std::cout << "ERROR::Nave::innitTexture::No se pudo cargar la textura de la nave" << std::endl;
        } 
    }

    void innitSprite()
    {
        this->enemigo.setTexture(this->texture);
        this->enemigo.scale(scaleX, scaleY);
    }

    void innitSound()
    {
        if (!this->buffer.loadFromFile("./assets/music/colisionA.wav"))
        {
            std::cout << "ERROR::Nave::innitSound::No se pudo cargar el sonido de disparo" << std::endl;
        }
        death.setBuffer(buffer);
    }

    void playDeathSound()
    {
        death.play();
    }

    Abeja(float posX = 0.f, float posY = 0.f)
    {
        this->innitVariables();
        this->innitTexture();
        this->innitSprite();
        this->innitSound();

        this->enemigo.setPosition(posX, posY);
    }
    ~Abeja()
    {
        

    }
};