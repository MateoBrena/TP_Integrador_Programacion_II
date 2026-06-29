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
        void dibujarCabecera(int posX, int posY, string columnas[], int anchos[], const int cantidadColumnas);
        void dibujarFila(int posX, int& posY, string datos[], int anchos[], const int cantidadColumnas, bool esUltimaFila);
        void iniciar();
        ~Menu();
};

#endif // CLSMENU_H_INCLUDED
