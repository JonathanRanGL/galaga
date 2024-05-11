# **Galaga Game**
___
El proyecto tiene como objetivo desarrollar un videojuego basado en texto, utilizando arte ASCII, inspirado en el clásico juego arcade Galaga.

* Implementar un sistema de juego que permita al jugador controlar una nave y disparar misiles para eliminar a los enemigos.
* Diseñar niveles progresivamente más difíciles con la aparición de enemigos más poderosos y la inclusión de jefes finales.


## **Carpetas**
___
El proyecto sigue una estructura organizada en varias carpetas para una gestión eficiente de los archivos y recursos del juego.

* src/: Contiene los archivos fuente del juego, incluido el archivo principal main.cpp que maneja la lógica del juego.

* include/: Contiene archivos de cabecera que definen clases, funciones y estructuras de datos utilizadas en el juego.

* assets/: Aquí se almacenan los recursos del juego, como el arte ASCII para la nave del jugador, los enemigos, efectos de sonido, etc.

* ocs/: Contiene documentación relevante del proyecto, como diagramas UML, especificaciones de diseño y otros documentos.

* README.md: Un archivo de markdown que proporciona una descripción general del proyecto, instrucciones de instalación, ejecución y cualquier otra información relevante.

## **Desarrollo**
___
El juego se desarrollará utilizando C++ junto con la biblioteca FTXUI para crear la interfaz de usuario basada en texto. Se implementará la mecánica principal del juego, que incluye el movimiento del jugador, el disparo de misiles, la aparición y movimiento de los enemigos, así como la lógica de colisiones.

La representación visual del juego se realizará utilizando arte ASCII, con archivos de texto dedicados para la nave del jugador, los enemigos y otros elementos del juego. Se prestará atención a los detalles para capturar la esencia del juego original de Galaga. 

# Dependencias

## **GraphViz**
___
~~~
sudo apt update

sudo apt install graphviz
~~~

## **FTXUI**
___
~~~
git clone [link:]https://github.com/ArthurSonzogni/FTXUI.git
sudo apt install cmake
cd FTXUI
mkdir build
cd build
cmake ..
make
sudo make install
~~~

## **Plugins VSCode**
___

* material icon
* c/c++
* plant uml
* cmake
* cmake tools
* make file tools

