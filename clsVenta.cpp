#include <iostream>
#include <cstring>
#include <iomanip>
#include "clsVenta.h"
using namespace std;

Venta::Venta(int n, Fecha f, const char * cc, int nV, const char *v, float m){
    nroVenta = n;
    fechaVenta = f;
    strcpy(cuitCliente, cc);
    nroVendedor = nV;
    strcpy(patenteVehiculo, v);
    monto = m;
    estado = true;
}

void Venta::setNroVenta(int nV){
    nroVenta = nV;
}

void Venta::setFechaVenta(Fecha fV){
    fechaVenta = fV;
}

void Venta::setCuitCliente(const char *cC){
    strcpy(cuitCliente,cC);
}

void Venta::setNroVendedor(int nV){
    nroVendedor = nV;
}

void Venta::setPatenteVehiculo(const char *pV){
    strcpy(patenteVehiculo,pV);
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

const char * Venta::getCuitCliente(){
    return cuitCliente;
}

int Venta::getNroVendedor(){
    return nroVendedor;
}

const char * Venta::getPatenteVehiculo(){
    return patenteVehiculo;
}

float Venta::getMonto(){
    return monto;
}

bool Venta::getEstado(){
    return estado;
}

void Venta::Cargar(int n, Fecha f, const char *cC, int nV, const char *pV, float m){
    nroVenta = n;
    fechaVenta = f;
    strcpy(cuitCliente, cC);
    nroVendedor = nV;
    strcpy(patenteVehiculo, pV);
    monto = m;
}

void Venta::Mostrar(){
    cout << fixed << setprecision(2);
    cout << "Numero de venta: " << nroVenta << endl;
    cout << "Fecha: " << fechaVenta.mostrarFechaFormato() << endl;
    cout << "CUIT del cliente: " << cuitCliente << endl;
    cout << "Numero de vendedor: " << nroVendedor << endl;
    cout << "Patente del vehiculo: " << patenteVehiculo << endl;
    cout << "Monto: $" << monto << endl;
}

Venta::~Venta(){
}
