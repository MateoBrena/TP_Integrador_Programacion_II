#include <iostream>
#include <cstring>
#include "clsDomicilio.h"
#include "cargarCadena.h"
using namespace std;

Domicilio::Domicilio(const char *c, int a, const char *l, const char *p, int cp){
    strcpy(calle, c);
    altura = a;
    strcpy(localidad, l);
    strcpy(provincia, p);
    codigoPostal = cp;
}

void Domicilio::setCalle(const char *c){
    strcpy(calle, c);
}

void Domicilio::setLocalidad(const char *l){
    strcpy(localidad, l);
}

void Domicilio::setProvincia(const char *p){
    strcpy(provincia, p);
}

void Domicilio::setAltura(int a){
    altura = a;
}

void Domicilio::setCodigoPostal(int cp){
    codigoPostal = cp;
}

const char* Domicilio::getCalle(){
    return calle;
}

const char* Domicilio::getLocalidad(){
    return localidad;
}

const char* Domicilio::getProvincia(){
    return provincia;
}

int Domicilio::getAltura(){
    return altura;
}

int Domicilio::getCodigoPostal(){
    return codigoPostal;
}

void Domicilio::cargar(){
    cout << "Calle: ";
    cargarCadena(calle, 50);
    cout << "Altura: ";
    cin >> altura;
    cout << "Localidad: ";
    cargarCadena(localidad, 50);
    cout << "Provincia: ";
    cargarCadena(provincia, 50);
    cout << "Codigo postal: ";
    cin >> codigoPostal;
}

void Domicilio::mostrar(){
    cout << "Calle: " << calle << " " << altura << endl;
    cout << "Localidad: " << localidad <<", Provincia: " << provincia << endl;
    cout << "Codigo postal: " << codigoPostal << endl;
}

Domicilio::~Domicilio(){

}
