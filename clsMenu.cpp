#include <iostream>
#include "rlutil.h"
#include <string>
#include "clsMenu.h"
#include "clsMenuCliente.h"
#include "clsMenuVendedor.h"
#include "clsMenuCategoriaVendedor.h"
#include "clsMenuMarca.h"
#include "clsMenuVehiculo.h"
#include "clsMenuVenta.h"
#include "clsMenuReporte.h"
using namespace std;

Menu::Menu(){

}

void Menu::mostrarSeleccionado(string texto, int posX, int posY, bool seleccionado){

    if(seleccionado){
        rlutil::setBackgroundColor(rlutil::WHITE);
        rlutil::setColor(rlutil::BLACK);
        rlutil::locate(posX-2, posY);
        cout << (char)175 << "  " << texto << "  " << (char)174 << endl;
    }else{
        rlutil::setBackgroundColor(rlutil::BLACK);
        rlutil::setColor(rlutil::GREY);
        rlutil::locate(posX-2, posY);
        cout << "   " << texto << "   " << endl;
    }

    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil::setColor(rlutil::GREY);
}

int Menu::mostrarMenu(string opciones[], int cantidad, int x, int y){

    int pos = 0;
    int tecla;
    while (true) {

        rlutil::locate(x,y);

        // Mostrar opciones
        for (int i = 0; i < cantidad; i++) {
            if (i == pos) {
                mostrarSeleccionado(opciones[i], x, y + i, true);
            } else {
                mostrarSeleccionado(opciones[i], x, y + i, false);
            }
        }

        tecla = rlutil::getkey();

        switch (tecla) {
            case 119: //arriba
                pos--;
                if (pos < 0) pos = cantidad - 1;
                break;

            case 115: //abajo
                pos++;
                if (pos >= cantidad) pos = 0;
                break;

            case 1: // ENTER
                return pos;   // devuelve el índice seleccionado
        }
    }
}


void Menu::iniciar(){
    rlutil::hidecursor();
    string opcionesMenu[] = {" Clientes ", " Vendedores ", " Categorias ", " Marcas ", " Vehiculos ", " Ventas ", " Reportes ", " Salir " };
    menuCliente mC;
    menuVendedor mV;
    menuCategoriaVendedor mCV;
    menuMarca mM;
    menuVehiculo mVh;
    menuVenta mVe;
    menuReporte mR;
    while(true){
        system("cls");
        cout << "   ======================  " << endl;
        cout << "   |   MENU PRINCIPAL   |  " << endl;
        cout << "   ======================  " << endl;
        int opc = mostrarMenu(opcionesMenu, 8, 6, 4);
        system("cls");
        switch(opc){
            case 0:
                mC.iniciar();
                break;
            case 1:
                mV.iniciar();
                break;
            case 2:
                mCV.iniciar();
                break;
            case 3:
                mM.iniciar();
                break;
            case 4:
                mVh.iniciar();
                break;
            case 5:
                mVe.iniciar();
                break;
            case 6:
                mR.iniciar();
                break;
            case 7:
                return;
        }
    }
}
