#ifndef CLSMENU_H_INCLUDED
#define CLSMENU_H_INCLUDED

#include <iostream>
#include <string>
using namespace std;

class Menu {
    public:
        Menu();
        void mostrarSeleccionado(string texto, int posX, int posY, bool seleccionado, int anchoMenu);
        int mostrarMenu(string opciones[], int cantidad, int x, int y, int anchoMenu);
        void iniciar();
};

#endif // CLSMENU_H_INCLUDED
