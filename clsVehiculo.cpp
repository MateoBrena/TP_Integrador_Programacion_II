#include <iostream>
#include <cstring>
#include "clsVehiculo.h"
#include "cargarCadena.h"
using namespace std;

Vehiculo::Vehiculo(){

}

void Vehiculo::setId(int i){
    id = i;
}

void Vehiculo::setPatente(const char *p){
    strcpy(patente,p);
}

void Vehiculo::setIdMarca(int iM){
    idMarca = iM;
}

void Vehiculo::setModelo(const char *m){
    strcpy(modelo,m);
}

void Vehiculo::setAnio(int a){
    anio = a;
}

void Vehiculo::setColor(const char *c){
     strcpy(color,c);
}

void Vehiculo::setKilometros(int k){
    kilometros = k;
}

void Vehiculo::setPrecio(float p){
    precio = p;
}

void Vehiculo::setCombustible(const char *co){
    strcpy(combustible,co);
}

void Vehiculo::setFechaIngreso(Fecha fI){
    fechaIngreso = fI;
}

void Vehiculo::setEstado(bool e){
    estado = e;
}

int Vehiculo::getId(){
    return id;
}

const char* Vehiculo::getPatente(){
    return patente;
}

int Vehiculo::getIdMarca(){
    return idMarca;
}

const char* Vehiculo::getModelo(){
    return modelo;
}

int Vehiculo::getAnio(){
    return anio;
}

const char* Vehiculo::getColor(){
    return color;
}

int Vehiculo::getKilometros(){
    return kilometros;
}

float Vehiculo::getPrecio(){
    return precio;
}

const char* Vehiculo::getCombustible(){
    return combustible;
}

Fecha Vehiculo::getFechaIngreso(){
    return fechaIngreso;
}

bool Vehiculo::getEstado(){
    return estado;
}

void Vehiculo::Cargar(){
}

void Vehiculo::Mostrar(){
}

Vehiculo::~Vehiculo(){
}
