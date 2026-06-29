#include <iostream>
#include <string>
#include <iomanip>
#include "rlutil.h"
#include "clsMenu.h"
#include "clsMenuVehiculo.h"
#include "clsArchivoVehiculos.h"
#include "clsArchivoMarcas.h"
using namespace std;

menuVehiculo::menuVehiculo(){
}

void menuVehiculo::mostrarCabeceraTabla(int posX, int posY) {
    const int TAM = 9;
    string columnas[TAM] = {"ID","PATENTE","MARCA","MODELO","ANIO","COLOR","KMS","PRECIO","COMBUSTIBLE"};
    int anchos[TAM] = {3,8,14,18,4,12,6,14,12};
    Menu m;
    m.dibujarCabecera(posX, posY, columnas, anchos, TAM);
}

void menuVehiculo::tablaVehiculos(int posX, int posY){
    ArchivoVehiculos arc;
    ArchivoMarcas arc2;
    int cant = arc.contarRegistros();
    if(cant <= 0){
        cout << "No hay vehiculos cargados." << endl;
        return;
    }
    int cantActivos = arc.contarRegistrosActivos(cant);
    if(cantActivos == 0){
        cout << "No hay vehiculos activos cargados." << endl;
        return;
    }
    mostrarCabeceraTabla(posX, posY);
    posY += 3;
    Vehiculo v;
    Marca m;
    Menu me;
    const int TAM = 9;
    int anchos[TAM] = {3,8,14,18,4,12,6,14,12};
    int pM;
    int filasDibujadas = 0;
    for(int i = 0; i < cant; i++){
        v = arc.leerRegistro(i);
        pM = v.getIdMarca()-1;
        m = arc2.leerRegistro(pM);
        if(v.getEstado()){
            filasDibujadas++;
            string columnas[TAM] = {to_string(v.getId()),v.getPatente(),m.getNombre(),v.getModelo(),
            to_string(v.getAnio()),v.getColor(),to_string(v.getKilometros()),v.getPrecioFormato(),v.getCombustible()};
            bool esFin = (filasDibujadas == cantActivos);
            me.dibujarFila(posX, posY, columnas, anchos, TAM, esFin);
        }
    }
}

void menuVehiculo::subMenuBuscarVehiculo(){
    rlutil::hidecursor();
    string opcionesMenu[] = {"Buscar por id","Buscar por patente","Buscar por marca","Buscar por modelo","Buscar por anio",
    "Buscar por color","Buscar por kilometros","Buscar por precio","Buscar por combustible","Buscar por fecha de ingreso",
    "Volver"};
    int anchoMenu = 32;
    int cantidadOpciones = 11;

    int consolaAncho = rlutil::tcols();
    int consolaAlto = rlutil::trows();
    int posX = (consolaAncho - anchoMenu) / 2;
    int posY = (consolaAlto - (cantidadOpciones + 4)) / 2;

    if (posX < 1) posX = 1;
    if (posY < 1) posY = 1;
    Menu m;
    ArchivoVehiculos arc;
    while(true){
        system("cls");
        rlutil::locate(posX, posY);
        cout << "================================";
        rlutil::locate(posX, posY + 1);
        cout << "|       BUSCAR VEHICULOS       |";
        rlutil::locate(posX, posY + 2);
        cout << "================================";
        int opc = m.mostrarMenu(opcionesMenu, cantidadOpciones, posX, posY + 4, anchoMenu);
        system("cls");
        switch(opc){
            case 0:
                arc.buscarPorId();
                break;
            case 1:
                arc.buscarPorPatente();
                break;
            case 2:
                arc.buscarPorMarca();
                break;
            case 3:
                arc.buscarPorModelo();
                break;
            case 4:
                arc.buscarPorAnio();
                break;
            case 5:
                arc.buscarPorColor();
                break;
            case 6:
                arc.buscarPorKilometros();
                break;
            case 7:
                arc.buscarPorPrecio();
                break;
            case 8:
                arc.buscarPorCombustible();
                break;
            case 9:
                arc.buscarPorFechaIngreso();
                break;
            case 10:
                return;
        }
        system("pause>nul");
    }
}

void menuVehiculo::subMenuModificarVehiculo(){
    rlutil::hidecursor();
    string opcionesMenu[] = {"Modificar patente","Modificar marca","Modificar modelo","Modificar anio","Modificar color",
    "Modificar kilometros","Modificar precio","Modificar combustible","Modificar fecha de ingreso","Volver"};
    int anchoMenu = 32;
    int cantidadOpciones = 10;

    int consolaAncho = rlutil::tcols();
    int consolaAlto = rlutil::trows();
    int posX = (consolaAncho - anchoMenu) / 2;
    int posY = (consolaAlto - (cantidadOpciones + 4)) / 2;

    if (posX < 1) posX = 1;
    if (posY < 1) posY = 1;
    Menu m;
    ArchivoVehiculos arc;
    while(true){
        system("cls");
        rlutil::locate(posX, posY);
        cout << "================================";
        rlutil::locate(posX, posY + 1);
        cout << "|      MODIFICAR VEHICULOS     |";
        rlutil::locate(posX, posY + 2);
        cout << "================================";
        int opc = m.mostrarMenu(opcionesMenu, cantidadOpciones, posX, posY + 4, anchoMenu);
        system("cls");
        switch(opc){
            case 0:
                arc.modificarPatente();
                break;
            case 1:
                arc.modificarMarca();
                break;
            case 2:
                arc.modificarModelo();
                break;
            case 3:
                arc.modificarAnio();
                break;
            case 4:
                arc.modificarColor();
                break;
            case 5:
                arc.modificarKilometros();
                break;
            case 6:
                arc.modificarPrecio();
                break;
            case 7:
                arc.modificarCombustible();
                break;
            case 8:
                arc.modificarFechaIngreso();
                break;
            case 9:
                return;
        }
        system("pause>nul");
    }
}

void menuVehiculo::iniciar(){
    rlutil::hidecursor();
    string opcionesMenu[] = {"Alta vehiculo", "Buscar vehiculo", "Listar vehiculos", "Modificar vehiculo", "Baja vehiculo", "Volver" };
    int anchoMenu = 32;
    int cantidadOpciones = 6;

    int consolaAncho = rlutil::tcols();
    int consolaAlto = rlutil::trows();
    int posX = (consolaAncho - anchoMenu) / 2;
    int posY = (consolaAlto - (cantidadOpciones + 4)) / 2;

    if (posX < 1) posX = 1;
    if (posY < 1) posY = 1;
    Menu m;
    ArchivoVehiculos arc;
    while(true){
        system("cls");
        rlutil::locate(posX, posY);
        cout << "================================";
        rlutil::locate(posX, posY + 1);
        cout << "|     SUBMENU DE VEHICULOS     |";
        rlutil::locate(posX, posY + 2);
        cout << "================================";
        int opc = m.mostrarMenu(opcionesMenu, cantidadOpciones, posX, posY + 4, anchoMenu);
        system("cls");
        switch(opc){
            case 0:
                arc.altaVehiculo();
                break;
            case 1:
                subMenuBuscarVehiculo();
                continue;
            case 2:
                tablaVehiculos(1, 2);
                break;
            case 3:
                subMenuModificarVehiculo();
                continue;
            case 4:
                arc.bajaVehiculo();
                break;
            case 5:
                return;
        }
        system("pause>nul");
    }
}

menuVehiculo::~menuVehiculo(){
}
