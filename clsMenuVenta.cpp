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
    string opcionesMenu[] = {" Alta venta ", " Buscar venta ", " Listar ventas ", " Modificar venta ", " Baja venta ", " Volver " };
    while(true){
        system("cls");
        cout << "   ========================   " << endl;
        cout << "   |   SUBMENU DE VENTAS  |   " << endl;
        cout << "   ========================   " << endl;
        Menu m;
        int opc = m.mostrarMenu(opcionesMenu, 6, 6, 4);
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
