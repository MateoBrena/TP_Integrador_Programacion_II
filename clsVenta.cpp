#include <iostream>
#include <cstring>
#include <iomanip>
#include "clsVenta.h"
using namespace std;

Venta::Venta(int n, Fecha f, const char * cc, int nV, const char *v, int iM, float m){
    nroVenta = n;
    fechaVenta = f;
    strcpy(cuitCliente, cc);
    nroVendedor = nV;
    strcpy(patenteVehiculo, v);
    idMarcaVehiculo = iM;
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

void Venta::setIdMarcaVehiculo(int d){
    idMarcaVehiculo = d;
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

int Venta::getIdMarcaVehiculo(){
    return idMarcaVehiculo;
}

float Venta::getMonto(){
    return monto;
}

bool Venta::getEstado(){
    return estado;
}

void Venta::Cargar(int n, Fecha f, const char *cC, int nV, const char *pV, int iM, float m){
    nroVenta = n;
    fechaVenta = f;
    strcpy(cuitCliente, cC);
    nroVendedor = nV;
    strcpy(patenteVehiculo, pV);
    idMarcaVehiculo = iM;
    monto = m;
}

void Venta::Mostrar(){
    cout << fixed << setprecision(2);
    cout << "Numero de venta: " << nroVenta << endl;
    cout << "Fecha: " << fechaVenta.mostrarFechaFormato() << endl;
    cout << "CUIT del cliente: " << cuitCliente << endl;
    cout << "Numero de vendedor: " << nroVendedor << endl;
    cout << "Patente del vehiculo: " << patenteVehiculo << endl;
    cout << "ID marca de vehiculo: " << idMarcaVehiculo << endl;
    cout << "Monto: $" << monto << endl;
}

Venta::~Venta(){
}
