#include <iostream>
#include <cstring>
#include "clsVendedor.h"
#include "cargarCadena.h"
using namespace std;

Vendedor::Vendedor(int n, int c, Fecha f){
    nroVendedor = n;
    categoria = c;
    fechaContratacion = f;
}

void Vendedor::setNroVendedor(int n){
    nroVendedor = n;
}

void Vendedor::setCategoria(int c){
    categoria = c;
}

void Vendedor::setFechaContratacion(Fecha f){
    fechaContratacion = f;
}

int Vendedor::getNroVendedor(){
    return nroVendedor;
}

int Vendedor::getCategoria(){
    return categoria;
}

Fecha Vendedor::getFechaContratacion(){
    return fechaContratacion;
}

void Vendedor::Cargar(int d, int n){
    Persona::Cargar(d);
    nroVendedor = n;
    cout << "Categoria: ";
    cin >> categoria;
    cout << "Fecha de contratacion: ";
    fechaContratacion.cargarFecha();
}

void Vendedor::Mostrar(){
    cout << "Nro Vendedor: " << nroVendedor << endl;
    Persona::Mostrar();
    cout << "Categoria: " << categoria << endl;
    cout << "Fecha de contratacion: ";
    fechaContratacion.mostrarFecha();
}

Vendedor::~Vendedor(){
}
