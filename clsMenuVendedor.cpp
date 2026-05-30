#include <iostream>
#include <string>
#include "rlutil.h"
#include "clsMenu.h"
#include "clsMenuVendedor.h"
#include "clsArchivosVendedores.h"
using namespace std;

menuVendedor::menuVendedor(){
}

void menuVendedor::iniciar(){
    rlutil::hidecursor();
    string opcionesMenu[] = {"Alta vendedor", "Buscar vendedor", "Listar vendedores", "Modificar vendedor", "Baja vendedor", "Volver"};
    int anchoMenu = 32;
    int cantidadOpciones = 6;

    int consolaAncho = rlutil::tcols();
    int consolaAlto = rlutil::trows();
    int posX = (consolaAncho - anchoMenu) / 2;
    int posY = (consolaAlto - (cantidadOpciones + 4)) / 2;

    if (posX < 1) posX = 1;
    if (posY < 1) posY = 1;
    Menu m;
    ArchivoVendedores arc;
    while(true){
        system("cls");
        rlutil::locate(posX, posY);
        cout << "================================";
        rlutil::locate(posX, posY + 1);
        cout << "|     SUBMENU DE VENDEDORES     |";
        rlutil::locate(posX, posY + 2);
        cout << "================================";
        int opc = m.mostrarMenu(opcionesMenu, cantidadOpciones, posX, posY + 4, anchoMenu);
        system("cls");
        switch(opc){
            case 0:
                arc.altaVendedor();
                break;
            case 1:
                arc.buscarPorDni();
                break;
            case 2:
                arc.listarRegistros();
                break;
            case 3:
                //modificarVendedor();
                cout << "Modificar vendedor";
                break;
            case 4:
                arc.bajaVendedor();
                break;
            case 5:
                return;
        }
        system("pause>nul");
    }
}

menuVendedor::~menuVendedor(){
}
