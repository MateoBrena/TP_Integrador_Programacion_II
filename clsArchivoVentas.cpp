#include <iostream>
#include <cstring>
#include "clsArchivoVentas.h"
#include "clsArchivoClientes.h"
#include "clsArchivosVendedores.h"
#include "clsArchivoVehiculos.h"
#include "clsArchivoMarcas.h"
#include "cargarCadena.h"
using namespace std;

ArchivoVentas::ArchivoVentas(const char *n){
    strcpy(nombre, n);
}

Venta ArchivoVentas::leerRegistro(int pos){
    FILE *p = fopen(nombre,"rb");
    Venta obj;
    if(p == nullptr){
        obj.setNroVenta(-2);
        return obj;
    }
    obj.setNroVenta(-1);
    fseek(p,  sizeof obj * pos, 0);
    fread(&obj, sizeof obj, 1, p);
    fclose(p);

    return obj;

}

bool ArchivoVentas::grabarRegistro(Venta obj){
    FILE *p = fopen(nombre, "ab");
    if(p == nullptr){
        return false;
    }
    bool escribio = fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
    return escribio;
}

bool ArchivoVentas::modificarRegistro(Venta obj, int pos){
    FILE *p = fopen(nombre, "rb+");
    if(p == nullptr){
        return false;
    }
    fseek(p, sizeof obj * pos, 0);
    bool escribio = fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
    return escribio;
}

int ArchivoVentas::contarRegistros(){
    FILE *p = fopen(nombre, "rb");
    if(p == nullptr){
        return -1;
    }
    fseek(p,0,2);
    int cant = ftell(p)/sizeof(Venta);
    fclose(p);
    return cant;
}

int ArchivoVentas::contarRegistrosActivos(int ca){
    int cantActivos = 0;
    for(int i=0; i<ca; i++){
        Venta c = leerRegistro(i);
        if(c.getEstado()){
            cantActivos++;
        }
    }

    return cantActivos;
}


int ArchivoVentas::buscarRegistro(int d){
    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++){
        Venta obj = leerRegistro(i);
        if(obj.getNroVenta() == d){
            return i;
        }
    }

    return -1;
}

int ArchivoVentas::buscarRegistroActivo(int d){
    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++){
        Venta obj = leerRegistro(i);
        if(obj.getNroVenta() == d && obj.getEstado()){
            return i;
        }
    }

    return -1;
}

void ArchivoVentas::listarRegistros(){
    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++){
        Venta obj = leerRegistro(i);
        if(obj.getEstado()){
            obj.Mostrar();
            cout << endl;
        }
    }
}

void ArchivoVentas::altaVenta(){
    char cc[12];
    cout << "Ingrese el CUIT del cliente (Sin espacios ni guiones): ";
    cin >> cc;
    ArchivoClientes arcCli;
    int pos = arcCli.buscarRegistroxCUIT(cc);
    if(pos < 0){
        cout << endl << "Error: No existe un cliente con el cuit ingresado" << endl;
        return;
    }
    int nv;
    cout << "Ingrese el numero del vendedor que realiza la venta: ";
    cin >> nv;
    ArchivoVendedores arcVen;
    pos = arcVen.buscarRegistroPorNv(nv);
    if(pos < 0){
        cout << endl << "Error: No existe un vendedor con el numero ingresado" << endl;
        return;
    }
    Vehiculo obj;
    char patente[10];
    cout << "Ingrese la patente del vehiculo (Sin espacios): ";
    cin >> patente;
    obj.hacerMayusculas(patente);
    if(!obj.validarPatente(patente)){
        cout << endl << "Error: Patente ingresada con formato invalido." << endl;
        return;
    }
    ArchivoVehiculos arcVeh;
    pos = arcVeh.buscarRegistro(patente);
    if(pos < 0){
        cout << endl << "Error: No existe un vehiculo con la patente ingresada." << endl;
        return;
    }
    obj = arcVeh.leerRegistro(pos);
    int idMarca = obj.getIdMarca();
    ArchivoMarcas arcMar;
    Marca mar;
    int posMarca = arcMar.buscarRegistro(idMarca);
    mar = arcMar.leerRegistro(posMarca);
    if(!mar.getEstado()){
        cout << endl << "Error: No se puede vender un vehiculo con una marca invalida o dada de baja." << endl;
        return;
    }
    idMarca = mar.getId();
    Fecha f;
    Fecha hoy;
    hoy.setHoy();
    f.cargarFecha();
    if(f > hoy){
        cout << endl << "Error: No se puede ingresar una fecha futura." << endl;
        return;
    }
    obj = arcVeh.leerRegistro(pos);
    float m = obj.getPrecio();
    int cant = contarRegistros();
    if(cant <0) cant = 0;
    int nro = cant + 1;
    Venta v;
    v.Cargar(nro, f, cc, nv, patente, idMarca, m);
    if(grabarRegistro(v)){
        cout<< endl <<"Registro grabado exitosamente!"<<endl;
        return;
    }else{
        cout<< endl <<"Error al grabar el registro"<<endl;
        return;
    }
}

