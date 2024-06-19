#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <math.h>
#include <cmath>
#include <vector>
#include <variant>
#include <thread>
#include <chrono>

#include <Nave.hpp>
#include <Proyectil.hpp>
#include <Enemigo.hpp>
#include <Abeja.hpp>
#include <Mariposa.hpp>
#include <Jefe.hpp>
#include <Puntaje.hpp>

class Game
{
private:
    // Variables

    bool endGame;

    bool firstEnemy;

    float moveStep;
    bool isSorted;

    float type;

    float xPosArray[8] = {100.f, 150.f, 200.f, 250.f, 300.f, 350.f, 400.f, 450.f};

    float yPosType1 = 100.f;
    float yposType2[2] = {150.f, 200.f};
    float yposType3[2] = {250.f, 300.f};

    bool slotStateType1[8] = {false, false, false, false, false, false, false, false};

    bool slotStateType2R1[8] = {false, false, false, false, false, false, false, false};
    bool slotStateType2R2[8] = {false, false, false, false, false, false, false, false};

    bool slotStateType3R1[8] = {false, false, false, false, false, false, false, false};
    bool slotStateType3R2[8] = {false, false, false, false, false, false, false, false};

    bool type1Full;
    bool type2Full;
    bool type3Full;

    bool slotReseted = false;

    float sortX;
    float sortY;

    int randAX;
    int randAY;
    bool readyToSort;
    int enemySpawnReset;
    int trajectoryPicked;

    int j;

    int yDelete;

    int typeToGenerate;
    int timerToSpawn;
    int timerToSpawnLimit;

    int randEnemy;
    int enemyShootingInterval;
    int enemyShootingIntervalLimit;

    int type1Value;
    int type2Value;
    int type3Value;

    bool gameStarted;

    //Background
    sf::Texture backgroundTexture;
    sf::Sprite background;

    //Puntaje

    Puntaje *puntaje;
    
    // Window

    sf::RenderWindow *window;
    sf::VideoMode videoMode;
    sf::Event event;

    //Audio
    sf::SoundBuffer introBuffer;
    sf::Sound introTone;

    sf::SoundBuffer stageStartBuffer;
    sf::Sound stageStartTone;

    sf::SoundBuffer gameOverBuffer;
    sf::Sound gameOverTone;

    int toneTimer;
    int toneTimerLimit;
    
    // Objetos dentro del juego

    Nave *nave;

    using EnemigosActivos = std::variant<Abeja *, Mariposa *, Jefe *>;
    std::vector<EnemigosActivos> enemigosActivos;

    /*
    Se crea un vector de enemigos encargado de almacenar los datos de todos los enemigos activos.
    Si el enemigo muere, se elimina del vector liberando la memporia que ocupaba, al igual que se
    hace con el proyectil de la nave que lo impactó y todos aquellos proyectiles que salen de la
    ventana.
    */

    /*
    Este vector se encarga de almacenar un 1 o un 0 que indicará si el enemigo ha sido ordenado o no,
    para cada enemigo activo en la pantalla, hay un valor dentro de este vector
    */
    std::vector<int> enemySorted;

    // Funciones privadas

    void initVariables()
    {
        this->endGame = false;

        this->window = nullptr;

        this->firstEnemy = true;

        this->isSorted = false;

        this->moveStep = -1.f;
        this->type = 0.f;

        this->sortX = -1.f;
        this->sortY = -1.f;
        this->randAX = 0;
        this->randAY = 0;
        this->readyToSort = false;

        this->yDelete = 0;

        this->type1Full = false;
        this->type2Full = false;
        this->type3Full = false;

        this->trajectoryPicked = rand() % 2;

        this->typeToGenerate = 0;
        this->timerToSpawn = 0;
        this->timerToSpawnLimit = 100;

        this->randEnemy = 0;
        this->enemyShootingInterval = 0;
        this->enemyShootingIntervalLimit = 100;

        this->type1Value = 400;
        this->type2Value = 200;
        this->type3Value = 100;

        this->gameStarted = false;
        this->toneTimer = 0;
        this->toneTimerLimit = 4000;
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
        this->nave = new Nave();

        this->puntaje = new Puntaje();
    }

