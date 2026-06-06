#include <iostream>
#include <cstring>
#include <cctype>
#include "clsPersona.h"
#include "cargarCadena.h"
using namespace std;

Persona::Persona(const char *d, const char *n, const char *a, const char *m, Fecha fN, Domicilio dom){
    strcpy(dni, d);
    strcpy(nombre, n);
    strcpy(apellido, a);
    strcpy(mail, m);
    fechaNacimiento = fN;
    domicilio = dom;
    estado = true;
}

bool Persona::validarDni(const char *d){
    int longitud = strlen(d);

    //verificamos longitud y que todos sean numeros
    if (longitud == 8) {
        return isdigit(d[0]) &&
               isdigit(d[1]) &&
               isdigit(d[2]) &&
               isdigit(d[3]) &&
               isdigit(d[4]) &&
               isdigit(d[5]) &&
               isdigit(d[6]) &&
               isdigit(d[7]);
    }else{
        return false;
    }
}

void Persona::setDni(const char *d){
    strcpy(dni, d);
}

void Persona::setNombre(const char *n){
    strcpy(nombre, n);
}

void Persona::setApellido(const char *a){
    strcpy(apellido, a);
}

void Persona::setMail(const char *m){
    strcpy(mail, m);
}

void Persona::setFechaNacimiento(Fecha fechaNac){
    fechaNacimiento = fechaNac;
}

void Persona::setDomicilio(Domicilio domi){
    domicilio = domi;
}

void Persona::setEstado(bool e){
    estado = e;
}

const char* Persona::getDni(){
    return dni;
}

const char* Persona::getNombre(){
    return nombre;
}

const char* Persona::getApellido(){
    return apellido;
}

const char* Persona::getMail(){
    return mail;
}

Fecha Persona::getFechaNacimiento(){
    return fechaNacimiento;
}

Domicilio Persona::getDomicilio(){
    return domicilio;
}

bool Persona::getEstado(){
    return estado;
}

void Persona::Cargar(const char *d, Fecha fN){
    strcpy(dni, d);
    fechaNacimiento = fN;
    cout<<"Nombre: ";
    cargarCadena(nombre, 20);
    cout<<"Apellido: ";
    cargarCadena(apellido, 20);
    cout<<"Mail: ";
    cargarCadena(mail, 30);
    cout<<"Domicilio: " << endl;
    domicilio.Cargar();
}

void Persona::Mostrar(){
    cout<<"DNI: "<<dni<<endl;
    cout<<"Nombre: "<<nombre<<endl;
    cout<<"Apellido: "<<apellido<<endl;
    cout<<"Mail: "<<mail<<endl;
    cout<<"Fecha de nacimiento: ";
    fechaNacimiento.mostrarFecha();
    cout<<"Domicilio: "<<endl;
    domicilio.Mostrar();
}

Persona::~Persona(){

}
