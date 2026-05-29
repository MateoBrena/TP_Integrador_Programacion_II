#include <iostream>
#include <string>
#include "rlutil.h"
#include "clsMenu.h"
#include "clsMenuReporte.h"
using namespace std;

menuReporte::menuReporte(){
}

void menuReporte::iniciar(){
    rlutil::hidecursor();
    string opcionesMenu[] = {"Reporte 1", "Reporte 2", "Reporte 3", "Reporte 4", "Reporte 5", "Volver" };
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
        cout << "|      SUBMENU DE REPORTES      |";
        rlutil::locate(posX, posY + 2);
        cout << "================================";
        int opc = m.mostrarMenu(opcionesMenu, cantidadOpciones, posX, posY + 4, anchoMenu);
        system("cls");
        switch(opc){
            case 0:
                //reporte1();
                cout << "Reporte 1";
                break;
            case 1:
                //reporte2();
                cout << "Reporte 2";
                break;
            case 2:
                //reporte3();
                cout << "Reporte 3";
                break;
            case 3:
                //reporte4();
                cout << "Reporte 4";
                break;
            case 4:
                //reporte5();
                cout << "Reporte 5";
                break;
            case 5:
                return;
        }
        system("pause>nul");
    }
}

menuReporte::~menuReporte(){
}
