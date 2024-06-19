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
    sf::Sprite enemigo;
    double speed;
    int tipo;
    int movDirection;

    std::vector<Proyectil *> proyectiles;

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
        /*
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
         */
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
        this->movDirection = 0;
    }

    void moveUp()
    {
        this->enemigo.move(0.f, -this->speed);
        this->movDirection = 8;
    }

    void moveDown()
    {
        this->enemigo.move(0.f, this->speed);
        this->movDirection = 2;
    }

    void moveLeft()
    {
        this->enemigo.move(-this->speed, 0.f);
        this->movDirection = 4;
    }

    void moveRight()
    {
        this->enemigo.move(this->speed, 0.f);
        this->movDirection = 6;
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
        this->movDirection = 3;
    }

    void moveDiagDownLeft(float factorX = 1.f, float factorY = 1.f)
    {
        this->enemigo.move(-0.707 * this->speed * factorX, 0.707 * this->speed * factorY);
        this->movDirection = 1;
    }

    void moveDiagUpRight(float factorX = 1.f, float factorY = 1.f)
    {
        this->enemigo.move(0.707 * this->speed * factorX, -0.707 * this->speed * factorY);
        this->movDirection = 9;
    }

    void moveDiagUpLeft(float factorX = 1.f, float factorY = 1.f)
    {
        this->enemigo.move(-0.707 * this->speed * factorX, -0.707 * this->speed * factorY);
        this->movDirection = 7;
    }

    // ------------------------------------------------------------------------------------------------------------------------------------

    void shoot()
    {
        this->proyectiles.push_back(new Proyectil(0.f, 1.f, (this->enemigo.getPosition().x + this->enemigo.getGlobalBounds().width / 2),
                                                  this->enemigo.getPosition().y + this->enemigo.getGlobalBounds().height));
    }

    void updateProyectiles()
    {
        unsigned counter = 0;
        for (auto *proyectil : this->proyectiles)
        {
            proyectil->update();

            /*
            Esta sección de esta función se encarga de eliminar los proyectiles que salgan
            de la pantalla (del lado inferior), para ello se revisa el borde inferior del 
            proyectil, si este se encuentra fuera de la ventana, se elimina el proyectil en la 
            posición del vector que le corresponde empezando desde el inicio del arreglo e 
            incrementando con ayuda de un contador cada que se actualiza un proyectil.
            */
            if (proyectil->getBounds().top <= 0.f)
            {
                delete this->proyectiles.at(counter);
                this->proyectiles.erase(this->proyectiles.begin() + counter);

                /*
                Cuando borre un proyectil se reduce también el tamaño del vector
                por lo que se reduce el contador para que no se salte un proyectil.
                */
                --counter;

                // std::cout << this->proyectiles.size() << std::endl;
            }

            ++counter;
        }
    }

    void deleteProyectil(int index)
    {
        /*
        Esta función permite eliminar un proyectil del vector de proyectiles en una posición en específico,
        la importancia de la función radica en que puede ser llamada desde fuera de la clase Nave.
        */
        delete this->proyectiles.at(index);
        this->proyectiles.erase(this->proyectiles.begin() + index);
    }

    int getProyectilesSize()
    {
        return this->proyectiles.size();
    }

    const sf::FloatRect getProyectilesBounds(int i)
    {
        return this->proyectiles.at(i)->getBounds();
    }

    //------------------------------------------------------------------------------------------------------------------------------------
    void update()
    {  
        // Actualización de los proyectiles lanzados por el enemigo
        this->updateProyectiles();
    }

    void render(sf::RenderTarget *target)
    {
        for (auto *proyectil : this->proyectiles)
        {
            proyectil->render(target);
        }
        
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