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
        if(obj.getId() == d && obj.getEstado()){
            return i;
        }
    }

    return -1;
}

int ArchivoMarcas::buscarRegistroxNombre(const char *n){

    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++){
        Marca obj = leerRegistro(i);
        if(strcmp(obj.getNombre(), n) == 0 && obj.getEstado()){
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

void ArchivoMarcas::altaMarca(){
    Marca obj;
    cout << "Ingrese el nombre de la marca: ";
    char n[20];
    cargarCadena(n,20);
    int pos = buscarRegistroxNombre(n);
    if(pos >= 0){
        cout << endl << "Error: Ya existe una marca con ese nombre" << endl;
        return;
    }
    int cant = contarRegistros();
    if(cant <0) cant = 0;
    int nro = cant + 1;
    obj.Cargar(nro, n);
    if(grabarRegistro(obj)){
        cout<< endl <<"Registro grabado exitosamente!"<<endl;
        return;
    }else{
        cout<< endl <<"Error al grabar el registro"<<endl;
        return;
    }
}

void ArchivoMarcas::listadoFiltrado(int *l, const int TAM){
    Marca m;
    for(int i=0; i<TAM; i++){
        m = leerRegistro(l[i]);
        m.Mostrar();
    }
}

void ArchivoMarcas::buscarPorId(){
    int d = cargarEntero("Ingrese el ID de la marca: ");
    int pos = buscarRegistro(d);
    if(pos < 0){
        cout << endl << "El ID ingresado no existe en el archivo" << endl;
        return;
    }
    Marca obj = leerRegistro(pos);
    obj.Mostrar();
}

void ArchivoMarcas::buscarPorNombre(){
    cout << "Ingrese el nombre: ";
    char nombre[20];
    cargarCadena(nombre, 20);
    int pos = buscarRegistroxNombre(nombre);
    if(pos < 0){
        cout << endl << "No hay ninguna marca llamada " << nombre << endl;
        return;
    }
    Marca obj = leerRegistro(pos);
    obj.Mostrar();
}

void ArchivoMarcas::buscarPorPais(){
    cout << "Ingrese el nombre del pais: ";
    char pais[20];
    cargarCadena(pais, 20);
    int cant = contarRegistros();
    Marca m;
    int coinciden = 0;
    for(int i=0; i<cant; i++){
        m = leerRegistro(i);
        if(strcmp(m.getPais(),pais) == 0 && m.getEstado()){
            coinciden++;
        }
    }
    if(coinciden == 0){
        cout << endl << "No existe ninguna marca de " << pais << endl;
        return;
    }
    const int TAM = coinciden;
    int *posCoinciden;
    posCoinciden = new int[TAM]{};
    if(posCoinciden==NULL){
        cout << endl << "ERROR DE ASIGNACION DE MEMORIA";
        return;
    }
    int posAsignadas = 0;
    for(int i=0; i<cant; i++){
        m = leerRegistro(i);
        if(strcmp(m.getPais(),pais) == 0 && m.getEstado()){
            posCoinciden[posAsignadas] = i;
            posAsignadas++;
        }
    }
    cout << "Cantidad de marcas de "<< pais <<": " << TAM << endl;
    listadoFiltrado(posCoinciden, TAM);
    delete[] posCoinciden;
}

void ArchivoMarcas::modificarNombre(){
    int d = cargarEntero("Ingrese el ID de la marca: ");
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
    int pos2 = buscarRegistroxNombre(nomAux);
    if(pos2 >= 0){
        cout << endl << "Error: Ya existe una marca con ese nombre" << endl;
        return;
    }
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
    int d = cargarEntero("Ingrese el ID de la marca: ");
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
    int d = cargarEntero("Ingrese el ID de la marca a dar de baja: ");
    int pos = buscarRegistro(d);
    if(pos < 0){
        cout << endl <<"El ID ingresado no existe en el archivo"<<endl;
        return;
    }
    Marca obj;
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
