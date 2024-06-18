#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <iostream>

#include <Enemigo.hpp>

class Abeja : public Enemigo
{
private:
    
    sf::Sprite enemigo;
    sf::Texture texture0;
    sf::Texture texture1;
    sf::Texture texture2;
    sf::Texture texture3;
    sf::Texture texture4;
    sf::Texture texture6;
    sf::Texture texture7;
    sf::Texture texture8;
    sf::Texture texture9;

    sf::RectangleShape test;


    sf::SoundBuffer buffer;
    sf::Sound muerte;

    float scaleX;
    float scaleY;

public:


    void innitVariablesA()
    {
        this->tipo = 3; // Se le asigna el tipo 3, que corresponde a la abeja

        this->scaleX = 0.02;
        this->scaleY = 0.02;
    }

    void innitShape()
    {
        this->test.setSize(sf::Vector2f(40.f, 40.f));
        this->test.setFillColor(sf::Color::Yellow);
    }

    void innitTexture()
    {
        // Cargar la texturas de la abeja

        // Textura de la abeja cuando no se está moviendo
        if (!this->texture0.loadFromFile("./assets/images/nave.png"))
        {
            std::cout << "ERROR::Abeja::innitTexture::No se pudo cargar la textura de la abeja" << std::endl;
        }
        /*
        // Textura de la abeja cuando se está moviendo hacia arriba
        if (!this->texture8.loadFromFile("./assets/images/abeja/abeja1.png"))
        {
            std::cout << "ERROR::Abeja::innitTexture::No se pudo cargar la textura de la abeja" << std::endl;
        }

        // Textura de la abeja cuando se está moviendo hacia abajo
        if (!this->texture2.loadFromFile("./assets/images/abeja/abeja1.png"))
        {
            std::cout << "ERROR::Abeja::innitTexture::No se pudo cargar la textura de la abeja" << std::endl;
        }

        // Textura de la abeja cuando se está moviendo hacia la derecha
        if (!this->texture6.loadFromFile("./assets/images/abeja/abeja6.png"))
        {
            std::cout << "ERROR::Abeja::innitTexture::No se pudo cargar la textura de la abeja" << std::endl;
        }

        // Textura de la abeja cuando se está moviendo hacia la izquierda
        if (!this->texture4.loadFromFile("./assets/images/abeja/abeja6.png"))
        {
            std::cout << "ERROR::Abeja::innitTexture::No se pudo cargar la textura de la abeja" << std::endl;
        }

        // Textura de la abeja cuando se está moviendo hacia abajo y a la derecha
        if (!this->texture3.loadFromFile("./assets/images/abeja/abeja4.png"))
        {
            std::cout << "ERROR::Abeja::innitTexture::No se pudo cargar la textura de la abeja" << std::endl;
        }

        // Textura de la abeja cuando se está moviendo hacia abajo y a la izquierda
        if (!this->texture1.loadFromFile("./assets/images/abeja/abeja4.png"))
        {
            std::cout << "ERROR::Abeja::innitTexture::No se pudo cargar la textura de la abeja" << std::endl;
        }

        // Textura de la abeja cuando se está moviendo hacia arriba y a la derecha
        if (!this->texture9.loadFromFile("./assets/images/abeja/abeja4.png"))
        {
            std::cout << "ERROR::Abeja::innitTexture::No se pudo cargar la textura de la abeja" << std::endl;
        }

        // Textura de la abeja cuando se está moviendo hacia arriba y a la izquierda
        if (!this->texture7.loadFromFile("./assets/images/abeja/abeja4.png"))
        {
            std::cout << "ERROR::Abeja::innitTexture::No se pudo cargar la textura de la abeja" << std::endl;
        }
        */
    }

    void innitSprite()
    {
        // Asignar la textura a la abjea
        this->enemigo.setTexture(this->texture0);

        // Escalar la sprite de la abeja al tamaño deseado
        this->enemigo.scale(scaleX, scaleY);
    }

    void innitSound()
    {
        // Cargar el sonido la muerte de la abeja
        if (!this->buffer.loadFromFile("./assets/music/colisionA.wav"))
        {
            std::cout << "ERROR::Abeja::innitSound::No se pudo cargar el sonido de la muerte de la abeja" << std::endl;
        }
        muerte.setBuffer(buffer);
    }

    void setCurrentSprite()
    {
        
        this->enemigo.setTexture(this->texture0);
        this->enemigo.scale(scaleX, scaleY);
        
        /*
        switch (this->movementDir)
        {
            case 0: //La abeja no se está moviendo
            {
                
                this->enemigo.setTexture(this->texture0);
                this->enemigo.scale(scaleX, scaleY);
                break;
            }

            case 8: //La abeja se está moviendo hacia arriba
            {
                this->enemigo.setTexture(this->texture8);
                this->enemigo.scale(scaleX, scaleY);
                break;
            }

            case 2: //La abeja se está moviendo hacia abajo
            {
                
                this->enemigo.setTexture(this->texture2);
                this->enemigo.scale(scaleX, -scaleY);
                break;
            }

            case 6: //La abeja se está moviendo hacia la derecha
            {
                this->enemigo.setTexture(this->texture6);
                this->enemigo.scale(-scaleX, scaleY);
                break;
            }

            case 4: //La abeja se está moviendo hacia la izquierda
            {
                this->enemigo.setTexture(this->texture4);
                this->enemigo.scale(scaleX, scaleY);
                break;
            }

            case 3: //La abeja se está moviendo hacia abajo y a la derecha
            {
                this->enemigo.setTexture(this->texture3);
                this->enemigo.scale(scaleX, -scaleY);
                break;
            }

            case 1: //La abeja se está moviendo hacia abajo y a la izquierda
            {
                this->enemigo.setTexture(this->texture1);
                this->enemigo.scale(scaleX, -scaleY);
                break;
            }

            case 9: //La abeja se está moviendo hacia arriba y a la derecha
            {
                this->enemigo.setTexture(this->texture9);
                this->enemigo.scale(-scaleX, scaleY);
                break;
            }

            case 7: //La abeja se está moviendo hacia arriba y a la izquierda
            {
                
                this->enemigo.setTexture(this->texture7);
                this->enemigo.scale(scaleX, scaleY);
                break;
            }
        }
        */
    }

    // Contructor y destructor
    Abeja(float posX = 0.f, float posY = 0.f)
    {
        this->innitVariablesA();
        this->innitTexture();
        this->innitSprite();
        this->innitSound();

        this->muerte.play();

        

        if (!this->texture0.loadFromFile("./assets/images/nave.png"))
        {
            std::cout << "ERROR::Abeja::innitTexture::No se pudo cargar la textura de la abeja" << std::endl;
        }
        this->enemigo.setTexture(this->texture0);
        this->enemigo.scale(scaleX, scaleY);

        this->enemigo.setPosition(posX, posY);
    }
    ~Abeja() {}
};