#include <iostream>
#include <string>
#include "rlutil.h"
#include "clsMenu.h"
#include "clsMenuCliente.h"
using namespace std;

menuCliente::menuCliente(){
}

void menuCliente::iniciar(){

    rlutil::hidecursor();
    string opcionesMenu[] = {" Alta cliente ", " Buscar cliente ", " Listar clientes ", " Modificar cliente ", " Baja cliente ", " Volver " };
    while(true){
        system("cls");
        cout << "   =====================   " << endl;
        cout << "   |SUBMENU DE CLIENTES|   " << endl;
        cout << "   =====================   " << endl;
        Menu m;
        int opc = m.mostrarMenu(opcionesMenu, 6, 6, 4);
        system("cls");
        switch(opc){
            case 0:
                //altaCliente();
                cout << "Alta cliente";
                break;
            case 1:
                //buscarCliente();
                cout << "Buscar cliente";
                break;
            case 2:
                //listarClientes();
                cout << "Listado de  clientes";
                break;
            case 3:
                //modificarCliente();
                cout << "Modificar clientes";
                break;
            case 4:
                //bajaCliente();
                cout << "Baja cliente";
                break;
            case 5:
                return;
        }
        system("pause>nul");
    }
}
