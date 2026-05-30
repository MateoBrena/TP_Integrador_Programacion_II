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

void Marca::Cargar(int d){
    if(d == -1){
        cout << "ID de marca: ";
        cin >> id;
    }else{
        id = d;
    }
    cout << "Nombre: ";
    cargarCadena(nombre, 20);
    cout << "Pais: ";
    cargarCadena(pais, 20);
}

void Marca::Mostrar(){
    cout << "ID de marca: " << id << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Pais: " << pais << endl;
}

Marca::~Marca(){

}
