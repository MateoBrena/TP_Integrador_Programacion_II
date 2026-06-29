#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include "rlutil.h"
#include "clsMenu.h"
#include "clsMenuCategoriaVendedor.h"
#include "clsArchivosCategoriaVendedor.h"
using namespace std;

menuCategoriaVendedor::menuCategoriaVendedor(){
}

void menuCategoriaVendedor::mostrarCabeceraTabla(int posX, int posY) {
    const int TAM = 3;
    string columnas[TAM] = {"ID","DESCRIPCION","COMISION"};
    int anchos[TAM] = {3,20,10};
    Menu m;
    m.dibujarCabecera(posX, posY, columnas, anchos, TAM);
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
    posY += 3;
    Menu m;
    CategoriaVendedor c;
    const int TAM = 3;
    int anchos[TAM] = {3,20,10};
    int filasDibujadas = 0;
    for(int i=0; i<cant; i++){
        c = arc.leerRegistro(i);
        stringstream porcFormato;
        porcFormato << fixed << setprecision(2) << c.getPorcentajeComision() << "%";
        if(c.getEstado()){
            filasDibujadas++;
            string columnas[TAM] = {to_string(c.getIdCategoria()),c.getDescripcion(),porcFormato.str()};
            bool esFin = (filasDibujadas == cantActivos);
            m.dibujarFila(posX, posY, columnas, anchos, TAM, esFin);
        }
    }
}

void menuCategoriaVendedor::subMenuBuscarCategoria(){
    rlutil::hidecursor();
    string opcionesMenu[] = {"Buscar por ID", "Buscar por nombre", "Buscar por comision" ,"Volver" };
    int anchoMenu = 32;
    int cantidadOpciones = 4;

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
        cout << "|       BUSCAR CATEGORIAS      |";
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
                arc.buscarPorComision();
                break;
            case 3:
                return;
                break;
        }
        system("pause>nul");
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
        cout << "|     SUBMENU DE CATEGORIAS    |";
        rlutil::locate(posX, posY + 2);
        cout << "================================";
        int opc = m.mostrarMenu(opcionesMenu, cantidadOpciones, posX, posY + 4, anchoMenu);
        system("cls");
        switch(opc){
            case 0:
                arc.altaCategoria();
                break;
            case 1:
                subMenuBuscarCategoria();
                continue;
            case 2:
                tablaCategorias(1,2);
                break;
            case 3:
                subMenuModificarCategoria();
                continue;
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
