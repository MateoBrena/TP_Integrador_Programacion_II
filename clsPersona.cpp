#include <iostream>
#include <cstring>
#include "clsPersona.h"
#include "cargarCadena.h"
using namespace std;

Persona::Persona(int d, const char *n, const char *a, const char *m, Fecha fN, Domicilio dom){
    dni = d;
    strcpy(nombre, n);
    strcpy(apellido, a);
    strcpy(mail, m);
    fechaNacimiento = fN;
    domicilio = dom;
    estado = true;
}

void Persona::setDni(int d){
    dni = d;
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

int Persona::getDni(){
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

void Persona::Cargar(int d){
    if(d == -1){
        cout<<"DNI: ";
        cin>>dni;
    }else{
        dni = d;
    }
    cout<<"Nombre: ";
    cargarCadena(nombre, 20);
    cout<<"Apellido: ";
    cargarCadena(apellido, 20);
    cout<<"Mail: ";
    cargarCadena(mail, 30);
    cout<<"Fecha de nacimiento: " << endl;
    fechaNacimiento.cargarFecha();
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
