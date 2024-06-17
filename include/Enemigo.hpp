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
        this->speed = 4.5;
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

    // ------------------------------------------------------------------------------------------------------------------------------------

    /*
    Las siguientes funciones pareciera que no tienen mucho sentido, ya que replican la funcionalidad de funciones originales de
    la librería SFML, sin embargo, su utilidad radica en que permiten llamar a estas funciones por fuera de la clase enemigo,
    esto permite no solo agilizar la actualización de la posición de un enemigo cualquira, si no que, obviamente, estas pueden
    ser llamadas por fuera de la clase enemigo, la que es su verdadera utilidad.
    */

    void setToXY(float posX, float posY)
    {
        /*
        Esta función permite establecer una posición en X y Y para el enemigo por fuera de la clase enemigo.
        */
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

    /*
    A las funciones de movimiento diagonal se les agregó dos productos a la velocidad, el primero siendo una constante de valor 0.707,
    la razón de esto es que la velocidad diagonal es mayor a la velocidad horizontal o vertical, esto se puede demostrar por medio de
    geometría, por lo que para mantener la velocidad diagnonal en un valor cercano a 1 se multiplica por 0.707 (que es el euivalente
    a el inverso de la raíz de 2).
    El segundo producto es un factor de altera el valor de la velocidad, esto permite que el vector de velocidad para X o para Y sea
    diferente, permitiendo que el movimient diagnonal del enemigo pueda tomar diferentes ángulos no únicamente 45°, es decir, que si
    se el factor de X es 2 y el factor de Y es 1, el enemigo se moverá 2 veces más en X que en Y, lo que cambia el ángulo de movimiento.
    */

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

    // ------------------------------------------------------------------------------------------------------------------------------------

    void update()
    {
    }

    void render(sf::RenderTarget *target)
    {
        target->draw(this->enemigo);
    }

    // Accesores
    float getSpeed()
    {
        /*
        Esta función permite obtener la velocidad del enemigo por fuera de la clase nave.
        */
        return this->speed;
    }
    
    float getXPos()
    {
        /*
        Esta función permite obtener la posición en X del enemigo por fuera de la clase nave.
        */
        return this->enemigo.getPosition().x;
    }

    float getYPos()
    {
        /*
        Esta función permite obtener la posición en Y del enemigo por fuera de la clase nave.
        */
        return this->enemigo.getPosition().y;
    }

    int getType()
    {
        /*
        Esta función permite obtener el tipo de enemigo por fuera de la clase nave.
        */
        return this->tipo;
    }

    const sf::FloatRect getBounds() const
    {
        /*
        Esta función permite obtener los límites en las dimensiones (por así decirlo, el hitbox)
        del enemigo, su utilidad radica en que puede ser llamada por fuera de la clase Enemigo.
        */
        return this->enemigo.getGlobalBounds();
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