#include <iostream>
#include <cstring>
#include "clsCategoriaVendedor.h"
#include "cargarCadena.h"
using namespace std;

CategoriaVendedor::CategoriaVendedor(int d, const char *desc, float pC){
    idCategoria = d;
    strcpy(descripcion, desc);
    porcentajeComision = pC;
    estado = true;
}

void CategoriaVendedor::setIdCategoria(int id){
    idCategoria = id;
}

void CategoriaVendedor::setDescripcion(const char *d){
    strcpy(descripcion, d);
}

void CategoriaVendedor::setComision(float c){
    porcentajeComision = c;
}

void CategoriaVendedor::setEstado(bool e){
    estado = e;
}

int CategoriaVendedor::getIdCategoria(){
    return idCategoria;
}

const char* CategoriaVendedor::getDescripcion(){
    return descripcion;
}

float CategoriaVendedor::getPorcentajeComision(){
    return porcentajeComision;
}

bool CategoriaVendedor::getEstado(){
    return estado;
}

void CategoriaVendedor::Cargar(int id){
    if(id == -1){
        cout << "ID de categoria: ";
        cin >> idCategoria;
    }else{
        idCategoria = id;
    }
    cout << "Descripcion: ";
    cargarCadena(descripcion, 30);
    int pC;
    cout << "Porcentaje de comision: (Ingresar numero entero. Ej: 3): ";
    cin >> pC;
    porcentajeComision = (float)pC / 100;
}

void CategoriaVendedor::Mostrar(){
    cout << "ID de Categoria: " << idCategoria << endl;
    cout << "Descripcion: " << descripcion << endl;
    cout << "Comision: " << porcentajeComision*100 << "%" <<endl;
}

string CategoriaVendedor::PorcFormato(){
    return to_string(porcentajeComision*100) + "%";
}

CategoriaVendedor::~CategoriaVendedor(){
}
