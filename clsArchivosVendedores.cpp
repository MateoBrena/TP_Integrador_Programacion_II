#include <iostream>
#include <cstring>
#include "clsArchivosVendedores.h"
#include "clsArchivosCategoriaVendedor.h"
#include "clsArchivoClientes.h"
#include "cargarCadena.h"
using namespace std;


ArchivoVendedores::ArchivoVendedores(const char *n){
    strcpy(nombre, n);
}

Vendedor ArchivoVendedores::leerRegistro(int pos){

    FILE *p = fopen(nombre,"rb");
    Vendedor obj;
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

bool ArchivoVendedores::grabarRegistro(Vendedor obj){

    FILE *p = fopen(nombre, "ab");
    if(p == nullptr){
        return false;
    }
    bool escribio = fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
    return escribio;
}

bool ArchivoVendedores::modificarRegistro(Vendedor obj, int pos){

    FILE *p = fopen(nombre, "rb+");
    if(p == nullptr){
        return false;
    }
    fseek(p, sizeof obj * pos, 0);
    bool escribio = fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
    return escribio;
}

int ArchivoVendedores::contarRegistros(){

    FILE *p = fopen(nombre, "rb");
    if(p == nullptr){
        return -1;
    }
    fseek(p,0,2);
    int cant = ftell(p)/sizeof(Vendedor);
    fclose(p);
    return cant;
}

int ArchivoVendedores::buscarRegistro(int d){

    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++){
        Vendedor obj = leerRegistro(i);
        if(obj.getDni() == d){
            return i;
        }
    }

    return -1;
}

int ArchivoVendedores::buscarRegistroPorNv(int d){

    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++){
        Vendedor obj = leerRegistro(i);
        if(obj.getNroVendedor() == d){
            return i;
        }
    }

    return -1;
}

void ArchivoVendedores::listarRegistros(){

    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++){
        Vendedor obj = leerRegistro(i);
        if(obj.getEstado()){
            obj.Mostrar();
            cout << endl;
        }
    }
}

void ArchivoVendedores::buscarPorDni(){
    int d;
    cout<<"Ingrese el DNI del vendedor: ";
    cin>>d;
    int pos = buscarRegistro(d);
    if(pos < 0){
        cout << endl << "El DNI ingresado no existe en el archivo" << endl;
        return;
    }
    Vendedor obj = leerRegistro(pos);
    if(obj.getEstado()){
        obj.Mostrar();
    }else{
        cout << endl << "Error: el vendedor con DNI " << d << " se encuentra dado de baja.";
        return;
    }
}

void ArchivoVendedores::altaVendedor(){
    Vendedor obj;
    int d;
    cout << "Ingrese el DNI del vendedor: ";
    cin >> d;
    if(d <= 0){
        cout << endl << "Error: No se puede ingresar un DNI igual o menor a cero" << endl;
        return;
    }
    int pos = buscarRegistro(d);
    ArchivoClientes arcCli;
    int pos2 = arcCli.buscarRegistro(d);
    if(pos >= 0 || pos2 >= 0){
        cout << endl << "Error: Ya existe una persona con ese DNI" << endl;
        return;
    }
    Fecha fN;
    Fecha hoy;
    hoy.setHoy();
    cout << "Ingrese la fecha de nacimiento:" << endl;
    fN.cargarFecha();
    if(fN > hoy){
        cout << endl << "Error: No se puede ingresar una fecha futura." << endl;
        return;
    }
    int cat;
    cout << "Ingrese el ID de categoria del vendedor: ";
    cin >> cat;
    ArchivoCategorias arcCat;
    pos = arcCat.buscarRegistroActivo(cat);
    if(pos == -1){
        cout << endl << "Error: no existe una categoria con ese ID" << endl;
        return;
    }
    Fecha fC;
    cout << "Ingrese la fecha de contratacion:" << endl;
    fC.cargarFecha();
    if(fC > hoy){
        cout << endl << "Error: No se puede ingresar una fecha futura." << endl;
        return;
    }
    int cant = contarRegistros();
    if(cant <0) cant = 0;
    int nro = cant + 1;
    obj.Cargar(d, nro, cat, fN, fC);
    if(grabarRegistro(obj)){
        cout<< endl <<"Registro grabado exitosamente!"<<endl;
        return;
    }else{
        cout<< endl <<"Error al grabar el registro"<<endl;
        return;
    }
}

void ArchivoVendedores::modificarNombre(){
    int d;
    cout<<"Ingrese el DNI del vendedor: ";
    cin>>d;
    int pos = buscarRegistro(d);
    if(pos < 0){
        cout << endl << "El DNI ingresado no existe en el archivo" << endl;
        return;
    }
    Vendedor obj;
    obj = leerRegistro(pos);
    char nomAux[50];
    cout << "Ingrese el nuevo nombre: ";
    cargarCadena(nomAux, 50);
    obj.setNombre(nomAux);
    if(modificarRegistro(obj, pos)){
        cout << endl << "Nombre modificado!" << endl;
        return;
    }else{
        cout << endl << "Error al modificar el nombre" << endl;
        return;
    }
}

