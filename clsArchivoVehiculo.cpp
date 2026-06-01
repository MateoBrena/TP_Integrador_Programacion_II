#include <iostream>
#include <cstring>
#include "clsArchivoVehiculos.h"
#include "clsArchivoMarcas.h"
#include "cargarCadena.h"
using namespace std;

ArchivoVehiculos::ArchivoVehiculos(const char *n){
    strcpy(nombre, n);
}

Vehiculo ArchivoVehiculos::leerRegistro(int pos){
    FILE *p = fopen(nombre, "rb");
    Vehiculo obj;
    if(p == nullptr){
        obj.setPatente("ERROR");
        return obj;
    }
    fseek(p, sizeof obj * pos, 0);
    fread(&obj, sizeof obj, 1, p);
    fclose(p);
    return obj;
}

bool ArchivoVehiculos::grabarRegistro(Vehiculo obj){
    FILE *p = fopen(nombre, "ab");
    if(p == nullptr){
        return false;
    }
    bool escribio = fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
    return escribio;
}

bool ArchivoVehiculos::modificarRegistro(Vehiculo obj, int pos){
    FILE *p = fopen(nombre, "rb+");
    if(p == nullptr){
        return false;
    }
    fseek(p, sizeof obj * pos, 0);
    bool escribio = fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
    return escribio;
}

int ArchivoVehiculos::contarRegistros(){
    FILE *p = fopen(nombre, "rb");
    if(p == nullptr){
        return -1;
    }
    fseek(p, 0, 2);
    int cant = ftell(p) / sizeof(Vehiculo);
    fclose(p);
    return cant;
}

int ArchivoVehiculos::buscarRegistro(const char* patente){
    int cantReg = contarRegistros();
    for(int i = 0; i < cantReg; i++){
        Vehiculo obj = leerRegistro(i);
        if(strcmp(obj.getPatente(), patente) == 0){
            return i;
        }
    }
    return -1;
}

void ArchivoVehiculos::listarRegistros(){
    int cantReg = contarRegistros();
    if(cantReg <= 0){
        cout << "No hay vehiculos registrados." << endl;
        return;
    }
    for(int i = 0; i < cantReg; i++){
        Vehiculo obj = leerRegistro(i);
        if(obj.getEstado()){
            obj.Mostrar();
            cout << "--------------------------------" << endl;
        }
    }
}

void ArchivoVehiculos::buscarPorPatente(){
    char auxPatente[10];
    cout << "Ingrese la patente del vehiculo a buscar: ";
    cargarCadena(auxPatente, 10);

    int pos = buscarRegistro(auxPatente);
    if(pos < 0){
        cout << "La patente ingresada no existe en el archivo." << endl;
        return;
    }

    Vehiculo obj = leerRegistro(pos);
    if(obj.getEstado()){
        obj.Mostrar();
    } else {
        cout << "Error: El vehiculo con patente " << auxPatente << " se encuentra dado de baja." << endl;
    }
}

void ArchivoVehiculos::altaVehiculo(){
    Vehiculo obj;
    obj.Cargar();
    int pos = buscarRegistro(obj.getPatente());
    if(pos >= 0){
        cout << endl << "Error: Ya existe un vehiculo registrado con la patente " << obj.getPatente() << ". Alta cancelada." << endl;
        return;
    }

    ArchivoMarcas arcMarcas;
    int posMarca = arcMarcas.buscarRegistro(obj.getIdMarca());

    if(posMarca == -1){
        cout << endl << "Error: El ID de marca (" << obj.getIdMarca() << ") no existe o esta dado de baja. Alta cancelada." << endl;
        return;
    }
    obj.setEstado(true);
    if(grabarRegistro(obj)){
        cout << endl << "Vehiculo registrado con exito!" << endl;
    } else {
        cout << endl << "Error al grabar el registro en el archivo." << endl;
    }
}

void ArchivoVehiculos::bajaVehiculo(){
    char auxPatente[10];
    cout << "Ingrese la patente del vehiculo a dar de baja: ";
    cargarCadena(auxPatente, 10);

    int pos = buscarRegistro(auxPatente);
    if(pos < 0){
        cout << "La patente ingresada no existe en el archivo." << endl;
        return;
    }

    Vehiculo obj = leerRegistro(pos);
    if(!obj.getEstado()){
        cout << "El vehiculo ya se encuentra dado de baja." << endl;
        return;
    }

    obj.setEstado(false); // Baja lógica
    if(modificarRegistro(obj, pos)){
        cout << "Baja del vehiculo realizada con exito." << endl;
    } else {
        cout << "Error al procesar la baja en el archivo." << endl;
    }
}


void ArchivoVehiculos::modificarMarca(){
    char auxPatente[10];
    cout << "Ingrese la patente del vehiculo: ";
    cargarCadena(auxPatente, 10);

    int pos = buscarRegistro(auxPatente);
    if(pos < 0){
        cout << "La patente ingresada no existe." << endl;
        return;
    }

    Vehiculo obj = leerRegistro(pos);
    int nuevaMarca;
    cout << "Ingrese el ID de la nueva marca: ";
    cin >> nuevaMarca;

    // 🔍 RELACIÓN: Validamos si la nueva marca existe y está activa
    ArchivoMarcas arcMarcas;
    int posMarca = arcMarcas.buscarRegistro(nuevaMarca);
    if(posMarca == -1){
        cout << "Error: La marca con ID " << nuevaMarca << " no existe o esta dada de baja." << endl;
        return;
    }

    obj.setIdMarca(nuevaMarca);
    if(modificarRegistro(obj, pos)){
        cout << "Marca modificada con exito!" << endl;
    } else {
        cout << "Error al guardar la modificacion." << endl;
    }
}

