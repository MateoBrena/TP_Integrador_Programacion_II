#include <iostream>
#include <cstring>
#include "clsVehiculo.h"
#include "cargarCadena.h"
using namespace std;

Vehiculo::Vehiculo(int d, const char *p, int iM, const char *m, int a, const char *c, int k, float pr, const char *co, Fecha fI){
    id = d;
    strcpy(patente, p);
    idMarca = iM;
    strcpy(modelo, m);
    anio = a;
    strcpy(color, c);
    kilometros = k;
    precio = pr;
    strcpy(combustible, co);
    fechaIngreso = fI;
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
    cout << "Patente: ";
    cargarCadena(patente,8);
    cout << "ID de marca: ";
    cin >> idMarca;
    cout << "Modelo: ";
    cargarCadena(modelo,20);
    cout << "Anio: ";
    cin >> anio;
    cout << "Color: ";
    cargarCadena(color,20);
    cout << "Kilometraje: ";
    cin >> kilometros;
    cout << "Precio: ";
    cin >> precio;
    cout << "Combustible: ";
    cargarCadena(combustible,10);
    cout << "Fecha de ingreso: ";
    fechaIngreso.cargarFecha();
}

void Vehiculo::Mostrar(){
    cout << "N de Vehiculo: " << id << endl;
    cout << "Patente: " << patente << endl;
    cout << "ID de marca: " << idMarca << endl;
    cout << "Modelo: " << modelo << endl;
    cout << "Anio: " << anio << endl;
    cout << "Color: " << color << endl;
    cout << "Kilometraje: " << kilometros << endl;
    cout << "Precio: " << precio << endl;
    cout << "Combustible: " << combustible << endl;
    cout << "Fecha de ingreso: ";
    fechaIngreso.mostrarFecha();
}

Vehiculo::~Vehiculo(){
}
