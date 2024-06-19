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

    double speed;
    float shootCooldown;
    float shootCooldownLimit;
    int remainingLives;

    // Sonido
    sf::Sprite nave;
    sf::Texture texture;

    sf::SoundBuffer buffer;
    sf::Sound disparo;

    sf::SoundBuffer bufferHit;
    sf::Sound hit;

    sf::SoundBuffer bufferRespawn;
    sf::Sound respawn;

    std::vector<Proyectil *> proyectiles; // Vector que almacena los punteros hacia los proyectiles

public:
    // Funciones
    void innitTexture()
    {
        // Cargar la textura de la nave
        if (!this->texture.loadFromFile("./assets/images/nave/nave.png"))
        {
            std::cout << "ERROR::Nave::innitTexture::No se pudo cargar la textura de la nave" << std::endl;
        }
    }

    void innitSprite()
    {
        // Asignar la textura a la nave
        this->nave.setTexture(this->texture);

        // Escalar la sprite de la nave al tamaño deseado
        this->nave.scale(0.1, 0.1);
    }

    void innitSound()
    {
        // Cargar el sonido para cada disparo de la nave
        if (!this->buffer.loadFromFile("./assets/music/disparo.wav"))
        {
            std::cout << "ERROR::Nave::innitSound::No se pudo cargar el sonido de disparo" << std::endl;
        }
        disparo.setBuffer(buffer);

        // Cargar el sonido para cada colisión de la nave
        if (!this->bufferHit.loadFromFile("./assets/music/DestruccionNave.wav"))
        {
            std::cout << "ERROR::Nave::innitSound::No se pudo cargar el sonido de colisión" << std::endl;
        }
        hit.setBuffer(bufferHit);

        // Cargar el sonido para cada respawn de la nave
        if (!this->bufferRespawn.loadFromFile("./assets/music/Reaparecer.wav"))
        {
            std::cout << "ERROR::Nave::innitSound::No se pudo cargar el sonido de respawn" << std::endl;
        }
        respawn.setBuffer(bufferRespawn);
    }

    void innitVariables()
    {
        this->remainingLives = 3;
        this->speed = 2.f;
        this->shootCooldownLimit = 60.f;
        this->shootCooldown = this->shootCooldownLimit;
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
            this->proyectiles.push_back(new Proyectil(0.f, -1.f, -2.f + nave.getPosition().x + nave.getGlobalBounds().width / 2, nave.getPosition().y));
            this->disparo.play();
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

    // Accesores
    int getProyectilesSize()
    {
        /*
        Esta función permite obtener el tamaño del vector de proyectiles, su utilidad radica en
        que puede ser llamada desde fuera de la clase Nave.
        */
        return this->proyectiles.size();
    }

    const sf::FloatRect getProyectilesBounds(int i)
    {
        /*
        Esta función permite obtener los límites en las dimensiones (por así decirlo, el hitbox)
        de un proyectil una posición en especificada en el vector de proyectiles, su utilidad radica
        en que puede ser llamada por fuera de la clase Nave.
        */
        return this->proyectiles.at(i)->getBounds();
    }

    const sf::FloatRect getBounds() const
    {
        /*
        Esta función permite obtener los límites en las dimensiones (por así decirlo, el hitbox)
        de la nave, su utilidad radica en que puede ser llamada por fuera de la clase Nave.
        */
        return this->nave.getGlobalBounds();
    }

    void playDestroyedSound()
    {
        this->hit.play();
    }

    void playRespawnSound()
    {
        this->respawn.play();
    }

    // Setters

    void resetPosition()
    {
        this->nave.setPosition(300.f - ((this->nave.getGlobalBounds().width) / 2), 700.f);
    }

    int takeHit()
    {
        remainingLives--;
        return this->remainingLives;
    }

    void setDefaultTexture()
    {
        if (!this->texture.loadFromFile("./assets/images/nave/nave.png"))
        {
            std::cout << "ERROR::Nave::innitTexture::No se pudo cargar la textura de la nave" << std::endl;
        }

        this->nave.setTexture(this->texture);
        this->nave.scale(1, 1);
    }

    void setDestroyedTexture1()
    {
        if (!this->texture.loadFromFile("./assets/images/nave/naveDestruida1.png"))
        {
            std::cout << "ERROR::Nave::innitTexture::No se pudo cargar la textura de la nave" << std::endl;
        }

        this->nave.setTexture(this->texture);
        this->nave.scale(1, 1);
    }

    void setDestroyedTexture2()
    {
        if (!this->texture.loadFromFile("./assets/images/nave/naveDestruida2.png"))
        {
            std::cout << "ERROR::Nave::innitTexture::No se pudo cargar la textura de la nave" << std::endl;
        }

        this->nave.setTexture(this->texture);
        this->nave.scale(1, 1);
    }

    void setDestroyedTexture3()
    {
        if (!this->texture.loadFromFile("./assets/images/nave/naveDestruida3.png"))
        {
            std::cout << "ERROR::Nave::innitTexture::No se pudo cargar la textura de la nave" << std::endl;
        }

        this->nave.setTexture(this->texture);
        this->nave.scale(1, 1);
    }

    void setDestroyedTexture4()
    {
        if (!this->texture.loadFromFile("./assets/images/nave/naveDestruida4.png"))
        {
            std::cout << "ERROR::Nave::innitTexture::No se pudo cargar la textura de la nave" << std::endl;
        }

        this->nave.setTexture(this->texture);
        this->nave.scale(1, 1);
    }

    void setDestroyedTexture5()
    {
        if (!this->texture.loadFromFile("./assets/images/nave/nothing.png"))
        {
            std::cout << "ERROR::Nave::innitTexture::No se pudo cargar la textura de la nave" << std::endl;
        }

        this->nave.setTexture(this->texture);
        this->nave.scale(1, 1);
    }

    // Constructor y Destructor
    Nave(float posX = -1.f, float posY = -1.f)
    {
        this->innitTexture();
        this->innitSprite();
        this->innitSound();

        this->innitVariables();

        if (posX = !-1.f || posY != -1.f)
        {
            this->nave.setPosition(posX, posY);
        }
        else // Posición por defecto centrado automático en función del tamaño de la nave
        {
            this->nave.setPosition(300.f - ((this->nave.getGlobalBounds().width) / 2), 700.f);
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