void ArchivoVehiculos::modificarModelo(){
    char auxPatente[10];
    cout << "Ingrese la patente del vehiculo: ";
    cargarCadena(auxPatente, 10);

    int pos = buscarRegistro(auxPatente);
    if(pos < 0){
        cout << "La patente ingresada no existe." << endl;
        return;
    }

    Vehiculo obj = leerRegistro(pos);
    char nuevoModelo[20];
    cout << "Ingrese el nuevo modelo: ";
    cargarCadena(nuevoModelo, 20);

    obj.setModelo(nuevoModelo);
    if(modificarRegistro(obj, pos)){
        cout << "Modelo modificado con exito!" << endl;
    } else {
        cout << "Error al guardar la modificacion." << endl;
    }
}

void ArchivoVehiculos::modificarAnio(){
    char auxPatente[10];
    cout << "Ingrese la patente del vehiculo: ";
    cargarCadena(auxPatente, 10);

    int pos = buscarRegistro(auxPatente);
    if(pos < 0){
        cout << "La patente ingresada no existe." << endl;
        return;
    }

    Vehiculo obj = leerRegistro(pos);
    int nuevoAnio;
    cout << "Ingrese el nuevo anio: ";
    cin >> nuevoAnio;

    obj.setAnio(nuevoAnio);
    if(modificarRegistro(obj, pos)){
        cout << "Anio modificado con exito!" << endl;
    } else {
        cout << "Error al guardar la modificacion." << endl;
    }
}

void ArchivoVehiculos::modificarColor(){
    char auxPatente[10];
    cout << "Ingrese la patente del vehiculo: ";
    cargarCadena(auxPatente, 10);

    int pos = buscarRegistro(auxPatente);
    if(pos < 0){
        cout << "La patente ingresada no existe." << endl;
        return;
    }

    Vehiculo obj = leerRegistro(pos);
    char nuevoColor[20];
    cout << "Ingrese el nuevo color: ";
    cargarCadena(nuevoColor, 20);

    obj.setColor(nuevoColor);
    if(modificarRegistro(obj, pos)){
        cout << "Color modificado con exito!" << endl;
    } else {
        cout << "Error al guardar la modificacion." << endl;
    }
}

void ArchivoVehiculos::modificarKilometros(){
    char auxPatente[10];
    cout << "Ingrese la patente del vehiculo: ";
    cargarCadena(auxPatente, 10);

    int pos = buscarRegistro(auxPatente);
    if(pos < 0){
        cout << "La patente ingresada no existe." << endl;
        return;
    }

    Vehiculo obj = leerRegistro(pos);
    int nuevosKms;
    cout << "Ingrese el nuevo kilometraje: ";
    cin >> nuevosKms;

    obj.setKilometros(nuevosKms);
    if(modificarRegistro(obj, pos)){
        cout << "Kilometros modificados con exito!" << endl;
    } else {
        cout << "Error al guardar la modificacion." << endl;
    }
}

void ArchivoVehiculos::modificarPrecio(){
    char auxPatente[10];
    cout << "Ingrese la patente del vehiculo: ";
    cargarCadena(auxPatente, 10);

    int pos = buscarRegistro(auxPatente);
    if(pos < 0){
        cout << "La patente ingresada no existe." << endl;
        return;
    }

    Vehiculo obj = leerRegistro(pos);
    float nuevoPrecio;
    cout << "Ingrese el nuevo precio: ";
    cin >> nuevoPrecio;

    obj.setPrecio(nuevoPrecio);
    if(modificarRegistro(obj, pos)){
        cout << "Precio modificado con exito!" << endl;
    } else {
        cout << "Error al guardar la modificacion." << endl;
    }
}

void ArchivoVehiculos::modificarCombustible(){
    char auxPatente[10];
    cout << "Ingrese la patente del vehiculo: ";
    cargarCadena(auxPatente, 10);

    int pos = buscarRegistro(auxPatente);
    if(pos < 0){
        cout << "La patente ingresada no existe." << endl;
        return;
    }

    Vehiculo obj = leerRegistro(pos);
    char nuevoCombustible[10];
    cout << "Ingrese el nuevo tipo de combustible: ";
    cargarCadena(nuevoCombustible, 10);

    obj.setCombustible(nuevoCombustible);
    if(modificarRegistro(obj, pos)){
        cout << "Tipo de combustible modificado con exito!" << endl;
    } else {
        cout << "Error al guardar la modificacion." << endl;
    }
}

void ArchivoVehiculos::modificarFechaIngreso(){
    char auxPatente[10];
    cout << "Ingrese la patente del vehiculo: ";
    cargarCadena(auxPatente, 10);

    int pos = buscarRegistro(auxPatente);
    if(pos < 0){
        cout << "La patente ingresada no existe." << endl;
        return;
    }

    Vehiculo obj = leerRegistro(pos);
    Fecha nuevaFecha;
    cout << "Ingrese la nueva fecha de ingreso: " << endl;
    nuevaFecha.cargarFecha();

    obj.setFechaIngreso(nuevaFecha);
    if(modificarRegistro(obj, pos)){
        cout << "Fecha de ingreso modificada con exito!" << endl;
    } else {
        cout << "Error al guardar la modificacion." << endl;
    }
}

ArchivoVehiculos::~ArchivoVehiculos(){
}


