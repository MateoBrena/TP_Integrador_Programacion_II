#include <iostream>
#include <cstring>
#include <iomanip>
#include "clsReporte.h"
#include "cargarCadena.h"
using namespace std;

Reporte::Reporte(){
}

int Reporte::buscarMayor(int *vec, int tam){
    int mayor = 0;
    int pos;

    for(int i=0; i<tam; i++){
        if(vec[i]>mayor){
            mayor = vec[i];
            pos = i;
        }
    }
    return pos;
}

int Reporte::buscarMayor(float *vec, int tam){
    float mayor = 0.00;
    int pos;

    for(int i=0; i<tam; i++){
        if(vec[i]>mayor){
            mayor = vec[i];
            pos = i;
        }
    }
    return pos;
}

void Reporte::clienteMasComproUnidades(){
    ArchivoClientes arcCli;
    int cantClientes = arcCli.contarRegistros();
    if(cantClientes <= 0){
        cout << endl <<"Error: No hay ningun cliente cargado."<<endl;
        return;
    }
    int *unidadesxCliente;
    unidadesxCliente = new int[cantClientes]{};
    if(unidadesxCliente==NULL){
        cout << endl << "ERROR DE ASIGNACION DE MEMORIA";
        return;
    }
    ArchivoVentas arcVen;
    int cantVentas = arcVen.contarRegistros();
    if(cantVentas <= 0){
        cout << endl <<"Error: No hay ninguna venta cargada."<<endl;
        return;
    }
    Cliente c;
    Venta v;
    for(int i=0; i<cantClientes; i++){
        c = arcCli.leerRegistro(i);
        for(int j=0; j<cantVentas; j++){
            v = arcVen.leerRegistro(j);
            if((c.getEstado() && v.getEstado()) && c.getNroCliente() == v.getNroCliente()){
                unidadesxCliente[i]++;
            }
        }
    }
    int pos = buscarMayor(unidadesxCliente, cantClientes);
    c = arcCli.leerRegistro(pos);
    c.Mostrar();
    cout << endl << "Cantidad de unidades compradas: " << unidadesxCliente[pos] << endl;

    delete[] unidadesxCliente;
}

void Reporte::clienteMasComproMonto(){
    ArchivoClientes arcCli;
    int cantClientes = arcCli.contarRegistros();
    if(cantClientes <= 0){
        cout << endl <<"Error: No hay ningun cliente cargado."<<endl;
        return;
    }
    float *montoxCliente;
    montoxCliente = new float[cantClientes]{};
    if(montoxCliente==NULL){
        cout << endl << "ERROR DE ASIGNACION DE MEMORIA";
        return;
    }
    ArchivoVentas arcVen;
    int cantVentas = arcVen.contarRegistros();
    if(cantVentas <= 0){
        cout << endl <<"Error: No hay ninguna venta cargada."<<endl;
        return;
    }
    Cliente c;
    Venta v;
    for(int i=0; i<cantClientes; i++){
        c = arcCli.leerRegistro(i);
        for(int j=0; j<cantVentas; j++){
            v = arcVen.leerRegistro(j);
            if((c.getEstado() && v.getEstado()) && c.getNroCliente() == v.getNroCliente()){
                montoxCliente[i]+=v.getMonto();
            }
        }
    }
    int pos = buscarMayor(montoxCliente, cantClientes);
    c = arcCli.leerRegistro(pos);
    cout << fixed << setprecision(2);
    c.Mostrar();
    cout << endl << "Monto de unidades compradas: $" << montoxCliente[pos] << endl;
    delete[] montoxCliente;
}

void Reporte::cantVendedoresSinventas(){
    int mes = cargarEntero("Ingrese el mes del periodo a consultar: ");
    if(mes < 1 || mes > 12){
        cout << endl << "Error: El mes ingresado no es valido" << endl;
        return;
    }
    int anio = cargarEntero("Ingrese el anio del periodo a consultar: ");
    ArchivoVendedores arcVend;
    int cantVendedores = arcVend.contarRegistros();
    if(cantVendedores <= 0){
        cout << endl <<"Error: No hay ningun vendedor cargado."<<endl;
        return;
    }
    ArchivoVentas arcVen;
    int cantVentas = arcVen.contarRegistros();
    if(cantVentas <= 0){
        cout << endl <<"Error: No hay ninguna venta cargada."<<endl;
        return;
    }
    int *ventasxVend;
    ventasxVend = new int[cantVendedores]{};
    if(ventasxVend==NULL){
        cout << endl << "ERROR DE ASIGNACION DE MEMORIA";
        return;
    }
    Vendedor ve;
    Venta v;
    for(int i=0; i<cantVendedores; i++){
        ve = arcVend.leerRegistro(i);
        for(int j=0; j<cantVentas; j++){
            v = arcVen.leerRegistro(j);
            if(v.getFechaVenta().getMes() == mes && v.getFechaVenta().getAnio() == anio){
                if(v.getNroVendedor() == ve.getNroVendedor() && v.getEstado() && ve.getEstado()){
                    ventasxVend[ve.getNroVendedor()-1]++;
                }
            }
        }
    }
    int vendedoresSinVentas = 0;
    for(int i=0; i<cantVendedores; i++){
        if(ventasxVend[i] == 0){
            vendedoresSinVentas++;
        }
    }
    const int CANTMESES = 12;
    string meses[CANTMESES]{"Enero","Febrero","Marzo","Abril","Mayo","Junio","Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre"};
    cout << endl << "Cantidad de vendedores sin ventas en " << meses[mes-1] << " de " << anio << ": " << vendedoresSinVentas << endl;
    cout << endl << "Cantidad total de vendedores: " << cantVendedores << endl;
    delete[] ventasxVend;
}

