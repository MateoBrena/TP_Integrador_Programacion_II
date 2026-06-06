#include <iostream>
#include <cstring>
#include <cctype>
#include "clsCliente.h"
#include "cargarCadena.h"
using namespace std;

Cliente::Cliente(int n, const char *c, const char *t){
    nroCliente = n;
    strcpy(cuit, c);
    strcpy(telefono, t);
}

bool Cliente::validarCuitFormato(const char *c){
    //longitud obligatoria
    if (c == nullptr || strlen(c) != 13){
        return false;
    }
    //validamos las posiciones de los guiones
    if (c[2] != '-' || c[11] != '-'){
        return false;
    }
    //validamos que sean todos numeros menos los guiones
    for (int i = 0; i < 13; i++){
        if (i == 2 || i == 11) continue; // a ellos los salteamos
        if(!isdigit(c[i])) {
            return false;
        }
    }
    if(c[0] != '2' || c[1] == '1' || c[1] == '2' || c[1] == '8' || c[1] == '9'){ //los prefijos deben ser 20, 23, 24, 25, 26 o 27
        return false;
    }

    return true;
}

bool Cliente::validarCuit(const char *c, const char *d){
    if(!validarCuitFormato(c)){
        return false;
    }
    char dniStr[9];
    strncpy(dniStr,c+3,8);
    dniStr[8] = '\0';
    if(strcmp(dniStr, d) == 0){
        return true;
    }else{
        return false;
    }
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

void Cliente::Cargar(const char *d, int n, const char *c, Fecha fN){
    Persona::Cargar(d, fN);
    nroCliente = n;
    strcpy(cuit,c);
    cout << "Ingrese el numero de telefono: ";
    cargarCadena(telefono,12);
}

void Cliente::Mostrar(){
    cout << endl << "Nro Cliente: " << nroCliente << endl;
    Persona::Mostrar();
    cout << "CUIT: " << cuit << endl;
    cout << "Telefono: " << telefono << endl;
}

Cliente::~Cliente(){

}
