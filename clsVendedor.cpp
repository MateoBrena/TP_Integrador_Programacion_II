#include <iostream>
#include <cstring>
#include "clsVendedor.h"
#include "cargarCadena.h"
using namespace std;

Vendedor::Vendedor(){

}

void Vendedor::setCategoria(int c){
    categoria = c;
}

void Vendedor::setFechaContratacion(Fecha f){
    fechaContratacion = f;
}

int Vendedor::getCategoria(){
    return categoria;
}

Fecha Vendedor::getFechaContratacion(){
    return fechaContratacion;
}

void Vendedor::Cargar(){
}

void Vendedor::Mostrar(){
}

Vendedor::~Vendedor(){
}
