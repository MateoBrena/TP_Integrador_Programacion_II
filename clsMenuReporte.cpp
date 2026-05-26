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
    string opcionesMenu[] = {" Reporte 1 ", " Reporte 2 ", " Reporte 3 ", " Reporte 4 ", " Reporte 5 ", " Volver " };
    while(true){
        system("cls");
        cout << "   =========================   " << endl;
        cout << "   |  SUBMENU DE REPORTES  |   " << endl;
        cout << "   =========================   " << endl;
        Menu m;
        int opc = m.mostrarMenu(opcionesMenu, 6, 6, 4);
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
