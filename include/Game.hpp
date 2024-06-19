#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <math.h>
#include <vector>
#include <variant>

#include <Nave.hpp>
#include <Proyectil.hpp>
#include <Enemigo.hpp>
#include <Abeja.hpp>
#include <Mariposa.hpp>
#include <Jefe.hpp>

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

    // Window

    sf::RenderWindow *window;
    sf::VideoMode videoMode;
    sf::Event event;

    // Objetos dentro del juego

    Nave *nave;

    using EnemigosActivos = std::variant<Abeja *, Mariposa *, Jefe *>;
    std::vector<EnemigosActivos> enemigosActivos;

    std::vector<Abeja *> abejas;

    /*
    Se crea un vector de enemigos encargado de almacenar los datos de todos los enemigos activos.
    Si el enemigo muere, se elimina del vector liberando la memporia que ocupaba, al igual que se
    hace con el proyectil de la nave que lo impactó y todos aquellos proyectiles que salen de la
    ventana.
    */
    std::vector<Enemigo *> enemigos;

    /*
    Este vector se encarga de almacenar un 1 o un 0 que indicará si el enemigo ha sido ordenado o no,
    para cada enemigo activo en la pantalla, hay un valor dentro de este vector
    */
    std::vector<int> enemySorted;

    // Funciones privadas

    void initVariables()
    {
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

        for (auto *i : this->abejas)
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
                break;
            }
        }
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
            this->trajectoryPicked = rand() % 2;
        }
        return readyToSort;
    }

    bool trajectoryGEN1(int i) // Trayectoria 1 para enemigos.
    {
        int VX = std::visit([](const auto& arg){
            return arg->getXPos();
        }, enemigosActivos[i]);
        
        int VY = std::visit([](const auto& arg){
            return arg->getYPos();
        }, enemigosActivos[i]);
        
        // Establece la posición inicial del enemigo antes de aparecer en la pantalla
        if (this->moveStep == -1.f)
        {
            std::visit([](const auto& arg){
                arg->setToXY(310.f, -40.f);
            }, enemigosActivos[i]);
            
            this->moveStep = 0.f;
            this->isSorted = false;
        }

        // Primer movimiento
        if (VY < 100.f && this->moveStep == 0.f)
        {
            std::visit([](const auto& arg){
                arg->moveDown();
            }, enemigosActivos[i]);
        }
        else if (this->moveStep == 0.f)
        {
            this->moveStep = 1.f;
        }

        // Segundo movimiento
        if(VX < 450.f && this->moveStep == 1.f)
        {
            std::visit([](const auto& arg){
                arg->moveDiagDownRight(1.5, 1.f);
            }, enemigosActivos[i]);
        }
        else if (this->moveStep == 1.f)
        {
            this->moveStep = 2.f;
        }

        // Tercer movimiento
        if (VX < 500.f && this->moveStep == 2.f)
        {
            std::visit([](const auto& arg){
                arg->moveDiagDownRight(1, 1.5);
            }, enemigosActivos[i]);
        }
        else if (this->moveStep == 2.f)
        {
            this->moveStep = 3.f;
        }

        // Cuarto movimiento
        if (VY < 380.f && this->moveStep == 3.f)
        {
            std::visit([](const auto& arg){
                arg->moveDown();
            }, enemigosActivos[i]);
        }
        else if (this->moveStep == 3.f)
        {
            this->moveStep = 4.f;
        }

        // Quinto movimiento
        if (VX > 390.f && this->moveStep == 4.f)
        {
            std::visit([](const auto& arg){
                arg->moveDiagDownLeft(1.3, 0.8);
            }, enemigosActivos[i]);
        }
        else if (this->moveStep == 4.f)
        {
            this->moveStep = 5.f;
        }

        // Sexto movimiento
        if (VX > 310.f && this->moveStep == 5.f)
        {
            std::visit([](const auto& arg){
                arg->moveDiagUpLeft(1.3, 0.8);
            }, enemigosActivos[i]);
        }
        else if (this->moveStep == 5.f)
        {
            this->moveStep = 6.f;
        }

        // Séptimo movimiento
        if (VY > 360.f && this->moveStep == 6.f)
        {
            std::visit([](const auto& arg){
                arg->moveUp();
            }, enemigosActivos[i]);
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
        this->type = std::visit([](const auto& arg){
            return arg->getType();
        }, enemigosActivos[i]);

        int VX = std::visit([](const auto& arg){
            return arg->getXPos();
        }, enemigosActivos[i]);

        int VY = std::visit([](const auto& arg){
            return arg->getYPos();
        }, enemigosActivos[i]);

        int speed = std::visit([](const auto& arg){
            return arg->getSpeed();
        }, enemigosActivos[i]);

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
                std::visit([](const auto& arg){
                    arg->moveRight();
                }, enemigosActivos[i]);
            }
            else if (VX > this->sortX)
            {
                std::visit([](const auto& arg){
                    arg->moveLeft();
                }, enemigosActivos[i]);
            }

            if (VY > this->sortY)
            {
                std::visit([](const auto& arg){
                    arg->moveUp();
                }, enemigosActivos[i]);
            }
            if (VY < this->sortY)
            {
                std::visit([](const auto& arg){
                    arg->moveDown();
                }, enemigosActivos[i]);
            }
            
            if ((abs(this->sortX - VX)) <= speed && (abs(this->sortY - VY)) < speed)
            {
                std::visit([this](const auto& arg){
                    arg->setToXY(this->sortX, this->sortY);
                }, enemigosActivos[i]);
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
                std::visit([](const auto& arg){
                    arg->moveRight();
                }, enemigosActivos[i]);
            }
            else if (VX > this->sortX)
            {
                std::visit([](const auto& arg){
                    arg->moveLeft();
                }, enemigosActivos[i]);
            }

            if (VY > this->sortY)
            {
                std::visit([](const auto& arg){
                    arg->moveUp();
                }, enemigosActivos[i]);
            }
            if (VY < this->sortY)
            {
                std::visit([](const auto& arg){
                    arg->moveDown();
                }, enemigosActivos[i]);
            }
            if ((abs(this->sortX - VX)) <= speed && (abs(this->sortY - VY)) < speed)
            {
                std::visit([this](const auto& arg){
                    arg->setToXY(this->sortX, this->sortY);
                }, enemigosActivos[i]);
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
                std::visit([](const auto& arg){
                    arg->moveRight();
                }, enemigosActivos[i]);
            }
            else if (VX > this->sortX)
            {
                std::visit([](const auto& arg){
                    arg->moveLeft();
                }, enemigosActivos[i]);
            }

            if (VY > this->sortY)
            {
                std::visit([](const auto& arg){
                    arg->moveUp();
                }, enemigosActivos[i]);
            }
            if (VY < this->sortY)
            {
                std::visit([](const auto& arg){
                    arg->moveDown();
                }, enemigosActivos[i]);
            }
            if ((abs(this->sortX - VX)) <= speed && (abs(this->sortY - VY)) < speed)
            {
                std::visit([this](const auto& arg){
                    arg->setToXY(this->sortX, this->sortY);
                }, enemigosActivos[i]);

                VX = std::visit([](const auto& arg){
                    return arg->getXPos();
                }, enemigosActivos[i]);

                VY = std::visit([](const auto& arg){
                    return arg->getYPos();
                }, enemigosActivos[i]);
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
                        std::visit([](const auto& arg){
                            return arg->getBounds();
                        }, enemigosActivos[i])
                    ))
                {
                    float X = std::visit([](const auto& arg){
                        return arg->getXPos();
                    }, enemigosActivos[i]);
                    
                    float Y = std::visit([](const auto& arg){
                        return arg->getYPos();
                    }, enemigosActivos[i]);

                    this->type = std::visit([](const auto& arg){
                        return arg->getType();
                    }, enemigosActivos[i]);

                    int hitCount = std::visit([](const auto& arg){
                        return arg->getHitCount();
                    }, enemigosActivos[i]);

                    
                    
                    if(this->type == 1 && hitCount == 0)
                    {
                        std::visit([](const auto& arg){
                            arg->playDamageSound();
                        }, enemigosActivos[i]);
                        
                        std::visit([](const auto& arg){
                            arg->takeHit();
                        }, enemigosActivos[i]);
                        
                        nave->deleteProyectil(k);
                    }
                    else
                    {
                        std::visit([](const auto& arg){
                            arg->playDeathSound();
                        }, enemigosActivos[i]);

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
                        //this->j = 0;

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

    void updateEnemigos()
    {
        if (firstEnemy == true) // Primer caso únicamente aplicando al primer enemigo generado
        {
            this->enemigosActivos.push_back(new Abeja(-10000.f, 10000.f)); 
            this->enemySorted.push_back(0);                                 // En el vector de enemigos ordenados se asigna un 0 en la posición correspondiente al enemigo
            this->firstEnemy = false;
            this->typeToGenerate = rand() % 3 + 1;
            this->timerToSpawn = 0;
        }

        //std::cout << this->enemigosActivos.size() << std::endl;

        for (int i = 0; i < this->enemigosActivos.size() ; i++)
        {
            if (this->readyToSort == false && this->enemySorted[i] == 0)
            {
                
                trajectoryGEN1(i);
                this->typeToGenerate = 0;
                this->timerToSpawn = 0;

                /*
                if (trajectoryPicked == 0)
                {
                    trajectoryE1(i);
                }
                else
                {
                    trajectoryE2(i);
                }
                */
            }

            if (this->readyToSort == true && this->enemySorted[i] == 0)
            {
                sortEnemyGEN(i);
                this->timerToSpawn = 0;
            }

            j = i;
        }

        std::cout << "J en updateEnemigos: " << j << std::endl;
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

        if(this->timerToSpawn >= this->timerToSpawnLimit)
        {
            typeToGenerate = rand() % 3 + 1;
            if (this->typeToGenerate == 1 && !isType1Full())
            {
                this->enemigosActivos.push_back(new Jefe(-10000.f, 10000.f)); 
                this->enemySorted.push_back(0);
                this->readyToSort = false;
                this->timerToSpawn = 0;
                
            }
            if (this->typeToGenerate == 2  && !isType1Full())
            {
                this->enemigosActivos.push_back(new Mariposa(-10000.f, 10000.f)); 
                this->enemySorted.push_back(0);
                this->readyToSort = false;
                this->timerToSpawn = 0;
            }
            if (this->typeToGenerate == 3  && !isType1Full())
            {
                this->enemigosActivos.push_back(new Abeja(-10000.f, 10000.f)); 
                this->enemySorted.push_back(0);
                this->readyToSort = false;
                this->timerToSpawn = 0;
            }
        }
        
        /*
        for(int k = 0; k < this->enemySorted.size(); k++)
        {
            if(this->enemySorted[])
        }
*/
        

        this->checkForHits();

        
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

        for (auto *Abeja : this->abejas)
        {
            Abeja->render(this->window);
        }

        for(int i = 0; i < this->enemigosActivos.size(); i++)
        {
            std::visit([this](const auto& arg){
                arg->render(this->window);
            }, enemigosActivos[i]);
        }

        // Una vez dibujados los elementos, se muestra la ventana (Equivale a 1 frame)

        this->window->display();
    }
};