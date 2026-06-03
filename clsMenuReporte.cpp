#include <iostream>
#include <string>
#include "rlutil.h"
#include "clsMenu.h"
#include "clsMenuReporte.h"
#include "clsReporte.h"
using namespace std;

/*  1-Cliente que más compró (puede ser en cantidad de autos o monto en $)
    2-Cantidad de vendedores que no tuvieron ventas en un mes y año que se ingresa por teclado.
    3-Vendedor que más cobró (ventas x porc.comisión)
    4-Marca más vendida. (unidades)
    5-Monto total de ventas por cada mes (entre todos los años)
*/

menuReporte::menuReporte(){
}

void menuReporte::iniciar(){
    rlutil::hidecursor();
    string opcionesMenu[] = {"Mayor cliente por unidades", "Mayor cliente por monto", "Vendedores sin ventas", "Mayor vendedor",
     "Marca mas vendida", "Ventas por mes", "Volver" };
    int anchoMenu = 32;
    int cantidadOpciones = 7;

    int consolaAncho = rlutil::tcols();
    int consolaAlto = rlutil::trows();
    int posX = (consolaAncho - anchoMenu) / 2;
    int posY = (consolaAlto - (cantidadOpciones + 4)) / 2;

    if (posX < 1) posX = 1;
    if (posY < 1) posY = 1;
    Menu m;
    Reporte r;
    while(true){
        system("cls");
        rlutil::locate(posX, posY);
        cout << "================================";
        rlutil::locate(posX, posY + 1);
        cout << "|      SUBMENU DE REPORTES     |";
        rlutil::locate(posX, posY + 2);
        cout << "================================";
        int opc = m.mostrarMenu(opcionesMenu, cantidadOpciones, posX, posY + 4, anchoMenu);
        system("cls");
        switch(opc){
            case 0:
                r.clienteMasComproUnidades();
                break;
            case 1:
                r.clienteMasComproMonto();
                break;
            case 2:
                r.cantVendedoresSinventas();
                break;
            case 3:
                r.mayorVendedor();
                break;
            case 4:
                r.marcaMasVendida();
                break;
            case 5:
                r.ventasxMes();
                break;
            case 6:
                return;
        }
        system("pause>nul");
    }
}

menuReporte::~menuReporte(){
}
