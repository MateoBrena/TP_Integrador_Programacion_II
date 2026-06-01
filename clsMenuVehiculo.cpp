#include <iostream>
#include <string>
#include <iomanip>
#include "rlutil.h"
#include "clsMenu.h"
#include "clsMenuVehiculo.h"
#include "clsArchivoVehiculos.h"
#include "clsVehiculo.h"
using namespace std;

menuVehiculo::menuVehiculo(){
}

void menuVehiculo::mostrarCabeceraTabla(int posX, int posY) {
    rlutil::setColor(rlutil::CYAN);
    rlutil::locate(posX, posY);
    // Dibujamos la línea superior adaptada al ancho total de las columnas de un vehículo
    cout << (char)218<<"----------"<<(char)194<<"--------"<<(char)194<<"--------------------"<<(char)194;
    cout << "------"<<(char)194<<"--------------------"<<(char)194<<"----------"<<(char)194<<"------------"<<(char)194<<"----------"<<(char)191;

    rlutil::locate(posX, posY + 1);
    cout << "| " << left << setw(8) << "PATENTE"
         << " | " << setw(6) << "MARCA"
         << " | " << setw(18) << "MODELO"
         << " | " << setw(4) << "ANIO"
         << " | " << setw(18) << "COLOR"
         << " | " << setw(8) << "KMS"
         << " | " << setw(10) << "PRECIO"
         << " | " << setw(8) << "NAFTA/DS" << " |";

    rlutil::locate(posX, posY + 2);
    cout << (char)195<<"----------"<<(char)197<<"--------"<<(char)197<<"--------------------"<<(char)197;
    cout << "------"<<(char)197<<"--------------------"<<(char)197<<"----------"<<(char)197<<"------------"<<(char)197<<"----------|";

    rlutil::setColor(rlutil::WHITE);
}

void menuVehiculo::tablaVehiculos(int posX, int posY){
    ArchivoVehiculos arc;
    int cant = arc.contarRegistros();
    if(cant <= 0){
        cout << "No hay vehiculos cargados." << endl;
        return;
    }

    mostrarCabeceraTabla(posX, posY);
    int filaActual = posY + 3;
    Vehiculo v;

    for(int i = 0; i < cant; i++){
        v = arc.leerRegistro(i);
        if(v.getEstado()){
            rlutil::locate(posX, filaActual);
            cout << "| " << left << setw(8) << v.getPatente()
                 << " | Id: " << setw(2) << v.getIdMarca()
                 << " | " << setw(18) << v.getModelo()
                 << " | " << setw(4) << v.getAnio()
                 << " | " << setw(18) << v.getColor()
                 << " | " << setw(8) << v.getKilometros()
                 << " | $" << setw(9) << v.getPrecio()
                 << " | " << setw(8) << v.getCombustible() << " |";

            // Dibujamos el piso del cuadro
            if(i == cant - 1){
                rlutil::locate(posX, filaActual + 1);
                cout << (char)192<<"----------"<<(char)193<<"--------"<<(char)193<<"--------------------"<<(char)193;
                cout << "------"<<(char)193<<"--------------------"<<(char)193<<"----------"<<(char)193<<"------------"<<(char)193<<"----------"<<(char)217;
            } else {
                rlutil::locate(posX, filaActual + 1);
                cout << (char)195<<"----------"<<(char)197<<"--------"<<(char)197<<"--------------------"<<(char)197;
                cout << "------"<<(char)197<<"--------------------"<<(char)197<<"----------"<<(char)197<<"------------"<<(char)197<<"----------|";
            }
            filaActual += 2;
        }
    }
}

void menuVehiculo::subMenuModificarVehiculo(){
    rlutil::hidecursor();
    string opcionesMenu[] = {
        "Modificar Marca",
        "Modificar Modelo",
        "Modificar Anio",
        "Modificar Color",
        "Modificar Kilometros",
        "Modificar Precio",
        "Modificar Combustible",
        "Modificar Fecha Ingreso",
        "Volver"
    };
    int anchoMenu = 32;
    int cantidadOpciones = 9;

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
                arc.modificarMarca();
                break;
            case 1:
                arc.modificarModelo();
                break;
            case 2:
                arc.modificarAnio();
                break;
            case 3:
                arc.modificarColor();
                break;
            case 4:
                arc.modificarKilometros();
                break;
            case 5:
                arc.modificarPrecio();
                break;
            case 6:
                arc.modificarCombustible();
                break;
            case 7:
                arc.modificarFechaIngreso();
                break;
            case 8:
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
        cout << "|      SUBMENU DE VEHICULOS    |";
        rlutil::locate(posX, posY + 2);
        cout << "================================";
        int opc = m.mostrarMenu(opcionesMenu, cantidadOpciones, posX, posY + 4, anchoMenu);
        system("cls");
        switch(opc){
            case 0:
                arc.altaVehiculo();
                continue;
            case 1:
                arc.buscarPorPatente();
                break;
            case 2:
                tablaVehiculos(2, 2);
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
