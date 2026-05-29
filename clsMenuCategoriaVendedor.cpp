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
    string opcionesMenu[] = {"Alta categoria", "Buscar categoria", "Listar categorias", "Modificar categoria", "Baja categoria", "Volver" };
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
        cout << "|     SUBMENU DE CATEGORIAS     |";
        rlutil::locate(posX, posY + 2);
        cout << "================================";
        int opc = m.mostrarMenu(opcionesMenu, cantidadOpciones, posX, posY + 4, anchoMenu);
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
