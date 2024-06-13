#include <SFML/Graphics.hpp>
#include <Game.hpp>

int main()
{
    Game game;

    while (game.running()) // Revisa constantemente si la ventana sigue abierta
    {
        
        // Update
        game.update();

        // Render
        game.render();

    }

    return 0;
}