    void innitGameSound()
    {
        if (!this->introBuffer.loadFromFile("./assets/music/intro.wav"))
        {
            std::cout << "ERROR::Game::innitGameSound::No se pudo cargar el sonido de inicio" << std::endl;
        }
        introTone.setBuffer(introBuffer);

        if (!this->stageStartBuffer.loadFromFile("./assets/music/inicioetapaD.wav"))
        {
            std::cout << "ERROR::Game::innitGameSound::No se pudo cargar el sonido de inicio de nivel" << std::endl;
        }
        stageStartTone.setBuffer(stageStartBuffer);

        if (!this->gameOverBuffer.loadFromFile("./assets/music/finetapaD.wav"))
        {
            std::cout << "ERROR::Game::innitGameSound::No se pudo cargar el sonido de fin de juego" << std::endl;
        }
        gameOverTone.setBuffer(gameOverBuffer);
    }

public:
    // Constructor y Destructor
    Game(/* args */)
    {
        this->innitGameBackground();
        this->initVariables();
        this->initWindow();
        this->initEntities();
        this->innitGameSound();
    }

    ~Game()
    {
        delete this->window;

        delete this->nave;

        // Eliminar enemigos
        this->enemigosActivos.clear();
    }

    // Evaluadores (retornan algo)

    const bool running() const
    {
        return this->window->isOpen();
    }

    const bool getEndGame() const
    {
        return this->endGame;
    }

    // Funciones

    void innitGameBackground()
    {
        if (!this->backgroundTexture.loadFromFile("./assets/images/background/background.png"))
        {
            std::cout << "ERROR::Game::innitGameBackground::No se pudo cargar la textura del fondo" << std::endl;
        }
        this->background.setTexture(this->backgroundTexture);
    }

    void renderGameBackground()
    {
        this->window->draw(this->background);
    }

    void printPoints()
    {
        this->puntaje->setTextSize(20);
        this->puntaje->setTextColor(sf::Color::White);
        this->puntaje->setPosition(10.f, 10.f);
        this->puntaje->setText(std::stringstream() << this->puntaje->getPuntaje());
    }

    void loadStartScreen()
    {
        this->window->clear();
        
        this->renderGameBackground();

        this->puntaje->setTextSize(30);
        this->puntaje->setTextColor(sf::Color::Cyan);
        this->puntaje->setPosition(210.f, 100.f);
        this->puntaje->setText(std::stringstream() << "GALAGA");
        this->puntaje->render(this->window);

        this->puntaje->setTextSize(14);
        this->puntaje->setTextColor(sf::Color::Red);
        this->puntaje->setPosition(160.f, 380.f);
        this->puntaje->setText(std::stringstream() << "Press ENTER to start");
        this->puntaje->render(this->window);

        this->puntaje->setTextSize(10);
        this->puntaje->setTextColor(sf::Color::White);
        this->puntaje->setPosition(220.f, 780.f);
        this->puntaje->setText(std::stringstream() << "23110179 - 23110115");
        this->puntaje->render(this->window);

        this->pollEvents();

        if(this->toneTimer == 0)
        {
            this->introTone.play();
            this->toneTimer = this->toneTimerLimit;
        }
        else
        {
            this->toneTimer--;
        }

        this->window->display();
    
    }

    void stageStartScreen()
    {

        this->stageStartTone.play();
        
        this->window->clear();
        this->renderGameBackground();
        this->puntaje->setTextSize(16);
        this->puntaje->setTextColor(sf::Color::Cyan);
        this->puntaje->setPosition(225.f, 250.f);
        this->puntaje->setText(std::stringstream() << "Stage inf.");
        this->puntaje->render(this->window);

        this->printPoints();
        this->window->display();
        
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }

    bool isType1Full()
    {
        for (int i = 0; i < 8; i++)
        {
            if (this->slotStateType1[i] == false)
            {
                this->type1Full = false;
                break;
            }
            else
            {
                this->typeToGenerate = rand() % 3 + 1;
                this->type1Full = true;
            }
        }
        return this->type1Full;
    }

    bool isType2Full()
    {
        for (int i = 0; i < 8; i++)
        {
            if (this->slotStateType2R1[i] == false || this->slotStateType2R2[i] == false)
            {
                this->type2Full = false;
                break;
            }
            else
            {
                this->typeToGenerate = rand() % 3 + 1;
                this->type2Full = true;
            }
        }
        return this->type2Full;
    }

