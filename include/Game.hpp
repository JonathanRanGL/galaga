#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <math.h>

#include <Nave.hpp>
#include <Proyectil.hpp>
#include <Enemigo.hpp>

class Game
{
private:
    // Variables

    bool endGame;

    float waveTimer;
    float waveTimerMax;

    float spawnTimer;
    float spawnTimerMax;

    float moveStep;

    float type;

    float xPosArray[8] = {100.f, 150.f, 200.f, 250.f, 300.f, 350.f, 400.f, 450.f};

    float yPosType1 = 100.f;
    float yposType2[2] = {150.f, 200.f};
    float yposType3[2] = {250.f, 300.f};

    float sortX;
    float sortY;
    bool readyToSort;
    bool trajectoryFinished;

    int n = 0;

    // Window

    sf::RenderWindow *window;
    sf::VideoMode videoMode;
    sf::Event event;

    // Objetos dentro del juego

    Nave* nave;
    std::vector<Enemigo *> enemigos;

    // Funciones privadas

    void initVariables()
    {
        this->window = nullptr;

        this->spawnTimerMax = 100.f;
        this->spawnTimer = this->spawnTimerMax;

        this->waveTimerMax = 100.f;
        this->waveTimer = this->waveTimerMax;

        this->moveStep = -1.f;
        this->type = 0.f;

        this->sortX = -1.f;
        this->sortY = -1.f;
        this->readyToSort = false;
        this->trajectoryFinished = false;
    }

    void initWindow()
    {
        this->videoMode.height = 800;
        this->videoMode.width = 600;

        this->window = new sf::RenderWindow(this->videoMode, "Galaga", sf::Style::Titlebar | sf::Style::Close);

        this->window->setFramerateLimit(165);
    }

    void initEntities()
    {
        // Inicializando enemigos
        // this->enemigo = new Enemigo(this->window->getSize().x / 2, 0.f);
        this->nave = new Nave();
    }

public:
    // Constructor y Destructor
    Game(/* args */)
    {
        this->initVariables();
        this->initWindow();
        this->initEntities();
    }

    ~Game()
    {
        delete this->window;

        delete this->nave;

        // Eliminar enemigos
        for (auto *i : this->enemigos)
        {
            delete i;
        }
    }

    // Evaluadores (retornan algo)

    const bool running() const
    {
        return this->window->isOpen();
    }

    // Funciones

    void pollEvents()
    {
        while (this->window->pollEvent(this->event)) // Revisa si en la ventana ocurre un evento
        {
            switch (this->event.type) // Determina la acción segun que evento suceda
            {
            case sf::Event::Closed: // Cerrar ventana si se presiona la "X" de la ventana
                this->window->close();
                break;

            case sf::Event::KeyPressed: // Cerrar ventana si se presiona ESC en el teclado
                if (this->event.key.code == sf::Keyboard::Escape)
                {
                    this->window->close();
                }
                break;
            }
        }
    }

    void sortEnemy(int i)
    {
        /*
        Esta función se encarga de ordenar a los enemigos en la pantalla, dependiendo de su tipo, se les asigna una posición
        en X y Y predefinidas según una matriz de posiciones, esto se ejecuta una vez que el enemigo haya terminado de recorrer
        la trayectoria mediante la que aparece en la pantalla.
        La posición que se le asigna en Y depende de su tipo, mientras que la posición en X es aleatoria para agregar un poco de
        variabilidad en la posición de los enemigos cada vez que se juegue una partida.
        */
        this->type = this->enemigos[i]->getType();
        if (this->type == 1.f)
        {
            if (this->sortX == -1.f && this->sortY == -1.f)
            {
                this->sortX = this->xPosArray[rand() % 7];
                this->sortY = this->yPosType1;
            }
            if (this->enemigos[i]->getXPos() < this->sortX)
            {
                this->enemigos[i]->moveRight();
            }
            else if (this->enemigos[i]->getXPos() > this->sortX)
            {
                this->enemigos[i]->moveLeft();
            }

            if (this->enemigos[i]->getYPos() > this->sortY)
            {
                this->enemigos[i]->moveUp();
            }
            if ((abs(this->sortX - this->enemigos[i]->getXPos())) <= 2.5 && (abs(this->sortY - this->enemigos[i]->getYPos())) < 2.5)
            {
                this->enemigos[i]->setToXY(this->sortX, this->sortY);
            }
        }
        else if (this->type == 2.f)
        {
            if (this->sortX == -1.f && this->sortY == -1.f)
            {
                this->sortX = this->xPosArray[rand() % 7];
                this->sortY = this->yposType2[rand() % 1];
            }
            if (this->enemigos[i]->getXPos() < this->sortX)
            {
                this->enemigos[i]->moveRight();
            }
            else if (this->enemigos[i]->getXPos() > this->sortX)
            {
                this->enemigos[i]->moveLeft();
            }

            if (this->enemigos[i]->getYPos() > this->sortY)
            {
                this->enemigos[i]->moveUp();
            }
            if ((abs(this->sortX - this->enemigos[i]->getXPos())) <= 2.5 && (abs(this->sortY - this->enemigos[i]->getYPos())) < 2.5)
            {
                this->enemigos[i]->setToXY(this->sortX, this->sortY);
            }
        }
        else if (this->type == 3.f)
        {
            if (this->sortX == -1.f && this->sortY == -1.f)
            {
                this->sortX = this->xPosArray[rand() % 7];
                this->sortY = this->yposType3[rand() % 1];
            }
            if (this->enemigos[i]->getXPos() < this->sortX)
            {
                this->enemigos[i]->moveRight();
            }
            else if (this->enemigos[i]->getXPos() > this->sortX)
            {
                this->enemigos[i]->moveLeft();
            }

            if (this->enemigos[i]->getYPos() > this->sortY)
            {
                this->enemigos[i]->moveUp();
            }
            if ((abs(this->sortX - this->enemigos[i]->getXPos())) <= 2.5 && (abs(this->sortY - this->enemigos[i]->getYPos())) < 2.5)
            {
                this->enemigos[i]->setToXY(this->sortX, this->sortY);
            }
        }

        if (this->sortX == this->enemigos[i]->getXPos() && this->sortY == this->enemigos[i]->getYPos())
        {
            this->sortX = -1.f;
            this->sortY = -1.f;
            this->readyToSort = false;
        }
    }

