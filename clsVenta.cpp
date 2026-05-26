#include <iostream>
#include "clsVenta.h"
using namespace std;

Venta::Venta(){

}

void Venta::setNroVenta(int nV){
    nroVenta = nV;
}

void Venta::setFechaVenta(Fecha fV){
    fechaVenta = fV;
}

void Venta::setCuitCliente(int cC){
    cuitCliente = cC;
}

void Venta::setNroVendedor(int nV){
    nroVendedor = nV;
}

void Venta::setidVehiculo(int iV){
    idVehiculo = iV;
}

void Venta::setMonto(float m){
    monto = m;
}

void Venta::setEstado(bool e){
    estado = e;
}

int Venta::getNroVenta(){
    return nroVenta;
}

Fecha Venta::getFechaVenta(){
    return fechaVenta;
}

int Venta::getCuitCliente(){
    return cuitCliente;
}

int Venta::getNroVendedor(){
    return nroVendedor;
}

int Venta::getIdVehiculo(){
    return idVehiculo;
}

float Venta::getMonto(){
    return monto;
}

bool Venta::getEstado(){
    return estado;
}

void Venta::Cargar(){

}

void Venta::Mostrar(){

}

Venta::~Venta(){
}