    bool isType3Full()
    {
        for (int i = 0; i < 8; i++)
        {
            if (this->slotStateType3R1[i] == false || this->slotStateType3R2[i] == false)
            {
                this->type3Full = false;
                break;
            }
            else
            {
                this->typeToGenerate = rand() % 3 + 1;
                this->type3Full = true;
            }
        }
        return this->type3Full;
    }

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
                else if (this->event.key.code == sf::Keyboard::Enter && !this->gameStarted)
                {
                    this->gameStarted = true;
                    this->introTone.stop();
                    this->stageStartScreen();
                    this->introTone.stop();
                }
                break;
            }
        }
    }

    bool runTrajectoryGen2(int i) // Trayectoria 2 para enemigos.
    {
        
        // Establece la posición inicial del enemigo antes de aparecer en la pantalla
        if (this->moveStep == -1.f)
        {
            std::visit([](const auto &arg)
                       { arg->setToXY(250.f, -40.f); }, enemigosActivos[i]);
            
            this->moveStep = 0.f;
            this->isSorted = false;
        }

        int VX = std::visit([](const auto &arg)
                            { return arg->getXPos(); }, enemigosActivos[i]);

        int VY = std::visit([](const auto &arg)
                            { return arg->getYPos(); }, enemigosActivos[i]);
                            
        // Primer movimiento
        if (VY < 100 && this->moveStep == 0.f)
        {
            std::visit([](const auto &arg)
                       { arg->moveDown(); }, enemigosActivos[i]);          
        }
        else if (this->moveStep == 0.f)
        {
            this->moveStep = 1.f;
        }

        // Segundo movimiento
        if (VX > 150.f && this->moveStep == 1.f)
        {
            //this->enemigos[i]->moveDiagDownLeft(1.5, 1.f);
            std::visit([](const auto &arg)
                       { arg->moveDiagDownLeft(1.5, 1.f); }, enemigosActivos[i]);
        }
        else if (this->moveStep == 1.f)
        {
            this->moveStep = 2.f;
        }

        // Tercer movimiento
        if (VX > 60.f && this->moveStep == 2.f)
        {
            //this->enemigos[i]->moveDiagDownLeft(1, 1.5);
            std::visit([](const auto &arg)
                       { arg->moveDiagDownLeft(1, 1.5); }, enemigosActivos[i]);
        }
        else if (this->moveStep == 2.f)
        {
            this->moveStep = 3.f;
        }

        // Cuarto movimiento
        if (VY < 380.f && this->moveStep == 3.f)
        {
            //this->enemigos[i]->moveDown();
            std::visit([](const auto &arg)
                       { arg->moveDown(); }, enemigosActivos[i]);
        }
        else if (this->moveStep == 3.f)
        {
            this->moveStep = 4.f;
        }

        // Quinto movimiento
        if (VX < 150.f && this->moveStep == 4.f)
        {
            //this->enemigos[i]->moveDiagDownRight(1.3, 0.8);
            std::visit([](const auto &arg)
                       { arg->moveDiagDownRight(1.3, 0.8); }, enemigosActivos[i]);
        }
        else if (this->moveStep == 4.f)
        {
            this->moveStep = 5.f;
        }

        // Sexto movimiento
        if (VX < 250.f && this->moveStep == 5.f)
        {
            //this->enemigos[i]->moveDiagUpRight(1.3, 0.8);
            std::visit([](const auto &arg)
                       { arg->moveDiagUpRight(1.3, 0.8); }, enemigosActivos[i]);
        }
        else if (this->moveStep == 5.f)
        {
            this->moveStep = 6.f;
        }

        // Séptimo movimiento
        if (VY > 360.f && this->moveStep == 6.f)
        {
            //this->enemigos[i]->moveUp();
            std::visit([](const auto &arg)
                       { arg->moveUp(); }, enemigosActivos[i]);
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
            this->trajectoryPicked = rand() % 2;
        }
        return readyToSort;
    }
    
    bool runTrajectoryGen1(int i) // Trayectoria 1 para enemigos.
    {
        int VX = std::visit([](const auto &arg)
                            { return arg->getXPos(); }, enemigosActivos[i]);

        int VY = std::visit([](const auto &arg)
                            { return arg->getYPos(); }, enemigosActivos[i]);

        // Establece la posición inicial del enemigo antes de aparecer en la pantalla
        if (this->moveStep == -1.f)
        {
            std::visit([](const auto &arg)
                       { arg->setToXY(310.f, -40.f); }, enemigosActivos[i]);

            this->moveStep = 0.f;
            this->isSorted = false;
        }

        // Primer movimiento
        if (VY < 100.f && this->moveStep == 0.f)
        {
            std::visit([](const auto &arg)
                       { arg->moveDown(); }, enemigosActivos[i]);
        }
        else if (this->moveStep == 0.f)
        {
            this->moveStep = 1.f;
        }

        // Segundo movimiento
        if (VX < 450.f && this->moveStep == 1.f)
        {
            std::visit([](const auto &arg)
                       { arg->moveDiagDownRight(1.5, 1.f); }, enemigosActivos[i]);
        }
        else if (this->moveStep == 1.f)
        {
            this->moveStep = 2.f;
        }

        // Tercer movimiento
        if (VX < 500.f && this->moveStep == 2.f)
        {
            std::visit([](const auto &arg)
                       { arg->moveDiagDownRight(1, 1.5); }, enemigosActivos[i]);
        }
        else if (this->moveStep == 2.f)
        {
            this->moveStep = 3.f;
        }

        // Cuarto movimiento
        if (VY < 380.f && this->moveStep == 3.f)
        {
            std::visit([](const auto &arg)
                       { arg->moveDown(); }, enemigosActivos[i]);
        }
        else if (this->moveStep == 3.f)
        {
            this->moveStep = 4.f;
        }

        // Quinto movimiento
        if (VX > 390.f && this->moveStep == 4.f)
        {
            std::visit([](const auto &arg)
                       { arg->moveDiagDownLeft(1.3, 0.8); }, enemigosActivos[i]);
        }
        else if (this->moveStep == 4.f)
        {
            this->moveStep = 5.f;
        }

        // Sexto movimiento
        if (VX > 310.f && this->moveStep == 5.f)
        {
            std::visit([](const auto &arg)
                       { arg->moveDiagUpLeft(1.3, 0.8); }, enemigosActivos[i]);
        }
        else if (this->moveStep == 5.f)
        {
            this->moveStep = 6.f;
        }

        // Séptimo movimiento
        if (VY > 360.f && this->moveStep == 6.f)
        {
            std::visit([](const auto &arg)
                       { arg->moveUp(); }, enemigosActivos[i]);
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
            this->trajectoryPicked = rand() % 2;
        }
        return readyToSort;
    }

    void sortEnemyGEN(int i)
    {
        /*
        Esta función se encarga de ordenar a los enemigos en la pantalla, dependiendo de su tipo, se les asigna una posición
        en X y Y predefinidas según una matriz de posiciones, esto se ejecuta una vez que el enemigo haya terminado de recorrer
        la trayectoria mediante la que aparece en la pantalla.
        La posición que se le asigna en Y depende de su tipo, mientras que la posición en X es aleatoria para agregar un poco de
        variabilidad en la posición de los enemigos cada vez que se juegue una partida.
        */
        this->type = std::visit([](const auto &arg)
                                { return arg->getType(); }, enemigosActivos[i]);

        int VX = std::visit([](const auto &arg)
                            { return arg->getXPos(); }, enemigosActivos[i]);

        int VY = std::visit([](const auto &arg)
                            { return arg->getYPos(); }, enemigosActivos[i]);

        int speed = std::visit([](const auto &arg)
                               { return arg->getSpeed(); }, enemigosActivos[i]);

        if (this->type == 1.f)
        {
            if (this->sortX == -1.f && this->sortY == -1.f)
            {
                randAX = rand() % 8;
                randAY = 0;

                this->sortX = this->xPosArray[randAX];
                this->sortY = this->yPosType1;

                if (this->slotStateType1[randAX] == true)
                {
                    randAX = rand() % 8;
                    this->sortX = -1.f;
                    this->sortY = -1.f;
                }
                else
                {
                    this->slotStateType1[randAX] = true;
                }
            }
            if (VX < this->sortX)
            {
                std::visit([](const auto &arg)
                           { arg->moveRight(); }, enemigosActivos[i]);
            }
            else if (VX > this->sortX)
            {
                std::visit([](const auto &arg)
                           { arg->moveLeft(); }, enemigosActivos[i]);
            }

            if (VY > this->sortY)
            {
                std::visit([](const auto &arg)
                           { arg->moveUp(); }, enemigosActivos[i]);
            }
            if (VY < this->sortY)
            {
                std::visit([](const auto &arg)
                           { arg->moveDown(); }, enemigosActivos[i]);
            }

            if ((abs(this->sortX - VX)) <= speed && (abs(this->sortY - VY)) < speed)
            {
                std::visit([this](const auto &arg)
                           { arg->setToXY(this->sortX, this->sortY); }, enemigosActivos[i]);
            }
        }
        else if (this->type == 2.f)
        {
            if (this->sortX == -1.f && this->sortY == -1.f)
            {
                this->randAX = rand() % 8;
                this->randAY = rand() % 2;

                this->sortX = this->xPosArray[this->randAX];
                this->sortY = this->yposType2[this->randAY];

                if (this->randAY == 0)
                {
                    if (this->slotStateType2R1[this->randAX] == true)
                    {
                        this->sortX = -1.f;
                        this->sortY = -1.f;

                        this->randAX = rand() % 8;
                        this->randAY = rand() % 2;
                    }
                    else
                    {
                        this->slotStateType2R1[this->randAX] = true;
                    }
                }
                else if (this->randAY == 1)
                {
                    if (this->slotStateType2R2[this->randAX] == true)
                    {
                        this->sortX = -1.f;
                        this->sortY = -1.f;

                        this->randAX = rand() % 8;
                        this->randAY = rand() % 2;
                    }
                    else
                    {
                        this->slotStateType2R2[this->randAX] = true;
                    }
                }
            }
            if (VX < this->sortX)
            {
                std::visit([](const auto &arg)
                           { arg->moveRight(); }, enemigosActivos[i]);
            }
            else if (VX > this->sortX)
            {
                std::visit([](const auto &arg)
                           { arg->moveLeft(); }, enemigosActivos[i]);
            }

            if (VY > this->sortY)
            {
                std::visit([](const auto &arg)
                           { arg->moveUp(); }, enemigosActivos[i]);
            }
            if (VY < this->sortY)
            {
                std::visit([](const auto &arg)
                           { arg->moveDown(); }, enemigosActivos[i]);
            }
            if ((abs(this->sortX - VX)) <= speed && (abs(this->sortY - VY)) < speed)
            {
                std::visit([this](const auto &arg)
                           { arg->setToXY(this->sortX, this->sortY); }, enemigosActivos[i]);
            }
        }
        else if (this->type == 3.f)
        {
            if (this->sortX == -1.f && this->sortY == -1.f)
            {
                this->randAX = rand() % 8;
                this->randAY = rand() % 2;

                this->sortX = this->xPosArray[this->randAX];
                this->sortY = this->yposType3[this->randAY];

                if (this->randAY == 0)
                {
                    if (this->slotStateType3R1[this->randAX] == true)
                    {
                        this->sortX = -1.f;
                        this->sortY = -1.f;

                        this->randAX = rand() % 8;
                        this->randAY = rand() % 2;
                    }
                    else
                    {
                        this->slotStateType3R1[this->randAX] = true;
                    }
                }
                else if (this->randAY == 1)
                {
                    if (this->slotStateType3R2[this->randAX] == true)
                    {
                        this->sortX = -1.f;
                        this->sortY = -1.f;

                        this->randAX = rand() % 8;
                        this->randAY = rand() % 2;
                    }
                    else
                    {
                        this->slotStateType3R2[this->randAX] = true;
                    }
                }
            }
            if (VX < this->sortX)
            {
                std::visit([](const auto &arg)
                           { arg->moveRight(); }, enemigosActivos[i]);
            }
            else if (VX > this->sortX)
            {
                std::visit([](const auto &arg)
                           { arg->moveLeft(); }, enemigosActivos[i]);
            }

            if (VY > this->sortY)
            {
                std::visit([](const auto &arg)
                           { arg->moveUp(); }, enemigosActivos[i]);
            }
            if (VY < this->sortY)
            {
                std::visit([](const auto &arg)
                           { arg->moveDown(); }, enemigosActivos[i]);
            }
            if ((abs(this->sortX - VX)) <= speed && (abs(this->sortY - VY)) < speed)
            {
                std::visit([this](const auto &arg)
                           { arg->setToXY(this->sortX, this->sortY); }, enemigosActivos[i]);

                VX = std::visit([](const auto &arg)
                                { return arg->getXPos(); }, enemigosActivos[i]);

                VY = std::visit([](const auto &arg)
                                { return arg->getYPos(); }, enemigosActivos[i]);
            }
        }

        if (this->sortX == VX && this->sortY == VY)
        {
            this->sortX = -1.f;
            this->sortY = -1.f;
            this->readyToSort = false;
            this->enemySorted[i] = 1;
            this->typeToGenerate = rand() % 3 + 1;
        }
    }

    void checkForHits()
    {
        for (int i = 0; i < this->enemigosActivos.size(); i++)
        {
            bool enemigoEliminado = false;
            for (size_t k = 0; k < nave->getProyectilesSize() && !enemigoEliminado; k++)
            {

                if (nave->getProyectilesBounds(k).intersects(
                        std::visit([](const auto &arg)
                                   { return arg->getBounds(); }, enemigosActivos[i])))
                {
                    float X = std::visit([](const auto &arg)
                                         { return arg->getXPos(); }, enemigosActivos[i]);

                    float Y = std::visit([](const auto &arg)
                                         { return arg->getYPos(); }, enemigosActivos[i]);

                    this->type = std::visit([](const auto &arg)
                                            { return arg->getType(); }, enemigosActivos[i]);

                    int hitCount = std::visit([](const auto &arg)
                                              { return arg->getHitCount(); }, enemigosActivos[i]);
                    
                    
                    if (this->type == 1 && hitCount == 0)
                    {
                        std::visit([](const auto &arg)
                                   { arg->playDamageSound(); }, enemigosActivos[i]);

                        std::visit([](const auto &arg)
                                   { arg->takeHit(); }, enemigosActivos[i]);

                        nave->deleteProyectil(k);
                    }
                    else
                    {
                        if(this->type == 1)
                        {
                            this->puntaje->increasePoints(type1Value);
                        }
                        else if(this->type == 2)
                        {
                            this->puntaje->increasePoints(type2Value);
                        }
                        else if(this->type == 3)
                        {
                            this->puntaje->increasePoints(type3Value);
                        }
                        
                        std::visit([](const auto &arg)
                                   { arg->playDeathSound(); }, enemigosActivos[i]);

                        for (int j = 0; this->slotReseted == false && j <= 1; j++)
                        {
                            if (Y == yPosType1)
                            {
                                yDelete = 11;
                            }
                            else if (Y == yposType2[j])
                            {
                                if (j == 0)
                                {
                                    yDelete = 21;
                                }
                                else if (j == 1)
                                {
                                    yDelete = 22;
                                }
                            }
                            else if (Y == yposType3[j])
                            {
                                if (j == 0)
                                {
                                    yDelete = 31;
                                }
                                else if (j == 1)
                                {
                                    yDelete = 32;
                                }
                            }

                            if (yDelete > 0)
                            {
                                for (int l = 0; this->slotReseted == false && l <= 7; l++)
                                {
                                    if (X == this->xPosArray[l])
                                    {
                                        this->slotReseted = true;
                                        if (yDelete == 11)
                                        {
                                            this->slotStateType1[l] = false;
                                        }
                                        else if (yDelete == 21)
                                        {
                                            this->slotStateType2R1[l] = false;
                                        }
                                        else if (yDelete == 22)
                                        {
                                            this->slotStateType2R2[l] = false;
                                        }
                                        else if (yDelete == 31)
                                        {
                                            this->slotStateType3R1[l] = false;
                                        }
                                        else if (yDelete == 32)
                                        {
                                            this->slotStateType3R2[l] = false;
                                        }
                                    }
                                }
                            }
                            this->slotReseted = false;
                        }

                        nave->deleteProyectil(k);
                        this->enemigosActivos.erase(this->enemigosActivos.begin() + i);

                        if (enemySorted[i] == 0)
                        {
                            this->moveStep = -1.f;
                        }
                        this->enemySorted.erase(this->enemySorted.begin() + i);

                        enemigoEliminado = true;
                        // std::cout << "Enemigo eliminado" << std::endl;
                        // std::cout << this->enemigos.size() << std::endl;
                    }
                }
            }
        }
    }

    void pickAndShoot()
    {
        /*
        Esta función se encarga de aleatoriamente seleccionar enemigos activos y para hacerlos disparar
        la cantidad de enemigos que disparan a la vez va en función de la cantidad de enemigos activos
        en pantalla y va desde 1 hasta 4 enemigos disparando a la vez o 5 si llenan todas las celdas.
        */
        for (int i = 1; i <= ((std::floor(this->enemigosActivos.size() / 10)) + 1); i++)
        {
            randEnemy = rand() % this->enemigosActivos.size();
            std::visit([this](const auto &arg)
                       { arg->shoot(); }, enemigosActivos[randEnemy]);
        }
    }

    void updateEnemigos()
    {
        /*
        Esta función es una de las más importantes en el juego, se encarga de la generación aleatoria de enemigos, de asignarles una de las trayectorias
        que existen de forma aleatoria, además de mandar a llamar otras funciones relacionadas a estos, como la función que se encarga de ordenarlos,
        la función que se encarga de revisar si un enemigo ha sido impactado por un proyectil de la nave o la función que se encarga de hacer que los
        enemigos disparen.
        */

        if (firstEnemy == true) // Primer caso únicamente aplicando al primer enemigo generado
        {
            this->enemigosActivos.push_back(new Abeja(-10000.f, 10000.f)); // El primer enemigo siempre será una abeja (no hay un motivo en particular)
            this->enemySorted.push_back(0);                                // En el vector de enemigos ordenados se asigna un 0 en la posición correspondiente al enemigo
            this->firstEnemy = false;
            this->typeToGenerate = rand() % 3 + 1;
            this->timerToSpawn = 0;
        }

        // std::cout << this->enemigosActivos.size() << std::endl;

        for (int i = 0; i < this->enemigosActivos.size(); i++)
        {
            if (this->readyToSort == false && this->enemySorted[i] == 0)
            {
                this->typeToGenerate = 0;
                this->timerToSpawn = 0;

                if (trajectoryPicked == 0)
                {
                    runTrajectoryGen1(i);
                }
                else
                {
                    runTrajectoryGen2(i);
                }
                
            }

            if (this->readyToSort == true && this->enemySorted[i] == 0)
            {
                sortEnemyGEN(i);
                this->timerToSpawn = 0;
            }

            j = i;
        }

        // std::cout << timerToSpawn << std::endl;
        if (firstEnemy == false && enemySorted[j] == 1 && !isType1Full() && this->typeToGenerate == 1)
        {
            this->enemigosActivos.push_back(new Jefe(-10000.f, 10000.f));
            this->enemySorted.push_back(0);
            this->readyToSort = false;
            this->timerToSpawn = 0;
        }
        else
        {
            this->timerToSpawn++;
        }

        if (firstEnemy == false && enemySorted[j] == 1 && !isType2Full() && this->typeToGenerate == 2)
        {
            this->enemigosActivos.push_back(new Mariposa(-10000.f, 10000.f));
            this->enemySorted.push_back(0);
            this->readyToSort = false;
            this->timerToSpawn = 0;
        }
        else
        {
            this->timerToSpawn++;
        }

        if (firstEnemy == false && enemySorted[j] == 1 && !isType3Full() && this->typeToGenerate == 3)
        {
            this->enemigosActivos.push_back(new Abeja(-10000.f, 10000.f));
            this->enemySorted.push_back(0);
            this->readyToSort = false;
            this->timerToSpawn = 0;
        }
        else
        {
            this->timerToSpawn++;
        }

        if (this->enemigosActivos.size() == 0)
        {
            typeToGenerate = rand() % 3 + 1;
            if (this->typeToGenerate == 1)
            {
                this->enemigosActivos.push_back(new Jefe(-10000.f, 10000.f));
                this->enemySorted.push_back(0);
                this->readyToSort = false;
                this->timerToSpawn = 0;
            }
            if (this->typeToGenerate == 2)
            {
                this->enemigosActivos.push_back(new Mariposa(-10000.f, 10000.f));
                this->enemySorted.push_back(0);
                this->readyToSort = false;
                this->timerToSpawn = 0;
            }
            if (this->typeToGenerate == 3)
            {
                this->enemigosActivos.push_back(new Abeja(-10000.f, 10000.f));
                this->enemySorted.push_back(0);
                this->readyToSort = false;
                this->timerToSpawn = 0;
            }
        }

        if (this->timerToSpawn >= this->timerToSpawnLimit)
        {
            typeToGenerate = rand() % 3 + 1;
            if (this->typeToGenerate == 1 && !isType1Full())
            {
                this->enemigosActivos.push_back(new Jefe(-10000.f, 10000.f));
                this->enemySorted.push_back(0);
                this->readyToSort = false;
                this->timerToSpawn = 0;
            }
            if (this->typeToGenerate == 2 && !isType1Full())
            {
                this->enemigosActivos.push_back(new Mariposa(-10000.f, 10000.f));
                this->enemySorted.push_back(0);
                this->readyToSort = false;
                this->timerToSpawn = 0;
            }
            if (this->typeToGenerate == 3 && !isType1Full())
            {
                this->enemigosActivos.push_back(new Abeja(-10000.f, 10000.f));
                this->enemySorted.push_back(0);
                this->readyToSort = false;
                this->timerToSpawn = 0;
            }
        }

        this->checkForHits();

        if (this->enemyShootingInterval >= this->enemyShootingIntervalLimit)
        {
            this->enemyShootingInterval = 0;
            this->pickAndShoot();
        }
        else
        {
            this->enemyShootingInterval++;
        }
    }

    void updateNave()
    {
        // Actualiza la nave
        this->nave->update(this->window);

        /*
        En este segmento de updateNave se revisa uno por uno los proyectiles que cada enemigo ha disparado
        para detectar si uno de ellos impacta con la nave (es decir sus hitboxes se intersectan), si este
        es el caso, se elimina dicho proyectil enemigo y se procede con la animación de la destrucción de la
        nave, se le reduce una vida a la nave y se revisa si la nave aún tiene vidas restantes, si no es así
        se termina el juego, caso contrario se reinicia la posición de la nave y se le asigna su textura por
        defecto.
        */
        for (int i = 0; i < this->enemigosActivos.size(); i++)
        {
            int proyectilesEnemigosActivos = std::visit([](const auto &arg)
                                                        { return arg->getProyectilesSize(); }, enemigosActivos[i]);

            for (size_t k = 0; k < proyectilesEnemigosActivos; k++)
            {
                if (this->nave->getBounds().intersects(
                        std::visit([k](const auto &arg)
                                   { return arg->getProyectilesBounds(k); }, enemigosActivos[i])))
                {
                    std::visit([k](const auto &arg)
                               { arg->deleteProyectil(k); }, enemigosActivos[i]);

                    this->nave->playDestroyedSound();

                    for (int i = 0; i <= 400; i++)
                    {
                        if (i <= 40)
                        {
                            this->nave->setDestroyedTexture1();
                        }
                        else if (i <= 80)
                        {
                            this->nave->setDestroyedTexture2();
                        }
                        else if (i <= 120)
                        {
                            this->nave->setDestroyedTexture3();
                        }
                        else if (i <= 160)
                        {
                            this->nave->setDestroyedTexture4();
                        }
                        else if (i <= 400)
                        {
                            this->nave->setDestroyedTexture5();
                        }
                        this->nave->render(this->window);
                        this->window->display();
                    }

                    if (this->nave->takeHit() == 0)
                    {
                        gameOverTone.play();
                        this->puntaje->setTextSize(30);
                        this->puntaje->setTextColor(sf::Color::Red);
                        this->puntaje->setPosition(180.f, 370.f);
                        this->puntaje->setText(std::stringstream() << "GAME OVER");
                        this->puntaje->render(this->window);
                        this->window->display();

                        std::this_thread::sleep_for(std::chrono::seconds(8));
                        this->endGame = true;
                    }
                    else
                    {
                        this->nave->setDefaultTexture();
                        this->nave->playRespawnSound();
                        this->nave->resetPosition();
                    }
                }
            }
        }
    }

    void update()
    {        
        if(gameStarted == true)
        {
            // Actualiza los eventos de la ventana
            this->pollEvents();

            // Actualiza todo lo relacionado con la nave, como su posición, proyectiles, etc.
            this->updateNave();

            // Actualiza todo lo relacionado con los enemigos, como su posición, movimiento, estado, etc.
            this->updateEnemigos();

            // Actualiza los disparos realizados por los enemigos
            for (int i = 0; i < this->enemigosActivos.size(); i++)
            {
                std::visit([this](const auto &arg)
                        { arg->update(); }, enemigosActivos[i]);
            }

            // Actualiza el puntaje
            this->printPoints();
        }
        else if(this->gameStarted == false)
        {
            this->loadStartScreen();
        }
    }

    void render()
    {
        if(gameStarted == true) // Solo comienza a renderizar si el juego ha comenzado (Se presionó la tecla ENTER)
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

            this->renderGameBackground();

            this->puntaje->render(this->window);
            
            this->nave->render(this->window);

            for (int i = 0; i < this->enemigosActivos.size(); i++)
            {
                std::visit([this](const auto &arg)
                        { arg->render(this->window); }, enemigosActivos[i]);
            }

            // Una vez dibujados los elementos, se muestra la ventana (Equivale a 1 frame)

            this->window->display();
        }
    }
};