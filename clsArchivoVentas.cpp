#include <iostream>
#include <cstring>
#include "clsArchivoVentas.h"
#include "clsArchivoClientes.h"
#include "clsArchivosVendedores.h"
#include "clsArchivoVehiculos.h"
#include "cargarCadena.h"
using namespace std;

ArchivoVentas::ArchivoVentas(const char *n){
    strcpy(nombre, n);
}

Venta ArchivoVentas::leerRegistro(int pos){
    FILE *p = fopen(nombre,"rb");
    Venta obj;
    if(p == nullptr){
        obj.setNroVenta(-2);
        return obj;
    }
    obj.setNroVenta(-1);
    fseek(p,  sizeof obj * pos, 0);
    fread(&obj, sizeof obj, 1, p);
    fclose(p);

    return obj;

}

bool ArchivoVentas::grabarRegistro(Venta obj){
    FILE *p = fopen(nombre, "ab");
    if(p == nullptr){
        return false;
    }
    bool escribio = fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
    return escribio;
}

bool ArchivoVentas::modificarRegistro(Venta obj, int pos){
    FILE *p = fopen(nombre, "rb+");
    if(p == nullptr){
        return false;
    }
    fseek(p, sizeof obj * pos, 0);
    bool escribio = fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
    return escribio;
}

int ArchivoVentas::contarRegistros(){
    FILE *p = fopen(nombre, "rb");
    if(p == nullptr){
        return -1;
    }
    fseek(p,0,2);
    int cant = ftell(p)/sizeof(Venta);
    fclose(p);
    return cant;
}

int ArchivoVentas::contarRegistrosActivos(int ca){
    int cantActivos = 0;
    for(int i=0; i<ca; i++){
        Venta c = leerRegistro(i);
        if(c.getEstado()){
            cantActivos++;
        }
    }

    return cantActivos;
}


int ArchivoVentas::buscarRegistro(int d){
    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++){
        Venta obj = leerRegistro(i);
        if(obj.getNroVenta() == d){
            return i;
        }
    }

    return -1;
}

int ArchivoVentas::buscarRegistroActivo(int d){
    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++){
        Venta obj = leerRegistro(i);
        if(obj.getNroVenta() == d && obj.getEstado()){
            return i;
        }
    }

    return -1;
}

void ArchivoVentas::listarRegistros(){
    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++){
        Venta obj = leerRegistro(i);
        if(obj.getEstado()){
            obj.Mostrar();
            cout << endl;
        }
    }
}

void ArchivoVentas::altaVenta(){
    char cc[12];
    cout << "Ingrese el CUIT del cliente (Sin espacios ni guiones): ";
    cin >> cc;
    ArchivoClientes arcCli;
    int pos = arcCli.buscarRegistroxCUIT(cc);
    if(pos < 0){
        cout << endl << "Error: No existe un cliente con el cuit ingresado" << endl;
        return;
    }
    int nv;
    cout << "Ingrese el numero del vendedor que realiza la venta: ";
    cin >> nv;
    ArchivoVendedores arcVen;
    pos = arcVen.buscarRegistroPorNv(nv);
    if(pos < 0){
        cout << endl << "Error: No existe un vendedor con el numero ingresado" << endl;
        return;
    }
    Vehiculo obj;
    char patente[10];
    cout << "Ingrese la patente del vehiculo (Sin espacios): ";
    cin >> patente;
    obj.hacerMayusculas(patente);
    if(!obj.validarPatente(patente)){
        cout << endl << "Error: Patente ingresada con formato invalido." << endl;
        return;
    }
    ArchivoVehiculos arcVeh;
    pos = arcVeh.buscarRegistro(patente);
    if(pos < 0){
        cout << endl << "Error: No existe un vehiculo con la patente ingresada." << endl;
        return;
    }
    Fecha f;
    Fecha hoy;
    hoy.setHoy();
    f.cargarFecha();
    if(f > hoy){
        cout << endl << "Error: No se puede ingresar una fecha futura." << endl;
        return;
    }
    obj = arcVeh.leerRegistro(pos);
    float m = obj.getPrecio();
    int cant = contarRegistros();
    if(cant <0) cant = 0;
    int nro = cant + 1;
    Venta v;
    v.Cargar(nro, f, cc, nv, patente, m);
    if(grabarRegistro(v)){
        cout<< endl <<"Registro grabado exitosamente!"<<endl;
    }else{
        cout<< endl <<"Error al grabar el registro"<<endl;
    }
}

void ArchivoVentas::buscarPorId(){
    int d;
    cout << "Ingrese el numero de la venta a buscar: ";
    cin >> d;
    int pos = buscarRegistroActivo(d);
    if(pos < 0){
        cout << endl << "Error: No existe una venta con el ID ingresado" << endl;
    }
    Venta v = leerRegistro(pos);
    v.Mostrar();
}

void ArchivoVentas::modificarFechaVenta(){
    cout << "Modificar fecha venta" << endl;
}
void ArchivoVentas::modificarCuitCliente(){
    cout << "Modificar cuit venta" << endl;
}
void ArchivoVentas::modificarNroVendedor(){
    cout << "Modificar nro vendedor venta" << endl;
}
void ArchivoVentas::modificarPatenteVehiculo(){
    cout << "Modificar patente venta" << endl;
}
void ArchivoVentas::modificarMonto(){
    cout << "Modificar monto venta" << endl;
}

void ArchivoVentas::bajaVenta(){
    cout<<"Ingrese el ID de la venta: ";
    int d;
    cin>>d;
    int pos = buscarRegistro(d);
    if(pos < 0){
        cout << endl << "Error: El ID ingresado no existe en el archivo"<<endl;
        return;
    }
    Venta obj;
    obj = leerRegistro(pos);
    if(obj.getEstado() == false){
        cout << endl <<"La venta ya se encuentra dada de baja"<<endl;
        return;
    }
    obj.setEstado(false);
    if(modificarRegistro(obj, pos)){
        cout << endl <<"Baja realizada correctamente"<<endl;
    }else{
        cout << endl <<"Error al realizar la baja"<<endl;
    }
}

ArchivoVentas::~ArchivoVentas(){
}
