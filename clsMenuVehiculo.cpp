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
    rlutil::setColor(rlutil::CYAN);
    rlutil::locate(posX, posY);

    cout << (char)218<<"-----"<<(char)194<<"----------"<<(char)194<<"--------------"<<(char)194<<"--------------------"<<(char)194;
    cout << "------"<<(char)194<<"----------------"<<(char)194<<"--------"<<(char)194<<"--------------"<<(char)194<<"--------------"<<(char)191;

    rlutil::locate(posX, posY + 1);
    cout << "| " << left << setw(3) << "ID"
        << " | " << setw(8) << "PATENTE"
        << " | " << setw(12) << "MARCA"
        << " | " << setw(18) << "MODELO"
        << " | " << setw(4) << "ANIO"
        << " | " << setw(14) << "COLOR"
        << " | " << setw(6) << "KMS"
        << " | " << setw(12) << "PRECIO"
        << " | " << setw(12) << "COMBUSTIBLE" << " |";

    rlutil::locate(posX, posY + 2);
    cout << (char)195<<"-----"<<(char)197<<"----------"<<(char)197<<"--------------"<<(char)197<<"--------------------"<<(char)197;
    cout << "------"<<(char)197<<"----------------"<<(char)197<<"--------"<<(char)197<<"--------------"<<(char)197<<"--------------|";
    rlutil::setColor(rlutil::WHITE);
}

void menuVehiculo::tablaVehiculos(int posX, int posY){
    ArchivoVehiculos arc;
    ArchivoMarcas arc2;
    int cant = arc.contarRegistros();
    if(cant <= 0){
        cout << "No hay vehiculos cargados." << endl;
        return;
    }
    mostrarCabeceraTabla(posX, posY);
    int filaActual = posY + 3;
    Vehiculo v;
    Marca m;
    int pM;
    cout << fixed << setprecision(2);
    for(int i = 0; i < cant; i++){
        v = arc.leerRegistro(i);
        pM = v.getIdMarca()-1;
        m = arc2.leerRegistro(pM);
        if(v.getEstado()){
            rlutil::locate(posX, filaActual);
            cout << "| " << left << setw(3) << v.getId()
                << " | " << setw(8) << v.getPatente()
                << " | " << setw(12) << m.getNombre()
                << " | " << setw(18) << v.getModelo()
                << " | " << setw(4) << v.getAnio()
                << " | " << setw(14) << v.getColor()
                << " | " << setw(6) << v.getKilometros()
                << " | $" << setw(11) << v.getPrecio()
                << " | " << setw(12) << v.getCombustible() << " |";

            if(i == cant - 1){
                rlutil::locate(posX, filaActual + 1);
                cout << (char)192<<"-----"<<(char)193<<"----------"<<(char)193<<"--------------"<<(char)193<<"--------------------"<<(char)193;
                cout << "------"<<(char)193<<"----------------"<<(char)193<<"--------"<<(char)193<<"--------------"<<(char)193<<"--------------"<<(char)217;
            } else {
                rlutil::locate(posX, filaActual + 1);
                cout << (char)195<<"-----"<<(char)197<<"----------"<<(char)197<<"--------------"<<(char)197<<"--------------------"<<(char)197;
                cout << "------"<<(char)197<<"----------------"<<(char)197<<"--------"<<(char)197<<"--------------"<<(char)197<<"--------------|";
            }
            filaActual += 2;
        }
    }
}

void menuVehiculo::subMenuModificarVehiculo(){
    rlutil::hidecursor();
    string opcionesMenu[] = {
        "Modificar Patente",
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
