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
    ArchivoClientes arcCli;
    int pos = arcCli.buscarRegistro(d);
    if(pos < 0){
        cout << "El DNI ingresado no existe en el archivo" << endl;
        return;
    }
    Cliente obj = arcCli.leerRegistro(pos);
    obj.Mostrar();
}

void ArchivoClientes::altaCliente(){
    Cliente obj;
    int d;
    cout << "Ingrese el DNI del cliente: ";
    cin >> d;
    if(d <= 0){
        cout << "Error: No se puede ingresar un DNI igual o menor a cero" << endl;
        return;
    }
    ArchivoClientes arcCli;
    int pos = arcCli.buscarRegistro(d);
    if(pos >= 0){
        cout << endl << "Error: Ya existe un cliente con ese DNI" << endl;
        return;
    }
    int cant = arcCli.contarRegistros();
    if(cant <0) cant = 0;
    int nro = cant + 1;
    obj.Cargar(d, nro);
    if(arcCli.grabarRegistro(obj)==false){
        cout<<"Error al grabar el registro"<<endl;
    }
}

void ArchivoClientes::modificarNombre(){
    int d;
    cout<<"Ingrese el DNI del cliente: ";
    cin>>d;
    ArchivoClientes arcCli;
    int pos = arcCli.buscarRegistro(d);
    if(pos < 0){
        cout << "El DNI ingresado no existe en el archivo" << endl;
        return;
    }
    Cliente obj;
    obj = arcCli.leerRegistro(pos);
    char nomAux[50];
    cout << "Ingrese el nuevo nombre: ";
    cargarCadena(nomAux, 50);
    obj.setNombre(nomAux);
    if(arcCli.modificarRegistro(obj, pos)){
        cout << endl << "Nombre modificado!" << endl;
    }else{
        cout << endl << "Error al modificar el nombre" << endl;
    }
}

void ArchivoClientes::modificarApellido(){
    int d;
    cout<<"Ingrese el DNI del cliente: ";
    cin>>d;
    ArchivoClientes arcCli;
    int pos = arcCli.buscarRegistro(d);
    if(pos < 0){
        cout << "El DNI ingresado no existe en el archivo" << endl;
        return;
    }
    Cliente obj;
    obj = arcCli.leerRegistro(pos);
    char apAux[50];
    cout << "Ingrese el nuevo apellido: ";
    cargarCadena(apAux, 50);
    obj.setApellido(apAux);
    if(arcCli.modificarRegistro(obj, pos)){
        cout << endl << "Apellido modificado!" << endl;
    }else{
        cout << endl << "Error al modificar el apellido" << endl;
    }
}

void ArchivoClientes::modificarFechaNacimiento(){
    int d;
    cout<<"Ingrese el DNI del cliente: ";
    cin>>d;
    ArchivoClientes arcCli;
    int pos = arcCli.buscarRegistro(d);
    if(pos < 0){
        cout << "El DNI ingresado no existe en el archivo" << endl;
        return;
    }
    Cliente obj;
    obj = arcCli.leerRegistro(pos);
    Fecha faux;
    cout << "Ingrese la nueva fecha de nacimiento: " << endl;
    faux.cargarFecha();
    obj.setFechaNacimiento(faux);
    if(arcCli.modificarRegistro(obj, pos)){
        cout << endl << "Fecha de nacimiento modificada!" << endl;
    }else{
        cout << endl << "Error al modificar la fecha de nacimiento" << endl;
    }
}

void ArchivoClientes::modificarMail(){
    int d;
    cout<<"Ingrese el DNI del cliente: ";
    cin>>d;
    ArchivoClientes arcCli;
    int pos = arcCli.buscarRegistro(d);
    if(pos < 0){
        cout << "El DNI ingresado no existe en el archivo" << endl;
        return;
    }
    Cliente obj;
    obj = arcCli.leerRegistro(pos);
    char mAux[30];
    cout << "Ingrese el nuevo mail: ";
    cargarCadena(mAux, 30);
    obj.setMail(mAux);
    if(arcCli.modificarRegistro(obj, pos)){
        cout << endl << "Mail modificado!" << endl;
    }else{
        cout << endl << "Error al modificar el mail" << endl;
    }
}

void ArchivoClientes::modificarDomicilio(){
    int d;
    cout<<"Ingrese el DNI del cliente: ";
    cin>>d;
    ArchivoClientes arcCli;
    int pos = arcCli.buscarRegistro(d);
    if(pos < 0){
        cout << "El DNI ingresado no existe en el archivo" << endl;
        return;
    }
    Cliente obj;
    obj = arcCli.leerRegistro(pos);
    Domicilio dAux;
    dAux.Cargar();
    obj.setDomicilio(dAux);
    if(arcCli.modificarRegistro(obj, pos)){
        cout << endl << "Domicilio modificado!" << endl;
    }else{
        cout << endl << "Error al modificar el domicilio" << endl;
    }
}

void ArchivoClientes::modificarTelefono(){
    int d;
    cout<<"Ingrese el DNI del cliente: ";
    cin>>d;
    ArchivoClientes arcCli;
    int pos = arcCli.buscarRegistro(d);
    if(pos < 0){
        cout << "El DNI ingresado no existe en el archivo" << endl;
        return;
    }
    Cliente obj;
    obj = arcCli.leerRegistro(pos);
    char tAux[12];
    cout << "Ingrese el nuevo telefono: ";
    cargarCadena(tAux, 12);
    obj.setTelefono(tAux);
    if(arcCli.modificarRegistro(obj, pos)){
        cout << endl << "Telefono modificado!" << endl;
    }else{
        cout << endl << "Error al modificar el telefono" << endl;
    }
}

void ArchivoClientes::bajaCliente(){
    ArchivoClientes arcCli;
    cout<<"Ingrese el DNI del cliente: ";
    int d;
    cin>>d;
    int pos = arcCli.buscarRegistro(d);
    if(pos < 0){
        cout<<"El DNI ingresado no existe en el archivo"<<endl;
        return;
    }
    Cliente obj;
    obj = arcCli.leerRegistro(pos);
    if(obj.getEstado() == false){
        cout<<"El cliente ya se encuentra dado de baja"<<endl;
        return;
    }
    obj.setEstado(false);
    if(arcCli.modificarRegistro(obj, pos)){
        cout<<"Baja realizada correctamente"<<endl;
    }else{
        cout<<"Error al realizar la baja"<<endl;
    }
}
