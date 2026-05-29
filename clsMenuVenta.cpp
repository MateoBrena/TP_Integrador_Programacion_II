#include <iostream>
#include <string>
#include "rlutil.h"
#include "clsMenu.h"
#include "clsMenuVenta.h"
using namespace std;

menuVenta::menuVenta(){
}

void menuVenta::iniciar(){

    rlutil::hidecursor();
    string opcionesMenu[] = {"Alta venta", "Buscar venta", "Listar ventas", "Modificar venta", "Baja venta", "Volver"};
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
        cout << "|       SUBMENU DE VENTAS       |";
        rlutil::locate(posX, posY + 2);
        cout << "================================";
        int opc = m.mostrarMenu(opcionesMenu, cantidadOpciones, posX, posY + 4, anchoMenu);
        system("cls");
        switch(opc){
            case 0:
                //altaVenta();
                cout << "Alta venta";
                break;
            case 1:
                //buscarVenta();
                cout << "Buscar venta";
                break;
            case 2:
                //listarVenta();
                cout << "Listado de ventas";
                break;
            case 3:
                //modificarVenta();
                cout << "Modificar venta";
                break;
            case 4:
                //bajaVenta();
                cout << "Baja venta";
                break;
            case 5:
                return;
        }
        system("pause>nul");
    }
}
