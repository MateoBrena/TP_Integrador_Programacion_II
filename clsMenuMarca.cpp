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
    rlutil::setColor(rlutil::CYAN);
    rlutil::locate(posX, posY);
    cout << (char)218<<"-----"<<(char)194<<"----------------------"<<(char)194<<"----------------------"<<(char)191;

    rlutil::locate(posX, posY + 1);
    cout << "| " << left << setw(3) << "ID"
         << " | " << setw(20) << "NOMBRE"
         << " | " << setw(20) << "PAIS" << " |";

    rlutil::locate(posX, posY + 2);
    cout <<(char)195<<"-----"<<(char)197<<"----------------------"<<(char)197<<"----------------------|";

    rlutil::setColor(rlutil::WHITE);
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
    int filaActual = posY + 3;
    Marca m;
    for(int i=0; i<cant; i++){
        rlutil::locate(posX, filaActual);
        m = arc.leerRegistro(i);
        if(m.getEstado()){
            cout << "| " << left << setw(3) << m.getId()
            << " | " << setw(20) << m.getNombre()
            << " | " << setw(20) << m.getPais() << " |";
            if(i == cant-1){
                rlutil::locate(posX, filaActual + 1);
                cout <<(char)192<<"-----"<<(char)193<<"----------------------"<<(char)193<<"----------------------"<<(char)217;
            }else{
                rlutil::locate(posX, filaActual + 1);
                cout <<(char)195<<"-----"<<(char)197<<"----------------------"<<(char)197<<"----------------------|";
            }
            filaActual += 2;
        }
    }

}

void menuMarca::subMenuModificarMarca(){
    rlutil::hidecursor();
    string opcionesMenu[] = {"Modificar Nombre", "Modificar Pais" ,"Volver" };
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
                arc.buscarPorId();
                break;
            case 2:
                //arc.listarRegistros();
                tablaMarcas(4,2);
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
