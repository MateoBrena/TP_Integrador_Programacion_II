#include <iostream>
#include "clsFecha.h"
using namespace std;

bool Fecha::esBisiesto(int a){
    return (a % 4 == 0 && a % 100 != 0) || (a % 400 == 0);
}

bool Fecha::esValida(int d, int m, int a){

    if (a < 1 || m < 1 || m > 12 || d < 1){
        return false;
    }

    int diasPorMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (m == 2 && esBisiesto(a)){
        diasPorMes[1] = 29;
    }

    return d <= diasPorMes[m-1];
}

Fecha::Fecha(int d, int m, int a){

    if (esValida(d, m, a)){
        dia = d;
        mes = m;
        anio = a;
    }
    else{
        dia = 1;
        mes = 1;
        anio = 1900;
    }
}

int Fecha::getDia(){
    return dia;
}

int Fecha::getMes(){
    return mes;
}

int Fecha::getAnio(){
    return anio;
}

bool Fecha::setDia(int d){

    if (esValida(d, mes, anio)){
        dia = d;
        return true;
    }
    return false;
}

bool Fecha::setMes(int m){

    if (esValida(dia, m, anio)){
        mes = m;
        return true;
    }
    return false;
}

bool Fecha::setAnio(int a){

    if (esValida(dia, mes, a)){
        anio = a;
        return true;
    }
    return false;
}

void Fecha::setHoy(){
    time_t t = time(NULL);
    tm * hoy = localtime(&t);
    dia = hoy->tm_mday;
    mes = hoy->tm_mon+1;
    anio = hoy->tm_year+1900;
}

void Fecha::cargarFecha(){
    int d, m, a;
    bool fechaCorrecta = false;

    do{
        cout << "Ingrese el dia: ";
        cin >> d;
        cout << "Ingrese el mes: ";
        cin >> m;
        cout << "Ingrese el anio: ";
        cin >> a;

        if (esValida(d, m, a)){
            dia = d;
            mes = m;
            anio = a;
            fechaCorrecta = true;
        }else{
            cout << "Error: La fecha ingresada no existe. Intente nuevamente.\n" << endl;
        }
    }
    while (!fechaCorrecta);
}

void Fecha::mostrarFecha(){
    cout << dia << "/" << mes << "/" << anio << endl;
}

string Fecha::mostrarFechaFormato(){
    return to_string(dia) + "/" + to_string(mes) + "/" + to_string(anio);
}

bool Fecha::operator<(Fecha obj){
    if(anio < obj.anio or (anio == obj.anio and mes < obj.mes) or (anio == obj.anio and mes == obj.mes and dia < obj.dia)){
        return true;
    }
    return false;
}

bool Fecha::operator<=(Fecha obj){
    if(anio < obj.anio or (anio == obj.anio and mes < obj.mes) or (anio == obj.anio and mes == obj.mes and dia <= obj.dia)){
        return true;
    }
    return false;
}

bool Fecha::operator>(Fecha obj){
    if(anio > obj.anio or (anio == obj.anio and mes > obj.mes) or (anio == obj.anio and mes == obj.mes and dia > obj.dia)){
        return true;
    }
    return false;
}

bool Fecha::operator>=(Fecha obj){
    if(anio > obj.anio or (anio == obj.anio and mes > obj.mes) or (anio == obj.anio and mes == obj.mes and dia >= obj.dia)){
        return true;
    }
    return false;
}

Fecha::~Fecha(){

}
