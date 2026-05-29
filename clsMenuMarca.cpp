#include <iostream>
#include <string>
#include "rlutil.h"
#include "clsMenu.h"
#include "clsMenuMarca.h"
using namespace std;

menuMarca::menuMarca(){
}

void menuMarca::iniciar(){

    rlutil::hidecursor();
    string opcionesMenu[] = {"Alta marca", "Buscar marca", "Listar marcas", "Modificar marca", "Baja marca", "Volver"};
    int anchoMenu = 32;
    int cantidadOpciones = 6;

    int consolaAncho = rlutil::tcols();
    int consolaAlto = rlutil::trows();
    int posX = (consolaAncho - anchoMenu) / 2;
    int posY = (consolaAlto - (cantidadOpciones + 4)) / 2;

    if (posX < 1) posX = 1;
    if (posY < 1) posY = 1;
    Menu m;
    while(true){
        system("cls");
        rlutil::locate(posX, posY);
        cout << "================================";
        rlutil::locate(posX, posY + 1);
        cout << "|       SUBMENU DE MARCAS       |";
        rlutil::locate(posX, posY + 2);
        cout << "================================";
        int opc = m.mostrarMenu(opcionesMenu, cantidadOpciones, posX, posY + 4, anchoMenu);
        system("cls");
        switch(opc){
            case 0:
                //altaMarca();
                cout << "Alta marca";
                break;
            case 1:
                //buscarMarca();
                cout << "Buscar marca";
                break;
            case 2:
                //listarMarca();
                cout << "Listado de marcas";
                break;
            case 3:
                //modificarMarca();
                cout << "Modificar marca";
                break;
            case 4:
                //bajaMarca();
                cout << "Baja marca";
                break;
            case 5:
                return;
        }
        system("pause>nul");
    }
}
