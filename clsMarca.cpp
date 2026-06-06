#include <iostream>
#include <cstring>
#include "cargarCadena.h"
#include "clsMarca.h"
using namespace std;

Marca::Marca(int d, const char *n, const char *p){
    id = d;
    strcpy(nombre, n);
    strcpy(pais, p);
    estado=true;
}

void Marca::setId(int i){
    id = i;
}

void Marca::setNombre(const char *n){
    strcpy(nombre, n);
}

void Marca::setPais(const char *p){
    strcpy(pais, p);
}

void Marca::setEstado(bool e){
    estado = e;
}

int Marca::getId(){
    return id;
}

const char* Marca::getNombre(){
    return nombre;
}

const char* Marca::getPais(){
    return pais;
}

bool Marca::getEstado(){
    return estado;
}

void Marca::Cargar(int d, const char *n){
    id = d;
    strcpy(nombre, n);
    cout << "Pais: ";
    cargarCadena(pais, 20);
}

void Marca::Mostrar(){
    cout << endl << "ID de marca: " << id << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Pais: " << pais << endl;
}

Marca::~Marca(){

}
