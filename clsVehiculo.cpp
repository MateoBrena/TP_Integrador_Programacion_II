#include <iostream>
#include <cstring>
#include <cctype>
#include <iomanip>
#include <sstream>
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
    estado = true;
}

void Vehiculo::hacerMayusculas(char *p){
    for (int i = 0; p[i] != '\0'; ++i) {
        p[i] = toupper(p[i]);
    }
}

bool Vehiculo::validarPatente(const char *p){
    int longitud = strlen(p);

    //verificamos el formato antiguo: AAA111
    if (longitud == 6) {
        return isupper(p[0]) &&
               isupper(p[1]) &&
               isupper(p[2]) &&
               isdigit(p[3]) &&
               isdigit(p[4]) &&
               isdigit(p[5]);
    }
    //verificamos el formato nuevo: AA111AA
    else if (longitud == 7) {
        return isupper(p[0]) &&
               isupper(p[1]) &&
               isdigit(p[2]) &&
               isdigit(p[3]) &&
               isdigit(p[4]) &&
               isupper(p[5]) &&
               isupper(p[6]);
    }

    //si no tiene longitud 6 ni 7, es invalida
    return false;
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

string Vehiculo::getPrecioFormato(){
    float precioFloat = getPrecio();
    stringstream ss;
    ss << "$" << fixed << setprecision(2) << precioFloat;

    return ss.str();
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

void Vehiculo::Cargar(int d, const char *p, int iM){
    id = d;
    strcpy(patente,p);
    idMarca = iM;
    cout << "Modelo: ";
    cargarCadena(modelo,20);
    anio = cargarEntero("Anio: ");
    cout << "Color: ";
    cargarCadena(color,20);
    kilometros = cargarEntero("Kilometraje: ");
    precio = cargarFlotante("Precio: ");
    cout << "Combustible: ";
    cargarCadena(combustible,10);
    cout << "Fecha de ingreso: ";
    fechaIngreso.cargarFecha();
}

void Vehiculo::Mostrar(){
    cout << fixed << setprecision(2);
    cout << endl << "N de Vehiculo: " << id << endl;
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
