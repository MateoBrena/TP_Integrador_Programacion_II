#include <iostream>
#include <cstring>
#include <iomanip>
#include <sstream>
#include "clsVenta.h"
using namespace std;

Venta::Venta(int n, Fecha f, int nC, int nV, int nVeh, int iM, float m){
    nroVenta = n;
    fechaVenta = f;
    nroCliente = nC;
    nroVendedor = nV;
    nroVehiculo = nVeh;
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

void Venta::setNroCliente(int nC){
    nroCliente = nC;
}

void Venta::setNroVendedor(int nV){
    nroVendedor = nV;
}

void Venta::setNroVehiculo(int nVeh){
    nroVehiculo = nVeh;
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

int Venta::getNroCliente(){
    return nroCliente;
}

int Venta::getNroVendedor(){
    return nroVendedor;
}

int Venta::getNroVehiculo(){
    return nroVehiculo;
}

int Venta::getIdMarcaVehiculo(){
    return idMarcaVehiculo;
}

float Venta::getMonto(){
    return monto;
}

string Venta::getMontoFormato(){
    float montoFloat = getMonto();
    stringstream ss;
    ss << "$" << fixed << setprecision(2) << montoFloat;

    return ss.str();
}

bool Venta::getEstado(){
    return estado;
}

void Venta::Cargar(int n, Fecha f, int nC, int nV, int nVeh, int iM, float m){
    nroVenta = n;
    fechaVenta = f;
    nroCliente = nC;
    nroVendedor = nV;
    nroVehiculo = nVeh;
    idMarcaVehiculo = iM;
    monto = m;
}

void Venta::Mostrar(){
    cout << fixed << setprecision(2);
    cout << endl << "Numero de venta: " << nroVenta << endl;
    cout << "Fecha: " << fechaVenta.mostrarFechaFormato() << endl;
    cout << "ID de cliente: " << nroCliente << endl;
    cout << "ID de vendedor: " << nroVendedor << endl;
    cout << "ID de vehiculo: " << nroVehiculo << endl;
    cout << "ID marca de vehiculo: " << idMarcaVehiculo << endl;
    cout << "Monto: $" << monto << endl;
}

Venta::~Venta(){
}