    bool trajectoryE1(int i) // Trayectoria 1 para enemigos.
    {
        // Establece la posición inicial del enemigo antes de aparecer en la pantalla
        if (this->moveStep == -1.f)
        {
            this->enemigos[i]->setToXY(310.f, -40.f);
            this->moveStep = 0.f;
        }

        // Primer movimiento
        if (this->enemigos[i]->getYPos() < 100.f && this->moveStep == 0.f)
        {
            this->enemigos[i]->moveDown();
        }
        else if (this->moveStep == 0.f)
        {
            this->moveStep = 1.f;
        }

        // Segundo movimiento
        if (this->enemigos[i]->getXPos() < 450.f && this->moveStep == 1.f)
        {
            this->enemigos[i]->moveDiagDownRight(1.5, 1.f);
        }
        else if (this->moveStep == 1.f)
        {
            this->moveStep = 2.f;
        }

        // Tercer movimiento
        if (this->enemigos[i]->getXPos() < 500.f && this->moveStep == 2.f)
        {
            this->enemigos[i]->moveDiagDownRight(1, 1.5);
        }
        else if (this->moveStep == 2.f)
        {
            this->moveStep = 3.f;
        }

        // Cuarto movimiento
        if (this->enemigos[i]->getYPos() < 380.f && this->moveStep == 3.f)
        {
            this->enemigos[i]->moveDown();
        }
        else if (this->moveStep == 3.f)
        {
            this->moveStep = 4.f;
        }

        // Quinto movimiento
        if (this->enemigos[i]->getXPos() > 390.f && this->moveStep == 4.f)
        {
            this->enemigos[i]->moveDiagDownLeft(1.3, 0.8);
        }
        else if (this->moveStep == 4.f)
        {
            this->moveStep = 5.f;
        }

        // Sexto movimiento
        if (this->enemigos[i]->getXPos() > 310.f && this->moveStep == 5.f)
        {
            this->enemigos[i]->moveDiagUpLeft(1.3, 0.8);
        }
        else if (this->moveStep == 5.f)
        {
            this->moveStep = 6.f;
        }

        // Séptimo movimiento
        if (this->enemigos[i]->getYPos() > 360.f && this->moveStep == 6.f)
        {
            this->enemigos[i]->moveUp();
        }
        else if (this->moveStep == 6.f)
        {
            this->moveStep = 7.f;
        }

        /*
        Si el enemigo llega a la posición final, se prepara para ser ordenado establece la variable readyToSort en true,
        se reinicia el contador de pasos de movimiento y se establece la variable trajectoryFinished en true indicando que
        la trayectoria ha finalizado.
        */
        if (this->moveStep == 7.f)
        {
            this->readyToSort = true;
            this->moveStep = -1.f;
            this->trajectoryFinished = true;
        }
        return readyToSort;
    }

