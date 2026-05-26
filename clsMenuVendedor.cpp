#include <iostream>
#include <string>
#include "rlutil.h"
#include "clsMenu.h"
#include "clsMenuVendedor.h"
using namespace std;

menuVendedor::menuVendedor(){
}

void menuVendedor::iniciar(){

    rlutil::hidecursor();
    string opcionesMenu[] = {" Alta vendedor ", " Buscar vendedor ", " Listar vendedores ", " Modificar vendedor ", " Baja vendedor ", " Volver " };
    while(true){
        system("cls");
        cout << "   =======================   " << endl;
        cout << "   |SUBMENU DE VENDEDORES|   " << endl;
        cout << "   =======================   " << endl;
        Menu m;
        int opc = m.mostrarMenu(opcionesMenu, 6, 6, 4);
        system("cls");
        switch(opc){
            case 0:
                //altaVendedor();
                cout << "Alta vendedor";
                break;
            case 1:
                //buscarVendedor();
                cout << "Buscar vendedor";
                break;
            case 2:
                //listarVendedor();
                cout << "Listado de vendedores";
                break;
            case 3:
                //modificarVendedor();
                cout << "Modificar vendedor";
                break;
            case 4:
                //bajaVendedor();
                cout << "Baja vendedor";
                break;
            case 5:
                return;
        }
        system("pause>nul");
    }
}
