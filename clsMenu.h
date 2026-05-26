#ifndef CLSMENU_H_INCLUDED
#define CLSMENU_H_INCLUDED

#include <iostream>
#include <string>
using namespace std;

class Menu {
    private:

    public:
        Menu();
        void mostrarSeleccionado(string texto, int posX, int posY, bool seleccionado);
        int mostrarMenu(string opciones[], int cantidad, int x, int y);
        void iniciar();
};

#endif // CLSMENU_H_INCLUDED