void ArchivoVendedores::modificarApellido(){
    int d;
    cout<<"Ingrese el DNI del vendedor: ";
    cin>>d;
    int pos = buscarRegistro(d);
    if(pos < 0){
        cout << endl << "El DNI ingresado no existe en el archivo" << endl;
        return;
    }
    Vendedor obj;
    obj = leerRegistro(pos);
    char apAux[50];
    cout << "Ingrese el nuevo apellido: ";
    cargarCadena(apAux, 50);
    obj.setApellido(apAux);
    if(modificarRegistro(obj, pos)){
        cout << endl << "Apellido modificado!" << endl;
        return;
    }else{
        cout << endl << "Error al modificar el apellido" << endl;
        return;
    }
}

void ArchivoVendedores::modificarFechaNacimiento(){
    int d;
    cout<<"Ingrese el DNI del vendedor: ";
    cin>>d;
    int pos = buscarRegistro(d);
    if(pos < 0){
        cout << endl << "El DNI ingresado no existe en el archivo" << endl;
        return;
    }
    Vendedor obj;
    obj = leerRegistro(pos);
    Fecha faux;
    cout << "Ingrese la nueva fecha de nacimiento: " << endl;
    faux.cargarFecha();
    obj.setFechaNacimiento(faux);
    if(modificarRegistro(obj, pos)){
        cout << endl << "Fecha de nacimiento modificada!" << endl;
        return;
    }else{
        cout << endl << "Error al modificar la fecha de nacimiento" << endl;
        return;
    }
}

void ArchivoVendedores::modificarFechaContratacion(){
    int d;
    cout<<"Ingrese el DNI del vendedor: ";
    cin>>d;
    int pos = buscarRegistro(d);
    if(pos < 0){
        cout << "El DNI ingresado no existe en el archivo" << endl;
        return;
    }
    Vendedor obj;
    obj = leerRegistro(pos);
    Fecha faux;
    cout << "Ingrese la nueva Fecha de Contratacion: " << endl;
    faux.cargarFecha();
    obj.setFechaContratacion(faux);
    if(modificarRegistro(obj, pos)){
        cout << endl << "Fecha de Contratacion modificada!" << endl;
        return;
    }else{
        cout << endl << "Error al modificar la fecha de Contratacion" << endl;
        return;
    }
}

void ArchivoVendedores::modificarMail(){
    int d;
    cout<<"Ingrese el DNI del vendedor: ";
    cin>>d;
    int pos = buscarRegistro(d);
    if(pos < 0){
        cout << endl << "El DNI ingresado no existe en el archivo" << endl;
        return;
    }
    Vendedor obj;
    obj = leerRegistro(pos);
    char mAux[30];
    cout << "Ingrese el nuevo mail: ";
    cargarCadena(mAux, 30);
    obj.setMail(mAux);
    if(modificarRegistro(obj, pos)){
        cout << endl << "Mail modificado!" << endl;
        return;
    }else{
        cout << endl << "Error al modificar el mail" << endl;
        return;
    }
}

void ArchivoVendedores::modificarDomicilio(){
    int d;
    cout<<"Ingrese el DNI del vendedor: ";
    cin>>d;
    int pos = buscarRegistro(d);
    if(pos < 0){
        cout << endl << "El DNI ingresado no existe en el archivo" << endl;
        return;
    }
    Vendedor obj;
    obj = leerRegistro(pos);
    Domicilio dAux;
    dAux.Cargar();
    obj.setDomicilio(dAux);
    if(modificarRegistro(obj, pos)){
        cout << endl << "Domicilio modificado!" << endl;
        return;
    }else{
        cout << endl << "Error al modificar el domicilio" << endl;
        return;
    }
}

void ArchivoVendedores::modifcarCategoria(){
    int d;
    cout << "Ingrese el DNI del vendedor a modificar: ";
    cin >> d;
    int posVen = buscarRegistro(d);
    if(posVen < 0){
        cout << endl << "El DNI ingresado no existe en el archivo." << endl;
        return;
    }
    Vendedor obj = leerRegistro(posVen);
    int nuevaCat;
    cout << "Ingrese el ID de la nueva categoria: ";
    cin >> nuevaCat;
    ArchivoCategorias arcCat;
    int posCat = arcCat.buscarRegistroActivo(nuevaCat);
    if(posCat == -1){
        cout << endl << "Error: La categoria con ID " << nuevaCat << " no existe o esta dada de baja." << endl;
        return;
    }
    obj.setCategoria(nuevaCat);
    if(modificarRegistro(obj, posVen)){
        cout << endl << "Categoria modificada con exito!" << endl;
        return;
    } else {
        cout << endl << "Error al guardar la modificacion en el archivo." << endl;
        return;
    }
}

void ArchivoVendedores::bajaVendedor(){
    cout<<"Ingrese el DNI del vendedor: ";
    int d;
    cin>>d;
    int pos = buscarRegistro(d);
    if(pos < 0){
        cout << endl <<"El DNI ingresado no existe en el archivo"<<endl;
        return;
    }
    Vendedor obj;
    obj = leerRegistro(pos);
    if(obj.getEstado() == false){
        cout << endl <<"El vendedor ya se encuentra dado de baja"<<endl;
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

ArchivoVendedores::~ArchivoVendedores(){
}