    bool trajectoryE2(int i) // Trayectoria 2 para enemigos.
    {
        // Establece la posición inicial del enemigo antes de aparecer en la pantalla
        if (this->moveStep == -1.f)
        {
            this->enemigos[i]->setToXY(250.f, -40.f);
            this->moveStep = 0.f;
        }

        // Primer movimiento
        if (this->enemigos[i]->getYPos() < 100.f && this->moveStep == 0.f)
        {
            this->enemigos[i]->moveDown();
        }
        else if (this->moveStep == 0.f)
        {
            this->moveStep = 1.f;
        }

        // Segundo movimiento
        if (this->enemigos[i]->getXPos() > 150.f && this->moveStep == 1.f)
        {
            this->enemigos[i]->moveDiagDownLeft(1.5, 1.f);
        }
        else if (this->moveStep == 1.f)
        {
            this->moveStep = 2.f;
        }

        // Tercer movimiento
        if (this->enemigos[i]->getXPos() > 60.f && this->moveStep == 2.f)
        {
            this->enemigos[i]->moveDiagDownLeft(1, 1.5);
        }
        else if (this->moveStep == 2.f)
        {
            this->moveStep = 3.f;
        }

        // Cuarto movimiento
        if (this->enemigos[i]->getYPos() < 380.f && this->moveStep == 3.f)
        {
            this->enemigos[i]->moveDown();
        }
        else if (this->moveStep == 3.f)
        {
            this->moveStep = 4.f;
        }

        // Quinto movimiento
        if (this->enemigos[i]->getXPos() < 150.f && this->moveStep == 4.f)
        {
            this->enemigos[i]->moveDiagDownRight(1.3, 0.8);
        }
        else if (this->moveStep == 4.f)
        {
            this->moveStep = 5.f;
        }

        // Sexto movimiento
        if (this->enemigos[i]->getXPos() < 250.f && this->moveStep == 5.f)
        {
            this->enemigos[i]->moveDiagUpRight(1.3, 0.8);
        }
        else if (this->moveStep == 5.f)
        {
            this->moveStep = 6.f;
        }

        // Séptimo movimiento
        if (this->enemigos[i]->getYPos() > 360.f && this->moveStep == 6.f)
        {
            this->enemigos[i]->moveUp();
        }
        else if (this->moveStep == 6.f)
        {
            this->moveStep = 7.f;
        }

        /*
        Si el enemigo llega a la posición final, se prepara para ser ordenado establece la variable readyToSort en true,
        se reinicia el contador de pasos de movimiento y se establece la variable trajectoryFinished en true indicando que
        la trayectoria ha finalizado.
        */
        if (this->moveStep == 7.f)
        {
            this->readyToSort = true;
            this->moveStep = -1.f;
            this->trajectoryFinished = true;
        }
        return readyToSort;
    }

    void updateEnemigos()
    {
        // this->spawnTimer += 1.f;
        if (this->spawnTimer >= this->spawnTimerMax)
        {
            this->enemigos.push_back(new Enemigo(240.f, 0.f));
            this->spawnTimer = 0.f;
        }

        if (this->trajectoryFinished == false)
        {
            for (int i = 0; i < this->enemigos.size(); i++)
            {
                trajectoryE2(i);
            }
        }

        if (this->readyToSort == true)
        {
            for (int i = 0; i < this->enemigos.size(); i++)
            {
                sortEnemy(i);
            }
        }

        /*
        Esta sección de la función se encarga de detectar la colisión de los proyectiles de la nave con los enemigos,
        en caso de haber un impacto, es decir, sus hitboxes se intersectan, se elimina el enemigo y el proyectil de
        su correspondiente vector.
        */

        for (int i = 0; i < this->enemigos.size(); i++)
        {
            bool enemigoEliminado = false;
            for (size_t k = 0; k < nave->getProyectilesSize() && !enemigoEliminado; k++)
            {
                if (nave->getProyectilesBounds(k).intersects(this->enemigos[i]->getBounds()))
                {
                    this->enemigos.erase(this->enemigos.begin() + i);
                    nave->deleteProyectil(k);
                    enemigoEliminado = true;
                    // std::cout << "Enemigo eliminado" << std::endl;
                    // std::cout << this->enemigos.size() << std::endl;
                }
            }
        }
    }

    void update()
    {
        // Actualiza los eventos de la ventana
        this->pollEvents();

        // Actualiza todo lo relacionado con la nave, como su posición, proyectiles, etc.
        this->nave->update(this->window);

        // Actualiza todo lo relacionado con los enemigos, como su posición, movimiento, estado, etc.
        this->updateEnemigos();
    }

    void render()
    {
        /*
            Muestra en la ventana del juego todos los elementos
            que sean dibujados previamente según el siguiente orden:

            - Borra el frame anterior
            - Dibuja todos los elementos especificados
            - Muestra el frame
        */

        this->window->clear();

        // Dibujar elementos en ventana

        this->nave->render(this->window);

        for (auto *Enemigo : this->enemigos)
        {
            Enemigo->render(this->window);
        }

        // Una vez dibujados los elementos, se muestra la ventana (Equivale a 1 frame)

        this->window->display();
    }
};