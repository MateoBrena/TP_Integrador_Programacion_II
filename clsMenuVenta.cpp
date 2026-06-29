#include <iostream>
#include <string>
#include <iomanip>
#include "rlutil.h"
#include "clsMenu.h"
#include "clsMenuVenta.h"
#include "clsArchivoVentas.h"
#include "clsArchivoClientes.h"
#include "clsArchivoVehiculos.h"
#include "clsArchivoMarcas.h"
using namespace std;

menuVenta::menuVenta(){
}

void menuVenta::mostrarCabeceraTabla(int posX, int posY){
    const int TAM = 7;
    string columnas[TAM] = {"ID","FECHA","CUIT","NRO VEND","PATENTE","MARCA","MONTO"};
    int anchos[TAM] = {2,10,14,10,8,16,12};
    Menu m;
    m.dibujarCabecera(posX, posY, columnas, anchos, TAM);
}

void menuVenta::tablaVentas(int posX, int posY){
    ArchivoVentas arc;
    int cant = arc.contarRegistros();
    if(cant == 0){
        cout << "No hay ventas cargadas." << endl;
        return;
    }
    int cantActivos = arc.contarRegistrosActivos(cant);
    if(cantActivos == 0){
        cout << "No hay ventas activas cargadas." << endl;
        return;
    }
    mostrarCabeceraTabla(posX,posY);
    posY += 3;
    Venta v;
    ArchivoClientes arcCli;
    ArchivoVehiculos arcVeh;
    ArchivoMarcas arcMar;
    Cliente c;
    Vehiculo veh;
    Marca m;
    Menu me;
    const int TAM = 7;
    int anchos[TAM] = {2,10,14,10,8,16,12};
    int filasDibujadas = 0;
    for(int i=0; i<cant; i++){
        v = arc.leerRegistro(i);
        c = arcCli.leerRegistro(v.getNroCliente()-1);
        veh = arcVeh.leerRegistro(v.getNroVehiculo()-1);
        m = arcMar.leerRegistro(v.getIdMarcaVehiculo()-1);
        if(v.getEstado()){
            filasDibujadas++;
            string columnas[TAM] ={to_string(v.getNroVenta()), v.getFechaVenta().mostrarFechaFormato(), c.getCuit(),
            to_string(v.getNroVendedor()), veh.getPatente(), m.getNombre(), v.getMontoFormato()};
            bool esFin = (filasDibujadas == cantActivos);
            me.dibujarFila(posX, posY, columnas, anchos, TAM, esFin);
        }
    }
}

void menuVenta::subMenuBuscarVenta(){
    rlutil::hidecursor();
    string opcionesMenu[] = {"Buscar por id", "Buscar por fecha", "Buscar por id cliente" ,"Buscar por id vendedor",
    "Buscar por id vehiculo", "Buscar por marca", "Buscar por monto", "Volver" };
    int anchoMenu = 32;
    int cantidadOpciones = 8;

    int consolaAncho = rlutil::tcols();
    int consolaAlto = rlutil::trows();
    int posX = (consolaAncho - anchoMenu) / 2;
    int posY = (consolaAlto - (cantidadOpciones + 4)) / 2;

    if (posX < 1) posX = 1;
    if (posY < 1) posY = 1;
    Menu m;
    ArchivoVentas arc;
    while(true){
        system("cls");
        rlutil::locate(posX, posY);
        cout << "================================";
        rlutil::locate(posX, posY + 1);
        cout << "|         BUSCAR VENTAS        |";
        rlutil::locate(posX, posY + 2);
        cout << "================================";
        int opc = m.mostrarMenu(opcionesMenu, cantidadOpciones, posX, posY + 4, anchoMenu);
        system("cls");
        switch(opc){
            case 0:
                arc.buscarPorId();
                break;
            case 1:
                arc.buscarPorFecha();
                break;
            case 2:
                arc.buscarPorCliente();
                break;
            case 3:
                arc.buscarPorVendedor();
                break;
            case 4:
                arc.buscarPorVehiculo();
                break;
            case 5:
                arc.buscarPorMarca();
                break;
            case 6:
                arc.buscarPorMonto();
                break;
            case 7:
                return;
        }
        system("pause>nul");
    }
}

void menuVenta::subMenuModificarVenta(){
    rlutil::hidecursor();
    string opcionesMenu[] = {"Modificar fecha", "Modificar ID cliente", "Modificar ID vendedor", "Modificar ID vehiculo", "Volver"};
    int anchoMenu = 32;
    int cantidadOpciones = 5;

    int consolaAncho = rlutil::tcols();
    int consolaAlto = rlutil::trows();
    int posX = (consolaAncho - anchoMenu) / 2;
    int posY = (consolaAlto - (cantidadOpciones + 4)) / 2;

    if (posX < 1) posX = 1;
    if (posY < 1) posY = 1;
    Menu m;
    ArchivoVentas arc;
    while(true){
        system("cls");
        rlutil::locate(posX, posY);
        cout << "================================";
        rlutil::locate(posX, posY + 1);
        cout << "|       MODIFICAR VENTAS       |";
        rlutil::locate(posX, posY + 2);
        cout << "================================";
        int opc = m.mostrarMenu(opcionesMenu, cantidadOpciones, posX, posY + 4, anchoMenu);
        system("cls");
        switch(opc){
            case 0:
                arc.modificarFechaVenta();
                break;
            case 1:
                arc.modificarNroCliente();
                break;
            case 2:
                arc.modificarNroVendedor();
                break;
            case 3:
                arc.modificarNroVehiculo();
                break;
            case 4:
                return;
        }
        system("pause>nul");
    }
}


void menuVenta::iniciar(){
    rlutil::hidecursor();
    string opcionesMenu[] = {"Alta venta", "Buscar venta", "Listar ventas", "Modificar venta", "Baja venta", "Volver"};
    int anchoMenu = 32;
    int cantidadOpciones = 6;

    int consolaAncho = rlutil::tcols();
    int consolaAlto = rlutil::trows();
    int posX = (consolaAncho - anchoMenu) / 2;
    int posY = (consolaAlto - (cantidadOpciones + 4)) / 2;

    if (posX < 1) posX = 1;
    if (posY < 1) posY = 1;
    Menu m;
    ArchivoVentas arc;
    while(true){
        system("cls");
        rlutil::locate(posX, posY);
        cout << "================================";
        rlutil::locate(posX, posY + 1);
        cout << "|       SUBMENU DE VENTAS      |";
        rlutil::locate(posX, posY + 2);
        cout << "================================";
        int opc = m.mostrarMenu(opcionesMenu, cantidadOpciones, posX, posY + 4, anchoMenu);
        system("cls");
        switch(opc){
            case 0:
                arc.altaVenta();
                break;
            case 1:
                subMenuBuscarVenta();
                continue;
            case 2:
                tablaVentas(1,2);
                break;
            case 3:
                subMenuModificarVenta();
                continue;
            case 4:
                arc.bajaVenta();
                break;
            case 5:
                return;
        }
        system("pause>nul");
    }
}

menuVenta::~menuVenta(){
}
