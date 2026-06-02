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
    rlutil::setColor(rlutil::CYAN);
    rlutil::locate(posX, posY);
    // Dibujamos la línea superior del cuadro adaptada a vendedores
    cout << (char)218<<"----"<<(char)194<<"--------------"<<(char)194<<"--------------"<<(char)194<<"----------"<<(char)194;
    cout << "------------"<<(char)194<<"------------"<<(char)194<<"------------------------"<<(char)191;

    rlutil::locate(posX, posY + 1);
    cout << "| " << left << setw(2) << "NV"
         << " | " << setw(12) << "NOMBRE"
         << " | " << setw(12) << "APELLIDO"
         << " | " << setw(8) << "D.N.I"
         << " | " << setw(10) << "CATEGORIA"
         << " | " << setw(10) << "FEC.CONTR."
         << " | " << setw(22) << "MAIL" << " |";

    rlutil::locate(posX, posY + 2);
    cout <<(char)195<<"----"<<(char)197<<"--------------"<<(char)197<<"--------------"<<(char)197<<"----------"<<(char)197;
    cout << "------------"<<(char)197<<"------------"<<(char)197<<"------------------------|";

    rlutil::setColor(rlutil::WHITE);
}

void menuVendedor::tablaVendedores(int posX, int posY){
    ArchivoVendedores arc;
    ArchivoCategorias arc2;
    int cant = arc.contarRegistros();
    if(cant <= 0){
        cout << "No hay vendedores cargados." << endl;
        return;
    }

    mostrarCabeceraTabla(posX, posY);
    int filaActual = posY + 3;
    Vendedor v;
    CategoriaVendedor c;
    int pC;
    for(int i = 0; i < cant; i++){
        v = arc.leerRegistro(i);
        pC = v.getCategoria()-1;
        c = arc2.leerRegistro(pC);
        if(v.getEstado()){
            rlutil::locate(posX, filaActual);
            cout << "| " << left << setw(2) << v.getNroVendedor()
                 << " | " << setw(12) << v.getNombre()
                 << " | " << setw(12) << v.getApellido()
                 << " | " << setw(8) << v.getDni()
                 << " | " << setw(10) << c.getDescripcion()
                 << " | " << setw(10) << v.getFechaContratacion().mostrarFechaFormato();
            cout << " | " << setw(22) << v.getMail() << " |";

            if(i == cant - 1){
                rlutil::locate(posX, filaActual + 1);
                cout <<(char)192<<"----"<<(char)193<<"--------------"<<(char)193<<"--------------"<<(char)193<<"----------"<<(char)193;
                cout<<"------------"<<(char)193<<"------------"<<(char)193<<"------------------------"<<(char)217;
            }else{
                rlutil::locate(posX, filaActual + 1);
                cout <<(char)195<<"----"<<(char)197<<"--------------"<<(char)197<<"--------------"<<(char)197<<"----------"<<(char)197;
                cout << "------------"<<(char)197<<"------------"<<(char)197<<"------------------------|";
            }
            filaActual += 2;
        }
    }
}

void menuVendedor::subMenuModificarVendedor(){
    rlutil::hidecursor();
    string opcionesMenu[] = {
        "Modificar Nombre",
        "Modificar Apellido",
        "Modificar Mail",
        "Modificar fecha de nac.",
        "Modificar fecha contratacion",
        "Modificar domicilio",
        "Modificar categoria",
        "Volver"
    };
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
        cout << "|     SUBMENU DE VENDEDORES     |";
        rlutil::locate(posX, posY + 2);
        cout << "================================";
        int opc = m.mostrarMenu(opcionesMenu, cantidadOpciones, posX, posY + 4, anchoMenu);
        system("cls");
        switch(opc){
            case 0:
                arc.altaVendedor();
                break;
            case 1:
                arc.buscarPorDni();
                break;
            case 2:
                //arc.listarRegistros();
                tablaVendedores(2,2);
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
