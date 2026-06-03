#include <iostream>
#include <cstring>
#include "clsArchivoMarcas.h"
#include "cargarCadena.h"
using namespace std;

ArchivoMarcas::ArchivoMarcas(const char *n){
    strcpy(nombre, n);
}

Marca ArchivoMarcas::leerRegistro(int pos){

    FILE *p = fopen(nombre,"rb");
    Marca obj;
    if(p == nullptr){
        obj.setId(-2);
        return obj;
    }
    obj.setId(-1);
    fseek(p,  sizeof obj * pos, 0);
    fread(&obj, sizeof obj, 1, p);
    fclose(p);

    return obj;

}

bool ArchivoMarcas::grabarRegistro(Marca obj){

    FILE *p = fopen(nombre, "ab");
    if(p == nullptr){
        return false;
    }
    bool escribio = fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
    return escribio;
}

bool ArchivoMarcas::modificarRegistro(Marca obj, int pos){

    FILE *p = fopen(nombre, "rb+");
    if(p == nullptr){
        return false;
    }
    fseek(p, sizeof obj * pos, 0);
    bool escribio = fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
    return escribio;
}

int ArchivoMarcas::contarRegistros(){

    FILE *p = fopen(nombre, "rb");
    if(p == nullptr){
        return -1;
    }
    fseek(p,0,2);
    int cant = ftell(p)/sizeof(Marca);
    fclose(p);
    return cant;
}

int ArchivoMarcas::contarRegistrosActivos(int ca){

    int cantActivos = 0;
    for(int i=0; i<ca; i++){
        Marca m = leerRegistro(i);
        if(m.getEstado()){
            cantActivos++;
        }
    }

    return cantActivos;
}

int ArchivoMarcas::buscarRegistro(int d){

    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++){
        Marca obj = leerRegistro(i);
        if(obj.getId() == d){
            return i;
        }
    }

    return -1;
}

void ArchivoMarcas::listarRegistros(){

    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++){
        Marca obj = leerRegistro(i);
        if(obj.getEstado()){
            obj.Mostrar();
            cout << endl;
        }
    }
}

void ArchivoMarcas::buscarPorId(){
    int d;
    cout<<"Ingrese el ID de la marca: ";
    cin>>d;
    int pos = buscarRegistro(d);
    if(pos < 0){
        cout << endl << "El ID ingresado no existe en el archivo" << endl;
        return;
    }
    Marca obj = leerRegistro(pos);
    if(obj.getEstado()){
        obj.Mostrar();
    }else{
        cout << endl << "Error: la marca con ID " << d << " se encuentra dada de baja.";
        return;
    }

}

void ArchivoMarcas::altaMarca(){
    Marca obj;
    int cant = contarRegistros();
    if(cant <0) cant = 0;
    int nro = cant + 1;
    obj.Cargar(nro);
    if(grabarRegistro(obj)){
        cout<< endl <<"Registro grabado exitosamente!"<<endl;
        return;
    }else{
        cout<< endl <<"Error al grabar el registro"<<endl;
        return;
    }
}

void ArchivoMarcas::modificarNombre(){
    int d;
    cout<<"Ingrese el ID de la marca: ";
    cin>>d;
    int pos = buscarRegistro(d);
    if(pos < 0){
        cout << endl << "El ID ingresado no existe en el archivo" << endl;
        return;
    }
    Marca obj;
    obj = leerRegistro(pos);
    char nomAux[20];
    cout << "Ingrese el nuevo nombre: ";
    cargarCadena(nomAux, 20);
    obj.setNombre(nomAux);
    if(modificarRegistro(obj, pos)){
        cout << endl << "Nombre modificado!" << endl;
        return;
    }else{
        cout << endl << "Error al modificar el nombre" << endl;
        return;
    }
}

void ArchivoMarcas::modificarPais(){
    int d;
    cout<<"Ingrese el ID de la marca: ";
    cin>>d;
    int pos = buscarRegistro(d);
    if(pos < 0){
        cout << endl << "El ID ingresado no existe en el archivo" << endl;
        return;
    }
    Marca obj;
    obj = leerRegistro(pos);
    char pAux[20];
    cout << "Ingrese el nuevo pais: ";
    cargarCadena(pAux, 20);
    obj.setPais(pAux);
    if(modificarRegistro(obj, pos)){
        cout << endl << "Pais modificado!" << endl;
        return;
    }else{
        cout << endl << "Error al modificar el apellido" << endl;
        return;
    }
}

void ArchivoMarcas::bajaMarca(){
    cout<<"Ingrese el ID de la marca: ";
    int d;
    cin>>d;
    int pos = buscarRegistro(d);
    if(pos < 0){
        cout << endl <<"El ID ingresado no existe en el archivo"<<endl;
        return;
    }
    Marca obj;
    obj = leerRegistro(pos);
    if(obj.getEstado() == false){
        cout << endl <<"La marca ya se encuentra dada de baja"<<endl;
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

ArchivoMarcas::~ArchivoMarcas(){
}
