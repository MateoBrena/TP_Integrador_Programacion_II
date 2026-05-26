#include <iostream>
#include <string>
#include "rlutil.h"
#include "clsMenu.h"
#include "clsMenuCategoriaVendedor.h"
using namespace std;

menuCategoriaVendedor::menuCategoriaVendedor(){
}

void menuCategoriaVendedor::iniciar(){

    rlutil::hidecursor();
    string opcionesMenu[] = {" Alta categoria ", " Buscar categoria ", " Listar categorias ", " Modificar categoria ", " Baja categoria ", " Volver " };
    while(true){
        system("cls");
        cout << "   ======================   " << endl;
        cout << "   |SUBMENU DE CATEGORIAS|   " << endl;
        cout << "   ======================   " << endl;
        Menu m;
        int opc = m.mostrarMenu(opcionesMenu, 6, 6, 4);
        system("cls");
        switch(opc){
            case 0:
                //altaCategoria();
                cout << "Alta categoria";
                break;
            case 1:
                //buscarCategoria();
                cout << "Buscar categoria";
                break;
            case 2:
                //listarCategorias();
                cout << "Listado de categorias";
                break;
            case 3:
                //modificarCategoria();
                cout << "Modificar categoria";
                break;
            case 4:
                //bajaCategoria();
                cout << "Baja categoria";
                break;
            case 5:
                return;
        }
        system("pause>nul");
    }
}
