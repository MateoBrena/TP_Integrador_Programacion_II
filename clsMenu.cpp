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

void Menu::mostrarSeleccionado(string texto, int posX, int posY, bool seleccionado, int anchoMenu){
    // Calculamos los espacios necesarios para que toda la fila mida exactamente 'anchoMenu'
    int espaciosLibres = anchoMenu - texto.length();
    int padIzq = espaciosLibres / 2;
    int padDer = espaciosLibres - padIzq;

    rlutil::locate(posX, posY);

    if(seleccionado){
        rlutil::setBackgroundColor(rlutil::WHITE);
        rlutil::setColor(rlutil::BLACK);

        // Descontamos 2 caracteres en el padding para acomodar la flecha y un espacio
        string paddingIzq(padIzq - 2, ' ');
        string paddingDer(padDer - 2, ' ');

        cout << paddingIzq << (char)175 << " " << texto << " " << (char)174 << paddingDer;
    } else {
        rlutil::setBackgroundColor(rlutil::BLACK);
        rlutil::setColor(rlutil::GREY);

        string paddingIzq(padIzq, ' ');
        string paddingDer(padDer, ' ');

        cout << paddingIzq << texto << paddingDer;
    }

    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil::setColor(rlutil::GREY);
}

int Menu::mostrarMenu(string opciones[], int cantidad, int x, int y, int anchoMenu){
    int pos = 0;
    int tecla;

    while (true) {

        for (int i = 0; i < cantidad; i++) {
            mostrarSeleccionado(opciones[i], x, y + i, (i == pos), anchoMenu);
        }

        tecla = rlutil::getkey();

        switch (tecla) {
            case 119: // w
            case 14:  // flecha arriba
                pos--;
                if (pos < 0) pos = cantidad - 1;
                break;

            case 115: // s
            case 15:  // flecha abajo
                pos++;
                if (pos >= cantidad) pos = 0;
                break;

            case 1: // ENTER
                return pos;
        }
    }
}

void Menu::iniciar(){
    rlutil::hidecursor();

    string opcionesMenu[] = {"Clientes", "Vendedores", "Categorias", "Marcas", "Vehiculos", "Ventas", "Reportes", "Salir"};
    int anchoMenu = 32;
    int cantidadOpciones = 8;

    // Cálculo dinámico para centrar en pantalla
    int consolaAncho = rlutil::tcols();
    int consolaAlto = rlutil::trows();
    int posX = (consolaAncho - anchoMenu) / 2;
    int posY = (consolaAlto - (cantidadOpciones + 4)) / 2; // +4 por las líneas del título

    // Preventivo: si la consola es muy chica, no imprimir en coordenadas negativas
    if (posX < 1) posX = 1;
    if (posY < 1) posY = 1;

    menuCliente mC;
    menuVendedor mV;
    menuCategoriaVendedor mCV;
    menuMarca mM;
    menuVehiculo mVh;
    menuVenta mVe;
    menuReporte mR;

    while(true){
        rlutil::setBackgroundColor(rlutil::BLACK);
        system("cls");
        // Imprimimos el título utilizando la coordenada X calculada
        rlutil::locate(posX, posY);
        cout << "================================";
        rlutil::locate(posX, posY + 1);
        cout << "|        MENU PRINCIPAL        |";
        rlutil::locate(posX, posY + 2);
        cout << "================================";
        // Llamamos al menú pasándole la posición ajustada (debajo del título) y el ancho
        int opc = mostrarMenu(opcionesMenu, cantidadOpciones, posX, posY + 4, anchoMenu);

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
