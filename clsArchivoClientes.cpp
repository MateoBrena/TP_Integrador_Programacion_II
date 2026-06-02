#include <iostream>
#include <cstring>
#include "clsArchivoClientes.h"
#include "cargarCadena.h"
using namespace std;

ArchivoClientes::ArchivoClientes(const char *n){
    strcpy(nombre, n);
}

Cliente ArchivoClientes::leerRegistro(int pos){

    FILE *p = fopen(nombre,"rb");
    Cliente obj;
    if(p == nullptr){
        obj.setDni(-2);
        return obj;
    }
    obj.setDni(-1);
    fseek(p,  sizeof obj * pos, 0);
    fread(&obj, sizeof obj, 1, p);
    fclose(p);

    return obj;

}

bool ArchivoClientes::grabarRegistro(Cliente obj){

    FILE *p = fopen(nombre, "ab");
    if(p == nullptr){
        return false;
    }
    bool escribio = fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
    return escribio;
}

bool ArchivoClientes::modificarRegistro(Cliente obj, int pos){

    FILE *p = fopen(nombre, "rb+");
    if(p == nullptr){
        return false;
    }
    fseek(p, sizeof obj * pos, 0);
    bool escribio = fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
    return escribio;
}

int ArchivoClientes::contarRegistros(){

    FILE *p = fopen(nombre, "rb");
    if(p == nullptr){
        return -1;
    }
    fseek(p,0,2);
    int cant = ftell(p)/sizeof(Cliente);
    fclose(p);
    return cant;
}

int ArchivoClientes::contarRegistrosActivos(int ca){

    int cantActivos = 0;
    for(int i=0; i<ca; i++){
        Cliente c = leerRegistro(i);
        if(c.getEstado()){
            cantActivos++;
        }
    }

    return cantActivos;
}

int ArchivoClientes::buscarRegistro(int d){

    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++){
        Cliente obj = leerRegistro(i);
        if(obj.getDni() == d){
            return i;
        }
    }

    return -1;
}

int ArchivoClientes::buscarRegistroxCUIT(const char *d){

    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++){
        Cliente obj = leerRegistro(i);
        if(strcmp(obj.getCuit(),d) == 0){
            return i;
        }
    }

    return -1;
}

void ArchivoClientes::listarRegistros(){

    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++){
        Cliente obj = leerRegistro(i);
        if(obj.getEstado()){
            obj.Mostrar();
            cout << endl;
        }
    }
}

void ArchivoClientes::buscarPorDni(){
    int d;
    cout<<"Ingrese el DNI del cliente: ";
    cin>>d;
    int pos = buscarRegistro(d);
    if(pos < 0){
        cout << endl << "El DNI ingresado no existe en el archivo" << endl;
        return;
    }
    Cliente obj = leerRegistro(pos);
    if(obj.getEstado()){
        obj.Mostrar();
    }else{
        cout << endl << "Error: el cliente con DNI " << d << " se encuentra dado de baja.";
    }

}

void ArchivoClientes::altaCliente(){
    Cliente obj;
    int d;
    cout << "Ingrese el DNI del cliente: ";
    cin >> d;
    if(d <= 0){
        cout << endl << "Error: No se puede ingresar un DNI igual o menor a cero" << endl;
        return;
    }
    int pos = buscarRegistro(d);
    if(pos >= 0){
        cout << endl << "Error: Ya existe un cliente con ese DNI" << endl;
        return;
    }
    int cant = contarRegistros();
    if(cant <0) cant = 0;
    int nro = cant + 1;
    obj.Cargar(d, nro);
    if(grabarRegistro(obj)){
        cout << endl << "Registro grabado exitosamente!" << endl;
    }else{
        cout << endl <<"Error al grabar el registro"<<endl;
    }
}

void ArchivoClientes::modificarNombre(){
    int d;
    cout<<"Ingrese el DNI del cliente: ";
    cin>>d;
    int pos = buscarRegistro(d);
    if(pos < 0){
        cout << endl << "El DNI ingresado no existe en el archivo" << endl;
        return;
    }
    Cliente obj;
    obj = leerRegistro(pos);
    char nomAux[50];
    cout << "Ingrese el nuevo nombre: ";
    cargarCadena(nomAux, 50);
    obj.setNombre(nomAux);
    if(modificarRegistro(obj, pos)){
        cout << endl << "Nombre modificado!" << endl;
    }else{
        cout << endl << "Error al modificar el nombre" << endl;
    }
}

