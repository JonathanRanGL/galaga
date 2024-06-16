#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include <Proyectil.hpp>

class Nave
{
private:
    // Variables
    sf::RectangleShape nave;
    double speed;
    float shootCooldown;
    float shootCooldownLimit;

    std::vector<Proyectil *> proyectiles; // Vector que almacena los punteros hacia los proyectiles

public:
    // Funciones

    void innitVariables()
    {
        this->speed = 3.f;
        this->shootCooldownLimit = 60.f;
        this->shootCooldown = this->shootCooldownLimit;
    }

    void innitShape()
    {
        /*
        FUNCION TEMPORAL, SE CAMBIARÁ A UN SPRITE EN EL FUTURO
        */
        this->nave.setSize(sf::Vector2f(40.f, 40.f));
        this->nave.setFillColor(sf::Color::Red);
    }

    void updateInput()
    {
        /*
        Función que se encarga de constantemente revisar la tecla que se presione
        con relación a la nave, según la telca presionada, esta puede:
        - Moverse a la izquierda (LEFT)
        - Moverse a la derecha (RIGHT)
        - Disparar (SPACE)

        No confundir con pollEvents, ya que la mencionada actúa en función de los eventos
        ocurridos en la ventana completa y no sobre la nave.
        */

        // Movimiento de la nave con telcado
        // Izquierda (LEFT)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            this->nave.move(-this->speed, 0.f);
        }
        // Derecha (RIGHT)
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            this->nave.move(this->speed, 0.f);
        }

        // Disparo (SPACE)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && this->canShoot())
        {
            this->proyectiles.push_back(new Proyectil(0.f, -1.f, nave.getPosition().x + nave.getSize().x / 2, nave.getPosition().y));
        }
    }

    void updateBoundCollsion(const sf::RenderTarget *target)
    {
        /*
        Esta es una función que detecta la colisión de la nave con los bordes de la ventana,
        si la nave colisiona con alguno de los bordes, esta se detiene y no puede seguir avanzando.
        */

        sf::Vector2 posNave = this->nave.getPosition();

        // Izquierda
        if (this->nave.getGlobalBounds().left <= 0.f)
        {
            this->nave.setPosition(0.f, posNave.y);
        }
        // Derecha
        else if (this->nave.getGlobalBounds().left + this->nave.getGlobalBounds().width >= target->getSize().x)
        {
            this->nave.setPosition(target->getSize().x - this->nave.getGlobalBounds().width, posNave.y);
        }
    }

    void updateCooldown()
    {
        /*
        Esta función se encarga de actualizar el contador utilizado para el espacio de tiempo entre desparos de la nave.
        */
        if (this->shootCooldown < this->shootCooldownLimit)
        {
            this->shootCooldown += 1.f;
        }
    }

    const bool canShoot()
    {
        /*
        Esta función se encarga de verificar si el contador que establece el tiempo entre cada disparo de la nave ha llegado
        a su límite, si es así, reinicia el contador y retorna verdadero, de lo contrario, retorna falso.
        */
        if (this->shootCooldown >= this->shootCooldownLimit)
        {
            this->shootCooldown = 0.f;
            return true;
        }
        return false;
    }

    void updateProyectiles()
    {

        unsigned counter = 0;
        for (auto *proyectil : this->proyectiles)
        {
            proyectil->update();

            /*
            Esta sección de esta función se encarga de eliminar los proyectiles que salgan
            de la pantalla, para ello se revisa el borde inferior del proyectil, si este
            se encuentra fuera de la ventana, se elimina el proyectil en la posición del vector
            que le corresponde empezando desde el inicio del arreglo e incrementando con ayuda
            de un contador cada que se actualiza un proyectil.
            */
            if (proyectil->getBounds().top + proyectil->getBounds().height <= 0.f)
            {
                delete this->proyectiles.at(counter);
                this->proyectiles.erase(this->proyectiles.begin() + counter);

                /*
                Cuando borre un proyectil se reduce también el tamaño del vector
                por lo que se reduce el contador para que no se salte un proyectil.
                */
                --counter;

                //std::cout << this->proyectiles.size() << std::endl;
            }

            ++counter;
        }
    }

    void update(const sf::RenderTarget *target)
    {
        // Actualización de la entrada del usuario (teclado)
        this->updateInput();

        // Colisión con los bordes de la ventana
        this->updateBoundCollsion(target);

        // Actualización de los proyectiles
        this->updateProyectiles();

        // Actualización del cooldown de disparo
        this->updateCooldown();
    }

    void render(sf::RenderTarget *target)
    {
        /*
        En esta función se dibuja la nave en la ventana, se utiliza un puntero
        para poder dibujar la nave en la ventana que se le pase como argumento,
        para ello se usa un objetivo sobre el cual se dibujará la nave llamado
        RenderTarget.
        */

        for (auto *proyectil : this->proyectiles)
        {
            proyectil->render(target);
        }

        target->draw(this->nave);
    }

    // Constructor y Destructor
    Nave(float posX = -1.f, float posY = -1.f)
    {
        this->innitVariables();
        this->innitShape();

        if (posX = !-1.f || posY != -1.f)
        {
            this->nave.setPosition(posX, posY);
        }
        else // Posición por defecto centrado automático en función del tamaño de la nave
        {
            this->nave.setPosition(300.f - ((this->nave.getSize().x) / 2), 700.f);
        }
    }
    ~Nave()
    {

        // Eliminación de los proyectiles
        for (auto *i : this->proyectiles)
        {
            delete i;
        }
    }
};