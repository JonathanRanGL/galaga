#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/color.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <list>
#include <fstream>

using namespace std;
using namespace ftxui;

int main(int argc, char const *argv[])
{
    fstream imagen;
    list<string> textos;
    string linea;

    imagen.open("./assets/imagen.txt");
    
    while (getline(imagen, linea))
    {
        textos.push_back(linea);
    }
    imagen.close();

    int posX = 0;
    int posY = 1;
    int fotograma = 0;
    string reset;

    Decorator colorFondo = bgcolor(Color::RGB(R, G, B));
    Decorator colorTexto = color(Color::RGB(B, G, R));
    Element dibujo = border({hbox() | colorFondo | colorTexto});

    Dimensions Alto = Dimension::Full();
    Dimensions Ancho = Dimension::Full();

    // Crear pantalla
    Screen pantalla = Screen::Create(Ancho, Alto);

    // Imprimir en la pantalla
    Render(pantalla, dibujo);

    pantalla.Print();

    // Resetear pantalla
    reset = pantalla.ResetPosition();
    cout << reset;
    this_thread::sleep_for(0.1s);
    
    return 0;
}