void ArchivoVentas::buscarPorId(){
    int d;
    cout << "Ingrese el numero de la venta a buscar: ";
    cin >> d;
    int pos = buscarRegistroActivo(d);
    if(pos < 0){
        cout << endl << "Error: No existe una venta con el ID ingresado" << endl;
        return;
    }
    Venta v = leerRegistro(pos);
    v.Mostrar();
}

void ArchivoVentas::modificarFechaVenta(){
    int id;
    cout << "Ingrese el ID de la venta a modificar: ";
    cin >> id;
    int pos = buscarRegistro(id);
    if(pos < 0){
        cout << endl << "Error: No existe una venta con el ID ingresado" << endl;
        return;
    }
    cout << "Ingrese la nueva fecha: " << endl;
    Fecha fAux;
    fAux.cargarFecha();
    Venta v;
    v = leerRegistro(pos);
    v.setFechaVenta(fAux);
    if(modificarRegistro(v,pos)){
        cout<< endl <<"Registro grabado exitosamente!"<<endl;
        return;
    }else{
        cout<< endl <<"Error al grabar el registro"<<endl;
        return;
    }

}
void ArchivoVentas::modificarCuitCliente(){
    int id;
    cout << "Ingrese el ID de la venta a modificar: ";
    cin >> id;
    int pos = buscarRegistro(id);
    if(pos < 0){
        cout << endl << "Error: No existe una venta con el ID ingresado" << endl;
        return;
    }
    cout << "Ingrese el nuevo CUIT (Sin espacios): " << endl;
    char cuitAux[12];
    cin >> cuitAux;
    ArchivoClientes arcCli;
    int pos2 = arcCli.buscarRegistroxCUIT(cuitAux);
    if(pos2 < 0){
        cout << endl << "Error: No existe un cliente con el CUIT ingresado" << endl;
        return;
    }
    Venta v;
    v = leerRegistro(pos);
    v.setCuitCliente(cuitAux);
    if(modificarRegistro(v,pos)){
        cout<< endl <<"Registro grabado exitosamente!"<<endl;
        return;
    }else{
        cout<< endl <<"Error al grabar el registro"<<endl;
        return;
    }
}
void ArchivoVentas::modificarNroVendedor(){
    int id;
    cout << "Ingrese el ID de la venta a modificar: ";
    cin >> id;
    int pos = buscarRegistro(id);
    if(pos < 0){
        cout << endl << "Error: No existe una venta con el ID ingresado" << endl;
        return;
    }
    cout << "Ingrese el nuevo numero de vendedor: ";
    int nvAux;
    cin >> nvAux;
    ArchivoVendedores arcVen;
    int pos2 = arcVen.buscarRegistroPorNv(nvAux);
    if(pos2 < 0){
        cout << endl << "Error: No existe un vendedor con el ID ingresado" << endl;
        return;
    }
    Venta v;
    v = leerRegistro(pos);
    v.setNroVendedor(nvAux);
    if(modificarRegistro(v,pos)){
        cout<< endl <<"Registro grabado exitosamente!"<<endl;
        return;
    }else{
        cout<< endl <<"Error al grabar el registro"<<endl;
        return;
    }

}
void ArchivoVentas::modificarPatenteVehiculo(){
    int id;
    cout << "Ingrese el ID de la venta a modificar: ";
    cin >> id;
    int pos = buscarRegistro(id);
    if(pos < 0){
        cout << endl << "Error: No existe una venta con el ID ingresado" << endl;
        return;
    }
    ArchivoVehiculos arcVeh;
    Vehiculo veh;
    cout << "Ingrese la nueva patente (Sin espacios): ";
    char patente[10];
    cin >> patente;
    veh.hacerMayusculas(patente);
    if(!veh.validarPatente(patente)){
        cout << endl << "Error: Patente ingresada con formato invalido." << endl;
        return;
    }
    int pos2 = arcVeh.buscarRegistro(patente);
    if(pos2 < 0){
        cout << endl << "Error: La patente ingresada no existe en el archivo." << endl;
        return;
    }
    Venta v;
    v = leerRegistro(pos);
    v.setPatenteVehiculo(patente);
    if(modificarRegistro(v,pos)){
        cout<< endl <<"Registro grabado exitosamente!"<<endl;
        return;
    }else{
        cout<< endl <<"Error al grabar el registro"<<endl;
        return;
    }
}

