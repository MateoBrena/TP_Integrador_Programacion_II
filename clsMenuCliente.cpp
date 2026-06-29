#include <iostream>
#include <string>
#include <iomanip>
#include "rlutil.h"
#include "clsMenu.h"
#include "clsMenuCliente.h"
#include "clsArchivoClientes.h"
using namespace std;

menuCliente::menuCliente(){
}

void menuCliente::mostrarCabeceraTabla(int posX, int posY){
    const int TAM = 7;
    string columnas[TAM] = {"NC","NOMBRE","APELLIDO","D.N.I","DOMICILIO","FECHA NAC.","MAIL"};
    int anchos[TAM] = {3,12,12,8,30,10,22};
    Menu m;
    m.dibujarCabecera(posX, posY, columnas, anchos, TAM);
}

void menuCliente::tablaClientes(int posX, int posY){

    ArchivoClientes arc;
    int cant = arc.contarRegistros();
    if(cant == 0){
        cout << "No hay clientes cargados." << endl;
        return;
    }
    int cantActivos = arc.contarRegistrosActivos(cant);
    if(cantActivos == 0){
        cout << "No hay clientes activos cargados." << endl;
        return;
    }
    mostrarCabeceraTabla(posX,posY);
    posY += 3;
    Cliente c;
    const int TAM = 7;
    int anchos[TAM] = {3,12,12,8,30,10,22};
    int filasDibujadas = 0;
    Menu m;
    for(int i=0; i<cant; i++){
        c = arc.leerRegistro(i);
        if(c.getEstado()){
            filasDibujadas++;
            string columnas[TAM] = {to_string(c.getNroCliente()),c.getNombre(),c.getApellido(),c.getDni(),
            c.getDomicilio().MostrarFormato(),c.getFechaNacimiento().mostrarFechaFormato(),c.getMail()};
            bool esFin = (filasDibujadas == cantActivos);
            m.dibujarFila(posX, posY, columnas, anchos, TAM, esFin);
        }
    }
}

void menuCliente::subMenuBuscarCliente(){
    rlutil::hidecursor();
    string opcionesMenu[] = {"Buscar por id", "Buscar por DNI" ,"Buscar por Nombre", "Buscar por Apellido", "Buscar por mail",
    "Buscar por fecha de nac.","Buscar por CUIT" , "Buscar por telefono", "Volver" };
    int anchoMenu = 32;
    int cantidadOpciones = 9;

    int consolaAncho = rlutil::tcols();
    int consolaAlto = rlutil::trows();
    int posX = (consolaAncho - anchoMenu) / 2;
    int posY = (consolaAlto - (cantidadOpciones + 4)) / 2;

    if (posX < 1) posX = 1;
    if (posY < 1) posY = 1;
    Menu m;
    ArchivoClientes arc;
    while(true){
        system("cls");
        rlutil::locate(posX, posY);
        cout << "================================";
        rlutil::locate(posX, posY + 1);
        cout << "|        BUSCAR CLIENTES       |";
        rlutil::locate(posX, posY + 2);
        cout << "================================";
        int opc = m.mostrarMenu(opcionesMenu, cantidadOpciones, posX, posY + 4, anchoMenu);
        system("cls");
        switch(opc){
            case 0:
                arc.buscarPorId();
                break;
            case 1:
                arc.buscarPorDni();
                break;
            case 2:
                arc.buscarPorNombre();
                break;
            case 3:
                arc.buscarPorApellido();
                break;
            case 4:
                arc.buscarPorMail();
                break;
            case 5:
                arc.buscarPorFechaNac();
                break;
            case 6:
                arc.buscarPorCuit();
                break;
            case 7:
                arc.buscarPorTelefono();
                break;
            case 8:
                return;
        }
        system("pause>nul");
    }
}

void menuCliente::subMenuModificarCliente(){
    rlutil::hidecursor();
    string opcionesMenu[] = {"Modificar Nombre", "Modificar Apellido", "Modificar mail", "Modificar fecha de nac.",
    "Modificar domicilio", "Modificar CUIT" , "Modificar telefono", "Volver" };
    int anchoMenu = 32;
    int cantidadOpciones = 8;

    int consolaAncho = rlutil::tcols();
    int consolaAlto = rlutil::trows();
    int posX = (consolaAncho - anchoMenu) / 2;
    int posY = (consolaAlto - (cantidadOpciones + 4)) / 2;

    if (posX < 1) posX = 1;
    if (posY < 1) posY = 1;
    Menu m;
    ArchivoClientes arc;
    while(true){
        system("cls");
        rlutil::locate(posX, posY);
        cout << "================================";
        rlutil::locate(posX, posY + 1);
        cout << "|      MODIFICAR CLIENTES      |";
        rlutil::locate(posX, posY + 2);
        cout << "================================";
        int opc = m.mostrarMenu(opcionesMenu, cantidadOpciones, posX, posY + 4, anchoMenu);
        system("cls");
        switch(opc){
            case 0:
                arc.modificarNombre();
                break;
            case 1:
                arc.modificarApellido();
                break;
            case 2:
                arc.modificarMail();
                break;
            case 3:
                arc.modificarFechaNacimiento();
                break;
            case 4:
                arc.modificarDomicilio();
                break;
            case 5:
                arc.modificarCuit();
                break;
            case 6:
                arc.modificarTelefono();
                break;
            case 7:
                return;
        }
        system("pause>nul");
    }
}

void menuCliente::iniciar(){

    rlutil::hidecursor();
    string opcionesMenu[] = {"Alta cliente", "Buscar cliente", "Listar clientes", "Modificar cliente", "Baja cliente", "Volver" };
    int anchoMenu = 32;
    int cantidadOpciones = 6;

    int consolaAncho = rlutil::tcols();
    int consolaAlto = rlutil::trows();
    int posX = (consolaAncho - anchoMenu) / 2;
    int posY = (consolaAlto - (cantidadOpciones + 4)) / 2;

    if (posX < 1) posX = 1;
    if (posY < 1) posY = 1;
    Menu m;
    ArchivoClientes arc;
    while(true){
        system("cls");
        rlutil::locate(posX, posY);
        cout << "================================";
        rlutil::locate(posX, posY + 1);
        cout << "|      SUBMENU DE CLIENTES     |";
        rlutil::locate(posX, posY + 2);
        cout << "================================";
        int opc = m.mostrarMenu(opcionesMenu, cantidadOpciones, posX, posY + 4, anchoMenu);
        system("cls");
        switch(opc){
            case 0:
                arc.altaCliente();
                break;
            case 1:
                subMenuBuscarCliente();
                continue;
            case 2:
                tablaClientes(1,2);
                break;
            case 3:
                subMenuModificarCliente();
                continue;
            case 4:
                arc.bajaCliente();
                break;
            case 5:
                return;
        }
        system("pause>nul");
    }
}

menuCliente::~menuCliente(){
}
