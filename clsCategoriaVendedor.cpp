#include <iostream>
#include <iomanip>
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

void CategoriaVendedor::Cargar(int id, const char *d, float p){
    idCategoria = id;
    strcpy(descripcion, d);
    porcentajeComision = p;
}

void CategoriaVendedor::Mostrar(){
    cout << endl << "ID de Categoria: " << idCategoria << endl;
    cout << "Descripcion: " << descripcion << endl;
    cout << "Comision: " << porcentajeComision << "%" <<endl;
}

CategoriaVendedor::~CategoriaVendedor(){
}
