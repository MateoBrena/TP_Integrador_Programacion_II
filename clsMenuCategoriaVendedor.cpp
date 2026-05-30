#include <iostream>
#include <string>
#include <iomanip>
#include "rlutil.h"
#include "clsMenu.h"
#include "clsMenuCategoriaVendedor.h"
#include "clsArchivosCategoriaVendedor.h"
using namespace std;

menuCategoriaVendedor::menuCategoriaVendedor(){
}

void menuCategoriaVendedor::mostrarCabeceraTabla(int posX, int posY) {
    rlutil::setColor(rlutil::CYAN);
    rlutil::locate(posX, posY);
    cout << (char)218<<"-----"<<(char)194<<"----------------------"<<(char)194<<"-----------"<<(char)191;

    rlutil::locate(posX, posY + 1);
    cout << "| " << left << setw(3) << "ID"
         << " | " << setw(20) << "DESCRIPCION"
         << " | " << setw(10) << "COMISION" << " |";

    rlutil::locate(posX, posY + 2);
    cout <<(char)195<<"-----"<<(char)197<<"----------------------"<<(char)197<<"------------|";

    rlutil::setColor(rlutil::WHITE);
}

void menuCategoriaVendedor::tablaCategorias(int posX, int posY){

    ArchivoCategorias arc;
    int cant = arc.contarRegistros();
    if(cant == 0){
        cout << "No hay categorias cargadas." << endl;
        return;
    }
    int cantActivos = arc.contarRegistrosActivos(cant);
    if(cantActivos == 0){
        cout << "No hay categorias activas cargadas." << endl;
        return;
    }
    mostrarCabeceraTabla(posX,posY);
    int filaActual = posY + 3;
    CategoriaVendedor c;
    for(int i=0; i<cant; i++){
        rlutil::locate(posX, filaActual);
        c = arc.leerRegistro(i);
        if(c.getEstado()){
            cout << "| " << left << setw(3) << c.getIdCategoria()
            << " | " << setw(20) << c.getDescripcion()
            << " | " << setw(10) << c.PorcFormato() << " |";
            if(i == cant-1){
                rlutil::locate(posX, filaActual + 1);
                cout <<(char)192<<"-----"<<(char)193<<"----------------------"<<(char)193<<"------------"<<(char)217;
            }else{
                rlutil::locate(posX, filaActual + 1);
                cout <<(char)195<<"-----"<<(char)197<<"----------------------"<<(char)197<<"------------|";
            }
            filaActual += 2;
        }
    }

}

void menuCategoriaVendedor::subMenuModificarCategoria(){
    rlutil::hidecursor();
    string opcionesMenu[] = {"Modificar Descripcion", "Modificar Comision" ,"Volver" };
    int anchoMenu = 32;
    int cantidadOpciones = 3;

    int consolaAncho = rlutil::tcols();
    int consolaAlto = rlutil::trows();
    int posX = (consolaAncho - anchoMenu) / 2;
    int posY = (consolaAlto - (cantidadOpciones + 4)) / 2;

    if (posX < 1) posX = 1;
    if (posY < 1) posY = 1;
    Menu m;
    ArchivoCategorias arc;
    while(true){
        system("cls");
        rlutil::locate(posX, posY);
        cout << "================================";
        rlutil::locate(posX, posY + 1);
        cout << "|     MODIFICAR CATEGORIAS     |";
        rlutil::locate(posX, posY + 2);
        cout << "================================";
        int opc = m.mostrarMenu(opcionesMenu, cantidadOpciones, posX, posY + 4, anchoMenu);
        system("cls");
        switch(opc){
            case 0:
                arc.modificarDescripcion();
                break;
            case 1:
                arc.modificarComision();
                break;
            case 2:
                return;
        }
        system("pause>nul");
    }
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
    ArchivoCategorias arc;
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
                arc.altaCategoria();
                break;
            case 1:
                arc.buscarPorId();
                break;
            case 2:
                tablaCategorias(4,2);
                break;
            case 3:
                subMenuModificarCategoria();
                break;
            case 4:
                arc.bajaCategoria();
                break;
            case 5:
                return;
        }
        system("pause>nul");
    }
}

menuCategoriaVendedor::~menuCategoriaVendedor(){
}