void Reporte::mayorVendedor(){
    ArchivoVendedores arcVend;
    int cantVendedores = arcVend.contarRegistros();
    if(cantVendedores <= 0){
        cout << endl <<"Error: No hay ningun vendedor cargado."<<endl;
        return;
    }
    float *montoxVendedor;
    montoxVendedor = new float[cantVendedores]{};
    if(montoxVendedor==NULL){
        cout << endl << "ERROR DE ASIGNACION DE MEMORIA";
        return;
    }
    int *ventasxVendedor;
    ventasxVendedor = new int[cantVendedores]{};
    if(ventasxVendedor==NULL){
        cout << endl << "ERROR DE ASIGNACION DE MEMORIA";
        return;
    }
    ArchivoVentas arcVent;
    int cantVentas = arcVent.contarRegistros();
    if(cantVentas <= 0){
        cout << endl <<"Error: No hay ninguna venta cargada."<<endl;
        return;
    }
    Vendedor ve;
    Venta v;
    ArchivoCategorias arcCat;
    CategoriaVendedor c;
    for(int i=0; i<cantVendedores; i++){
        ve = arcVend.leerRegistro(i);
        for(int j=0; j<cantVentas; j++){
            v = arcVent.leerRegistro(j);
            if((ve.getEstado() && v.getEstado()) && ve.getNroVendedor() == v.getNroVendedor()){
                int nroCat = ve.getCategoria();
                c = arcCat.leerRegistro(nroCat-1);
                float monto = v.getMonto() * (c.getPorcentajeComision()/100.00);
                montoxVendedor[i]+= monto;
                ventasxVendedor[i]++;
            }
        }
    }
    int pos = buscarMayor(montoxVendedor, cantVendedores);
    ve = arcVend.leerRegistro(pos);
    cout << fixed << setprecision(2);
//    for(int i=0; i<cantVendedores; i++){
//        cout << montoxVendedor[i] << endl;
//    }
//    cout << endl;
//    for(int i=0; i<cantVendedores; i++){
//        cout << ventasxVendedor[i] << endl;
//    }
    ve.Mostrar();
    cout << endl << "Comision por ventas: $" << montoxVendedor[pos] << endl;
    cout << "Unidades vendidas: " << ventasxVendedor[pos] << endl;
    delete[] montoxVendedor;
    delete[] ventasxVendedor;
}

void Reporte::marcaMasVendida(){
    ArchivoMarcas arcMar;
    int cantMarcas = arcMar.contarRegistros();
    if(cantMarcas <= 0){
        cout << endl <<"Error: No hay ningun cliente cargado."<<endl;
        return;
    }
    int *unidadesxMarca;
    unidadesxMarca = new int[cantMarcas]{};
    if(unidadesxMarca==NULL){
        cout << endl << "ERROR DE ASIGNACION DE MEMORIA";
        return;
    }
    ArchivoVentas arcVen;
    int cantVentas = arcVen.contarRegistros();
        if(cantVentas <= 0){
        cout << endl <<"Error: No hay ninguna venta cargada."<<endl;
        return;
    }
    Marca m;
    Venta v;
    for(int i=0; i<cantMarcas; i++){
        m = arcMar.leerRegistro(i);
        for(int j=0; j<cantVentas; j++){
            v = arcVen.leerRegistro(j);
            if(v.getEstado() && m.getId() == v.getIdMarcaVehiculo()){
                unidadesxMarca[i]++;
            }
        }
    }
    int pos = buscarMayor(unidadesxMarca, cantMarcas);
    m = arcMar.leerRegistro(pos);
    m.Mostrar();
    cout << endl << "Cantidad de unidades vendidas: " << unidadesxMarca[pos] << endl;
    delete[] unidadesxMarca;
}

void Reporte::ventasxMes(){
    ArchivoVentas arcVen;
    int cantVentas = arcVen.contarRegistros();
        if(cantVentas <= 0){
        cout << endl <<"Error: No hay ninguna venta cargada."<<endl;
        return;
    }
    const int CANTMESES = 12;
    string meses[CANTMESES]{"Enero","Febrero","Marzo","Abril","Mayo","Junio","Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre"};
    int vxMes[CANTMESES]{};
    Venta v;
    for(int i=0; i<cantVentas; i++){
        v = arcVen.leerRegistro(i);
        if(v.getEstado()){
            int mesVenta = v.getFechaVenta().getMes();
            vxMes[mesVenta-1]++;
        }
    }
    cout << "Ventas por mes (historico):" << endl << endl;
    for(int i=0; i<CANTMESES; i++){
        cout << meses[i] << ": " << vxMes[i] << " unidades"<< endl;
    }
}

Reporte::~Reporte(){
}