void ArchivoVentas::modificarMarcaVehiculo(){
    int id;
    cout << "Ingrese el ID de la venta a modificar: ";
    cin >> id;
    int pos = buscarRegistro(id);
    if(pos < 0){
        cout << endl << "Error: No existe una venta con el ID ingresado" << endl;
        return;
    }
    cout << "Ingrese el ID de la nueva marca: ";
    int idAux;
    cin >> idAux;
    ArchivoMarcas arcMar;
    int pos2 = arcMar.buscarRegistro(idAux);
    if(pos2 < 0){
        cout << endl << "Error: No existe una marca con el ID ingresado" << endl;
        return;
    }
    Venta v;
    v = leerRegistro(pos);
    v.setIdMarcaVehiculo(idAux);
    if(modificarRegistro(v,pos)){
        cout<< endl <<"Registro grabado exitosamente!"<<endl;
        return;
    }else{
        cout<< endl <<"Error al grabar el registro"<<endl;
        return;
    }
}

void ArchivoVentas::modificarMonto(){
    int id;
    cout << "Ingrese el ID de la venta a modificar: ";
    cin >> id;
    int pos = buscarRegistro(id);
    if(pos < 0){
        cout << endl << "Error: No existe una venta con el ID ingresado" << endl;
        return;
    }
    cout << "Ingrese el nuevo monto: ";
    int mAux;
    cin >> mAux;
    if(mAux < 0){
        cout << endl << "Error: La venta no puede tener un monto negativo" << endl;
        return;
    }
    Venta v;
    v = leerRegistro(pos);
    v.setMonto(mAux);
    if(modificarRegistro(v,pos)){
        cout<< endl <<"Registro grabado exitosamente!"<<endl;
        return;
    }else{
        cout<< endl <<"Error al grabar el registro"<<endl;
        return;
    }
}

void ArchivoVentas::bajaVenta(){
    cout<<"Ingrese el ID de la venta: ";
    int d;
    cin>>d;
    int pos = buscarRegistro(d);
    if(pos < 0){
        cout << endl << "Error: El ID ingresado no existe en el archivo"<<endl;
        return;
    }
    Venta obj;
    obj = leerRegistro(pos);
    if(obj.getEstado() == false){
        cout << endl <<"La venta ya se encuentra dada de baja"<<endl;
        return;
    }
    obj.setEstado(false);
    if(modificarRegistro(obj, pos)){
        cout << endl <<"Baja realizada correctamente"<<endl;
        return;
    }else{
        cout << endl <<"Error al realizar la baja"<<endl;
        return;
    }
}

ArchivoVentas::~ArchivoVentas(){
}
