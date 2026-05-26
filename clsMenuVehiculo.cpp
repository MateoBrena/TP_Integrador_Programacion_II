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
    string opcionesMenu[] = {" Alta vehiculo ", " Buscar vehiculo ", " Listar vehiculos ", " Modificar vehiculo ", " Baja vehiculo ", " Volver " };
    while(true){
        system("cls");
        cout << "   =======================   " << endl;
        cout << "   |SUBMENU DE VEHICULOS |   " << endl;
        cout << "   =======================   " << endl;
        Menu m;
        int opc = m.mostrarMenu(opcionesMenu, 6, 6, 4);
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
