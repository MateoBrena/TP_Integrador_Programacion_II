#include <iostream>
#include <string>
#include <iomanip>
#include "rlutil.h"
#include "clsMenu.h"
#include "clsMenuMarca.h"
#include "clsArchivoMarcas.h"
using namespace std;

menuMarca::menuMarca(){
}

void menuMarca::mostrarCabeceraTabla(int posX, int posY) {
    const int TAM = 3;
    string columnas[TAM] = {"ID","NOMBRE","PAIS"};
    int anchos[TAM] = {3,20,20};
    Menu m;
    m.dibujarCabecera(posX, posY, columnas, anchos, TAM);
}

void menuMarca::tablaMarcas(int posX, int posY){

    ArchivoMarcas arc;
    int cant = arc.contarRegistros();
    if(cant == 0){
        cout << "No hay marcas cargadas." << endl;
        return;
    }
    int cantActivos = arc.contarRegistrosActivos(cant);
    if(cantActivos == 0){
        cout << "No hay marcas activas cargadas." << endl;
        return;
    }
    mostrarCabeceraTabla(posX,posY);
    posY += 3;
    Marca m;
    Menu me;
    const int TAM = 3;
    int anchos[TAM] = {3,20,20};
    int filasDibujadas = 0;
    for(int i=0; i<cant; i++){
        m = arc.leerRegistro(i);
        if(m.getEstado()){
            filasDibujadas++;
            string columnas[TAM] = {to_string(m.getId()),m.getNombre(),m.getPais()};
            bool esFin = (filasDibujadas == cantActivos);
            me.dibujarFila(posX, posY, columnas, anchos, TAM, esFin);
        }
    }
}

void menuMarca::subMenuBuscarMarca(){
    rlutil::hidecursor();
    string opcionesMenu[] = {"Buscar por ID", "Buscar por nombre", "Buscar por pais" ,"Volver" };
    int anchoMenu = 32;
    int cantidadOpciones = 4;

    int consolaAncho = rlutil::tcols();
    int consolaAlto = rlutil::trows();
    int posX = (consolaAncho - anchoMenu) / 2;
    int posY = (consolaAlto - (cantidadOpciones + 4)) / 2;

    if (posX < 1) posX = 1;
    if (posY < 1) posY = 1;
    Menu m;
    ArchivoMarcas arc;
    while(true){
        system("cls");
        rlutil::locate(posX, posY);
        cout << "================================";
        rlutil::locate(posX, posY + 1);
        cout << "|         BUSCAR MARCAS        |";
        rlutil::locate(posX, posY + 2);
        cout << "================================";
        int opc = m.mostrarMenu(opcionesMenu, cantidadOpciones, posX, posY + 4, anchoMenu);
        system("cls");
        switch(opc){
            case 0:
                arc.buscarPorId();
                break;
            case 1:
                arc.buscarPorNombre();
                break;
            case 2:
                arc.buscarPorPais();
                break;
            case 3:
                return;
                break;
        }
        system("pause>nul");
    }
}

void menuMarca::subMenuModificarMarca(){
    rlutil::hidecursor();
    string opcionesMenu[] = {"Modificar Nombre", "Modificar Pais", "Volver" };
    int anchoMenu = 32;
    int cantidadOpciones = 3;

    int consolaAncho = rlutil::tcols();
    int consolaAlto = rlutil::trows();
    int posX = (consolaAncho - anchoMenu) / 2;
    int posY = (consolaAlto - (cantidadOpciones + 4)) / 2;

    if (posX < 1) posX = 1;
    if (posY < 1) posY = 1;
    Menu m;
    ArchivoMarcas arc;
    while(true){
        system("cls");
        rlutil::locate(posX, posY);
        cout << "================================";
        rlutil::locate(posX, posY + 1);
        cout << "|       MODIFICAR MARCAS       |";
        rlutil::locate(posX, posY + 2);
        cout << "================================";
        int opc = m.mostrarMenu(opcionesMenu, cantidadOpciones, posX, posY + 4, anchoMenu);
        system("cls");
        switch(opc){
            case 0:
                arc.modificarNombre();
                break;
            case 1:
                arc.modificarPais();
                break;
            case 2:
                return;
        }
        system("pause>nul");
    }
}

void menuMarca::iniciar(){

    rlutil::hidecursor();
    string opcionesMenu[] = {"Alta marca", "Buscar marca", "Listar marcas", "Modificar marca", "Baja marca", "Volver"};
    int anchoMenu = 32;
    int cantidadOpciones = 6;

    int consolaAncho = rlutil::tcols();
    int consolaAlto = rlutil::trows();
    int posX = (consolaAncho - anchoMenu) / 2;
    int posY = (consolaAlto - (cantidadOpciones + 4)) / 2;

    if (posX < 1) posX = 1;
    if (posY < 1) posY = 1;
    Menu m;
    ArchivoMarcas arc;
    while(true){
        system("cls");
        rlutil::locate(posX, posY);
        cout << "================================";
        rlutil::locate(posX, posY + 1);
        cout << "|       SUBMENU DE MARCAS      |";
        rlutil::locate(posX, posY + 2);
        cout << "================================";
        int opc = m.mostrarMenu(opcionesMenu, cantidadOpciones, posX, posY + 4, anchoMenu);
        system("cls");
        switch(opc){
            case 0:
                arc.altaMarca();
                break;
            case 1:
                subMenuBuscarMarca();
                continue;
            case 2:
                tablaMarcas(1,2);
                break;
            case 3:
                subMenuModificarMarca();
                continue;
            case 4:
                arc.bajaMarca();
                break;
            case 5:
                return;
        }
        system("pause>nul");
    }
}

menuMarca::~menuMarca(){
}
