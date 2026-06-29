#include <iostream>
#include <string>
#include <iomanip>
#include "rlutil.h"
#include "clsMenu.h"
#include "clsMenuVendedor.h"
#include "clsArchivosVendedores.h"
#include "clsArchivosCategoriaVendedor.h"
using namespace std;

menuVendedor::menuVendedor(){
}

void menuVendedor::mostrarCabeceraTabla(int posX, int posY) {
    const int TAM = 7;
    string columnas[TAM] = {"NV","NOMBRE","APELLIDO","D.N.I","CATEGORIA","FEC. CONTR.","MAIL"};
    int anchos[TAM] = {2,12,12,8,12,12,22};
    Menu m;
    m.dibujarCabecera(posX, posY, columnas, anchos, TAM);
}

void menuVendedor::tablaVendedores(int posX, int posY){
    ArchivoVendedores arc;
    ArchivoCategorias arc2;
    int cant = arc.contarRegistros();
    if(cant <= 0){
        cout << "No hay vendedores cargados." << endl;
        return;
    }
    int cantActivos = arc.contarRegistrosActivos(cant);
    if(cantActivos == 0){
        cout << "No hay vendedores activos cargados." << endl;
        return;
    }

    mostrarCabeceraTabla(posX, posY);
    posY += 3;
    Vendedor v;
    CategoriaVendedor c;
    Menu m;
    const int TAM = 7;
    int anchos[TAM] = {2,12,12,8,12,12,22};
    int pC;
    int filasDibujadas = 0;
    for(int i = 0; i < cant; i++){
        v = arc.leerRegistro(i);
        pC = v.getCategoria()-1;
        c = arc2.leerRegistro(pC);
        if(v.getEstado()){
            filasDibujadas++;
            string columnas[TAM] = {to_string(v.getNroVendedor()),v.getNombre(),v.getApellido(),v.getDni(),
            c.getDescripcion(),v.getFechaContratacion().mostrarFechaFormato(),v.getMail()};
            bool esFin = (filasDibujadas == cantActivos);
            m.dibujarFila(posX, posY, columnas, anchos, TAM, esFin);
        }
    }
}

void menuVendedor::subMenuBuscarVendedor(){
    rlutil::hidecursor();
    string opcionesMenu[] = {"Buscar por id","Buscar por DNI","Buscar por Nombre","Buscar por Apellido","Buscar por mail",
    "Buscar por fecha de nac.","Buscar por fecha contr.","Buscar por categoria","Volver"};
    int anchoMenu = 32;
    int cantidadOpciones = 9;

    int consolaAncho = rlutil::tcols();
    int consolaAlto = rlutil::trows();
    int posX = (consolaAncho - anchoMenu) / 2;
    int posY = (consolaAlto - (cantidadOpciones + 4)) / 2;

    if (posX < 1) posX = 1;
    if (posY < 1) posY = 1;
    Menu m;
    ArchivoVendedores arc;
    while(true){
        system("cls");
        rlutil::locate(posX, posY);
        cout << "================================";
        rlutil::locate(posX, posY + 1);
        cout << "|       BUSCAR VENDEDORES      |";
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
                arc.buscarPorFechaCont();
                break;
            case 7:
                arc.buscarPorCat();
                break;
            case 8:
                return;
        }
        system("pause>nul");
    }
}

void menuVendedor::subMenuModificarVendedor(){
    rlutil::hidecursor();
    string opcionesMenu[] = {"Modificar Nombre","Modificar Apellido","Modificar mail","Modificar fecha de nac.",
    "Modificar fecha contratacion","Modificar domicilio","Modificar categoria","Volver"};
    int anchoMenu = 32;
    int cantidadOpciones = 8;

    int consolaAncho = rlutil::tcols();
    int consolaAlto = rlutil::trows();
    int posX = (consolaAncho - anchoMenu) / 2;
    int posY = (consolaAlto - (cantidadOpciones + 4)) / 2;

    if (posX < 1) posX = 1;
    if (posY < 1) posY = 1;
    Menu m;
    ArchivoVendedores arc;
    while(true){
        system("cls");
        rlutil::locate(posX, posY);
        cout << "================================";
        rlutil::locate(posX, posY + 1);
        cout << "|     MODIFICAR VENDEDORES     |";
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
                arc.modificarFechaContratacion();
                break;
            case 5:
                arc.modificarDomicilio();
                break;
            case 6:
                arc.modifcarCategoria();
                break;
            case 7:
                return;
        }
        system("pause>nul");
    }
}

void menuVendedor::iniciar(){
    rlutil::hidecursor();
    string opcionesMenu[] = {"Alta vendedor", "Buscar vendedor", "Listar vendedores", "Modificar vendedor", "Baja vendedor", "Volver"};
    int anchoMenu = 32;
    int cantidadOpciones = 6;

    int consolaAncho = rlutil::tcols();
    int consolaAlto = rlutil::trows();
    int posX = (consolaAncho - anchoMenu) / 2;
    int posY = (consolaAlto - (cantidadOpciones + 4)) / 2;

    if (posX < 1) posX = 1;
    if (posY < 1) posY = 1;
    Menu m;
    ArchivoVendedores arc;
    while(true){
        system("cls");
        rlutil::locate(posX, posY);
        cout << "================================";
        rlutil::locate(posX, posY + 1);
        cout << "|     SUBMENU DE VENDEDORES    |";
        rlutil::locate(posX, posY + 2);
        cout << "================================";
        int opc = m.mostrarMenu(opcionesMenu, cantidadOpciones, posX, posY + 4, anchoMenu);
        system("cls");
        switch(opc){
            case 0:
                arc.altaVendedor();
                break;
            case 1:
                subMenuBuscarVendedor();
                continue;
            case 2:
                tablaVendedores(1,2);
                break;
            case 3:
                subMenuModificarVendedor();
                continue;
            case 4:
                arc.bajaVendedor();
                break;
            case 5:
                return;
        }
        system("pause>nul");
    }
}

menuVendedor::~menuVendedor(){
}
