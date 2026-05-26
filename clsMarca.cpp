#include <iostream>
#include <cstring>
using namespace std;
#include "clsMarca.h"

Marca::Marca(){

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

void Marca::Cargar(){

}

void Marca::Mostrar(){

}

Marca::~Marca(){

}
