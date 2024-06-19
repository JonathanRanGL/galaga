#pragma once 
#include <SFML/Graphics.hpp>
#include <iostream>

class Puntaje
{
    private:
        sf::Font font;
        sf::Text puntajeText;
        int puntaje;

    public:
        void aggPuntuacion (int puntos)
        {
            puntaje += puntos;
            updateText();
        }

        void updateText()
        {
        scoreText.setString("Puntaje: " + std::to_string(puntaje));
        }

        void draw(sf::RenderWindow &window)
        {
        window.draw(puntajeText);
        }

    Puntaje()
    {
        if (!font.loadFromFile("./assets/fonts/galaga.tff"))
        {
            std::cout << "ERROR::Puntaje::innitTexture::No se pudo cargar la fuente" << std::endl;
        }

        puntaje = 0;
        puntaje.setFont(font);
        puntaje.setCharacterSize(22);
        puntaje.setFillColor(sf::Color::White);
        puntaje.setPosition(10, 10);

        updateText();
    }

     ~Puntaje() {}
};