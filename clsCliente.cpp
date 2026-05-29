#include <iostream>
#include <cstring>
#include "clsCliente.h"
#include "cargarCadena.h"
using namespace std;

Cliente::Cliente(int n, const char *c, const char *t){
    nroCliente = n;
    strcpy(cuit, c);
    strcpy(telefono, t);
}

void Cliente::setNroCliente(int n){
    nroCliente = n;
}

void Cliente::setCuit(const char *c){
    strcpy(cuit, c);
}
void Cliente::setTelefono(const char *t){
    strcpy(telefono, t);
}

int Cliente::getNroCliente(){
    return nroCliente;
}

const char* Cliente::getCuit(){
    return cuit;
}

const char* Cliente::getTelefono(){
    return telefono;
}

void Cliente::Cargar(int d, int n){
    Persona::Cargar(d);
    nroCliente = n;
    cout << "CUIT: ";
    cargarCadena(cuit,12);
    cout << "Telefono: ";
    cargarCadena(telefono,12);
}

void Cliente::Mostrar(){
    cout << "Nro Cliente: " << nroCliente << endl;
    Persona::Mostrar();
    cout << "CUIT: " << cuit << endl;
    cout << "Telefono: " << telefono << endl;
}

Cliente::~Cliente(){

}
