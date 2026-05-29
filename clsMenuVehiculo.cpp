#include <iostream>
#include <string>
#include "rlutil.h"
#include "clsMenu.h"
#include "clsMenuVehiculo.h"
using namespace std;

menuVehiculo::menuVehiculo(){
}

void menuVehiculo::iniciar(){

    rlutil::hidecursor();
    string opcionesMenu[] = {"Alta vehiculo", "Buscar vehiculo", "Listar vehiculos", "Modificar vehiculo", "Baja vehiculo", "Volver" };
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
        cout << "|     SUBMENU DE VEHICULOS     |";
        rlutil::locate(posX, posY + 2);
        cout << "================================";
        int opc = m.mostrarMenu(opcionesMenu, cantidadOpciones, posX, posY + 4, anchoMenu);
        system("cls");
        switch(opc){
            case 0:
                //altaVehiculo();
                cout << "Alta vehiculo";
                break;
            case 1:
                //buscarVehiculo();
                cout << "Buscar vehiculo";
                break;
            case 2:
                //listarVehiculo();
                cout << "Listado de vehiculos";
                break;
            case 3:
                //modificarVehiculo();
                cout << "Modificar vehiculo";
                break;
            case 4:
                //bajaVehiculo();
                cout << "Baja vehiculo";
                break;
            case 5:
                return;
        }
        system("pause>nul");
    }
}