void ArchivoClientes::modificarApellido(){
    int d;
    cout<<"Ingrese el DNI del cliente: ";
    cin>>d;
    int pos = buscarRegistro(d);
    if(pos < 0){
        cout << endl << "El DNI ingresado no existe en el archivo" << endl;
        return;
    }
    Cliente obj;
    obj = leerRegistro(pos);
    char apAux[50];
    cout << "Ingrese el nuevo apellido: ";
    cargarCadena(apAux, 50);
    obj.setApellido(apAux);
    if(modificarRegistro(obj, pos)){
        cout << endl << "Apellido modificado!" << endl;
    }else{
        cout << endl << "Error al modificar el apellido" << endl;
    }
}

void ArchivoClientes::modificarFechaNacimiento(){
    int d;
    cout<<"Ingrese el DNI del cliente: ";
    cin>>d;
    int pos = buscarRegistro(d);
    if(pos < 0){
        cout << endl << "El DNI ingresado no existe en el archivo" << endl;
        return;
    }
    Cliente obj;
    obj = leerRegistro(pos);
    Fecha faux;
    cout << "Ingrese la nueva fecha de nacimiento: " << endl;
    faux.cargarFecha();
    obj.setFechaNacimiento(faux);
    if(modificarRegistro(obj, pos)){
        cout << endl << "Fecha de nacimiento modificada!" << endl;
    }else{
        cout << endl << "Error al modificar la fecha de nacimiento" << endl;
    }
}

void ArchivoClientes::modificarMail(){
    int d;
    cout<<"Ingrese el DNI del cliente: ";
    cin>>d;
    int pos = buscarRegistro(d);
    if(pos < 0){
        cout << endl << "El DNI ingresado no existe en el archivo" << endl;
        return;
    }
    Cliente obj;
    obj = leerRegistro(pos);
    char mAux[30];
    cout << "Ingrese el nuevo mail: ";
    cargarCadena(mAux, 30);
    obj.setMail(mAux);
    if(modificarRegistro(obj, pos)){
        cout << endl << "Mail modificado!" << endl;
    }else{
        cout << endl << "Error al modificar el mail" << endl;
    }
}

void ArchivoClientes::modificarDomicilio(){
    int d;
    cout<<"Ingrese el DNI del cliente: ";
    cin>>d;
    int pos = buscarRegistro(d);
    if(pos < 0){
        cout << endl << "El DNI ingresado no existe en el archivo" << endl;
        return;
    }
    Cliente obj;
    obj = leerRegistro(pos);
    Domicilio dAux;
    dAux.Cargar();
    obj.setDomicilio(dAux);
    if(modificarRegistro(obj, pos)){
        cout << endl << "Domicilio modificado!" << endl;
    }else{
        cout << endl << "Error al modificar el domicilio" << endl;
    }
}

void ArchivoClientes::modificarTelefono(){
    int d;
    cout<<"Ingrese el DNI del cliente: ";
    cin>>d;
    int pos = buscarRegistro(d);
    if(pos < 0){
        cout << endl << "El DNI ingresado no existe en el archivo" << endl;
        return;
    }
    Cliente obj;
    obj = leerRegistro(pos);
    char tAux[12];
    cout << "Ingrese el nuevo telefono: ";
    cargarCadena(tAux, 12);
    obj.setTelefono(tAux);
    if(modificarRegistro(obj, pos)){
        cout << endl << "Telefono modificado!" << endl;
    }else{
        cout << endl << "Error al modificar el telefono" << endl;
    }
}

void ArchivoClientes::bajaCliente(){
    cout<<"Ingrese el DNI del cliente: ";
    int d;
    cin>>d;
    int pos = buscarRegistro(d);
    if(pos < 0){
        cout << endl <<"El DNI ingresado no existe en el archivo"<<endl;
        return;
    }
    Cliente obj;
    obj = leerRegistro(pos);
    if(obj.getEstado() == false){
        cout << endl <<"El cliente ya se encuentra dado de baja"<<endl;
        return;
    }
    obj.setEstado(false);
    if(modificarRegistro(obj, pos)){
        cout << endl <<"Baja realizada correctamente"<<endl;
    }else{
        cout << endl <<"Error al realizar la baja"<<endl;
    }
}

ArchivoClientes::~ArchivoClientes(){
}
