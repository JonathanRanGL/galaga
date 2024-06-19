#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <iostream>
#include <sstream>

class Puntaje
{
private:
    
    sf::Font font;
    sf::Text pointsText;

    int points;

    void innitVariables()
    {
        this->points = 0;
    }

    void innitFont()
    {
        if (!this->font.loadFromFile("./assets/fonts/galaga.ttf"))
        {
            std::cout << "ERROR::Puntaje::innitFont::No se pudo cargar la fuente" << std::endl;
        }
    }

    void innitText()
    {
        this->pointsText.setFont(this->font);
        this->pointsText.setFillColor(sf::Color::White);
    }

public:
    
    //Setters
    void setPosition(float x, float y)
    {
        this->pointsText.setPosition(x, y);
    }

    void setTextColor(sf::Color color)
    {
        this->pointsText.setFillColor(color);
    }

    void setTextSize(int size)
    {
        this->pointsText.setCharacterSize(size);
    }

    void setText(std::stringstream ss)
    {
        this->pointsText.setString(ss.str());
    }
    

    void render(sf::RenderTarget *target)
    {
        target->draw(this->pointsText);
    }
    
    void setPuntaje(int p)
    {
        points = p;
    }

    //Getters
    int getPuntaje()
    {
        return points;
    }
    
    // Funciones
    void increasePoints(int enemyVlaue)
    {
        points += enemyVlaue;
    }

    Puntaje()
    {
        this->innitVariables();
        this->innitFont();
        this->innitText();
    }

    ~Puntaje() {}
};