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
    string opcionesMenu[] = {" Alta marca ", " Buscar marca ", " Listar marcas ", " Modificar marca ", " Baja marca ", " Volver " };
    while(true){
        system("cls");
        cout << "   =======================   " << endl;
        cout << "   |  SUBMENU DE MARCAS  |   " << endl;
        cout << "   =======================   " << endl;
        Menu m;
        int opc = m.mostrarMenu(opcionesMenu, 6, 6, 4);
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
