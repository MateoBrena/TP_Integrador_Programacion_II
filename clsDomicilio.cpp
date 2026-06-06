#include "clsDomicilio.h"
#include "cargarCadena.h"
using namespace std;

Domicilio::Domicilio(const char *c, int a, const char *l, const char *p, const char *cp){
    strcpy(calle, c);
    altura = a;
    strcpy(localidad, l);
    strcpy(provincia, p);
    strcpy(codigoPostal,cp);
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

void Domicilio::setCodigoPostal(const char *cp){
    strcpy(codigoPostal,cp);
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

const char * Domicilio::getCodigoPostal(){
    return codigoPostal;
}

void Domicilio::Cargar(){
    cout << "Calle: ";
    cargarCadena(calle, 30);
    altura = cargarEntero("Altura: ");
    cout << "Localidad: ";
    cargarCadena(localidad, 30);
    cout << "Provincia: ";
    cargarCadena(provincia, 30);
    cout << "Codigo postal: ";
    cargarCadena(codigoPostal, 10);
}

void Domicilio::Mostrar(){
    cout << "Calle: " << calle << " " << altura << endl;
    cout << "Localidad: " << localidad <<", Provincia: " << provincia << endl;
    cout << "Codigo postal: " << codigoPostal << endl;
}

string Domicilio::MostrarFormato(){
    return string(calle) + "," + to_string(altura) + "." + string(localidad);
}

Domicilio::~Domicilio(){

}
