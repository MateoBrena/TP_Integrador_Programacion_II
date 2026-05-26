#include <iostream>
#include <cstring>
#include "clsPersona.h"
#include "cargarCadena.h"
using namespace std;

Persona::Persona(const char *n, const char *a, int d, const char *m, Fecha fN, Domicilio dom){
    strcpy(nombre, n);
    strcpy(apellido, a);
    dni = d;
    strcpy(mail, m);
    fechaNacimiento = fN;
    domicilio = dom;
    estado = true;
}

void Persona::setNombre(const char *n){
    strcpy(nombre, n);
}

void Persona::setApellido(const char *a){
    strcpy(apellido, a);
}

void Persona::setDni(int d){
    dni = d;
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

const char* Persona::getNombre(){
    return nombre;
}

const char* Persona::getApellido(){
    return apellido;
}

int Persona::getDni(){
    return dni;
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

void Persona::Cargar(){
    cout<<"Nombre: ";
    cargarCadena(nombre, 50);
    cout<<"Apellido: ";
    cargarCadena(apellido, 50);
    cout<<"DNI: ";
    cin>>dni;
    cout<<"Mail: ";
    cargarCadena(mail, 30);
    cout<<"Fecha de nacimiento: ";
    fechaNacimiento.cargarFecha();
    cout<<"Domicilio: ";
    domicilio.cargar();
}

void Persona::Mostrar(){
    cout<<"Nombre: "<<nombre<<endl;
    cout<<"Apellido: "<<apellido<<endl;
    cout<<"DNI: "<<dni<<endl;
    cout<<"Mail: "<<mail<<endl;
    cout<<"Fecha de nacimiento: ";
    fechaNacimiento.mostrarFecha();
    cout<<"Domicilio: "<<endl;
    domicilio.mostrar();
}

Persona::~Persona(){

}
