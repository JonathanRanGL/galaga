# **Galaga Game**
![Inicio](https://github.com/JonathanRanGL/galaga/assets/159947420/164ed5d2-c116-4d04-874a-655a4cda710b)

## **Creadores**
___
-Jonathan Rodrigo Sanchez Rangel

-Kenya Gabriela Frutos Gonzalez

## **Objetivo**
___
* Crear un videojuego arcade en lenguaje c++.

* Dominar el uso de la biblioteca SFML para manejar gráficos, sonido y eventos en juegos.

* El objetivo principal del jugador es acumular la mayor cantidad de puntos posible al eliminar enemigos y completar niveles, mientras intentas superar tus mejores marcas personales.

## **Descripción**
___
Este proyecto consiste en una recreación del clásico juego Galaga (1981), utilizando la biblioteca SFML para crear los gráficos y sonidos necesarios que aseguran una experiencia de juego agradable. En este juego, el jugador controla una nave espacial que se desplaza de izquierda a derecha, esquivando los proyectiles enemigos y disparándoles para eliminarlos.

## **Desarrollo**
___
El juego ha sido desarrollado utilizando Visual Studio Code, el lenguaje C++ en conjunto con la biblioteca SFML, la cual nos permite crear animaciones, cargar imágenes, gestionar sonidos, manipular tipos de fuente, entre otras funcionalidades. En esta implementación se ha puesto en marcha la mecánica principal del juego, la cual abarca el movimiento del jugador, el disparo de misiles, la aparición y movimiento de los enemigos, así como la lógica de colisiones y el seguimiento de los puntajes obtenidos por el jugador.

Se ha prestado especial atención a los detalles para capturar fielmente la esencia del juego original Galaga.
![Partida](https://github.com/JonathanRanGL/galaga/assets/159947420/832a79cf-f406-40df-9b84-7cb260c2bab5)


## **Como Jugar**
___
 * Movimiento: Utiliza las teclas de dirección (izquierda y derecha) para mover tu nave espacial de un lado a otro en la parte inferior de la pantalla.

* Disparo: Presiona la tecla de disparo para lanzar misiles y destruir a los enemigos.


## **Demostración**
___
[![Video en YouTube](https://img.youtube.com/vi/HOU1MYvxhdw/0.jpg)](https://youtu.be/HOU1MYvxhdw)

## **Carpetas**
___
El proyecto sigue una estructura organizada en varias carpetas para una gestión eficiente de los archivos y recursos del juego.

* .vscode: contiene configuraciones específicas del entorno de desarrollo.

* bin: e utiliza para almacenar los archivos binarios generados por el compilador.

* src: Contiene los archivos fuente del juego, incluido el archivo principal main.cpp que maneja la lógica del juego.

* include: Contiene archivos de cabecera que definen clases, funciones y estructuras de datos utilizadas en el juego.

* assets: Aquí se almacenan los recursos del juego, como las imagenes que se  utilizan para los hacer los sprites, sonidos y fuentes. 

* docs: Contiene documentación relevante del proyecto, como diagramas UML, especificaciones de diseño y otros documentos.

* README.md: Un archivo de markdown que proporciona una descripción general del proyecto, instrucciones de instalación, ejecución y cualquier otra información relevante.


# **Dependencias**
___

### Visual Studio Code
___
Se puede descargar en el siguiente 
[enlace](https://code.visualstudio.com/).

### Github Desktop
___
Se puede descargar en el siguiente 
[enlace](https://desktop.github.com/).

### Git
___
Para poder realizar commits de vscode es necesario tener instalado Git, descargarlo del siguiente [enlace](https://git-scm.com/).

### MSYS2 (Windows)
___
Instalar Msys2 usando el siguiente [enlace](https://github.com/msys2/msys2-installer/releases/download/2023-05-26/msys2-x86_64-20230526.exe).

No modificar ninguna opcion al momento de la instalacion para evitar errores. 

Una vez instalado es necesario agregar los siguientes directorios al path de windows y reiniciar.

> C:\msys64\mingw64\bin

> C:\msys64\usr\bin


# **Librerias**
## MSYS2
### DevTools
> pacman -S --needed base-devel mingw-w64-x86_64-toolchain 

### SFML
> pacman -S mingw-w64-x86_64-sfml


## VSCODE
* Material Icon
* C/C++
* PlantUML
* GitGraph

# **Creditos**

## Imagenes 
[Jefe](https://static.wikia.nocookie.net/ssb/images/3/3c/Boss-Galaga-Sprite.png/revision/latest?cb=20230213092347)

[Abeja](https://www.google.com/url?sa=i&url=https%3A%2F%2Fwww.pngfind.com%2Fmpng%2FmxxioR_galaga-galaga-enemy-no-background-hd-png-download%2F&psig=AOvVaw3eImNE-SvPSPc0YfOadKxi&ust=1718939924951000&source=images&cd=vfe&opi=89978449&ved=0CA8QjRxqFwoTCKDJrq6c6YYDFQAAAAAdAAAAABAn)

[Mariposa](https://www.google.com/url?sa=i&url=https%3A%2F%2Fwww.vhv.rs%2Fviewpic%2FhJxTTox_galaga-bugs-hd-png-download%2F&psig=AOvVaw3eImNE-SvPSPc0YfOadKxi&ust=1718939924951000&source=images&cd=vfe&opi=89978449&ved=0CA8QjRxqFwoTCKDJrq6c6YYDFQAAAAAdAAAAABBN)

[Nave](https://www.google.com/url?sa=i&url=https%3A%2F%2Fwww.pngwing.com%2Fes%2Ffree-png-yklwg&psig=AOvVaw3eImNE-SvPSPc0YfOadKxi&ust=1718939924951000&source=images&cd=vfe&opi=89978449&ved=0CA8QjRxqFwoTCKDJrq6c6YYDFQAAAAAdAAAAABBX)

[Sprites](https://www.google.com/url?sa=i&url=https%3A%2F%2Fwww.spriters-resource.com%2Farcade%2Fgalaga%2Fsheet%2F26482%2F&psig=AOvVaw2Lv7V6U7dzbIu_VRjie-_x&ust=1718940434464000&source=images&cd=vfe&opi=89978449&ved=0CA8QjRxqFwoTCIDqhKGe6YYDFQAAAAAdAAAAABAE)

## Sonidos
[Efectos](https://downloads.khinsider.com/game-soundtracks/album/galaga-arcade)


![Game Over](https://github.com/JonathanRanGL/galaga/assets/159947420/ae772dd0-ef7b-4627-9fbb-30f455236bdc)


