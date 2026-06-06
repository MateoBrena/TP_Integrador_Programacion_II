#include <iostream>
#include <cstring>
#include "clsArchivosCategoriaVendedor.h"
#include "cargarCadena.h"
using namespace std;

ArchivoCategorias::ArchivoCategorias(const char *n){
    strcpy(nombre, n);
}

CategoriaVendedor ArchivoCategorias::leerRegistro(int pos){
    FILE *p = fopen(nombre,"rb");
    CategoriaVendedor obj;
    if(p == nullptr){
        obj.setIdCategoria(-2);
        return obj;
    }
    obj.setIdCategoria(-1);
    fseek(p,  sizeof obj * pos, 0);
    fread(&obj, sizeof obj, 1, p);
    fclose(p);

    return obj;

}

bool ArchivoCategorias::grabarRegistro(CategoriaVendedor obj){
    FILE *p = fopen(nombre, "ab");
    if(p == nullptr){
        return false;
    }
    bool escribio = fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
    return escribio;
}

bool ArchivoCategorias::modificarRegistro(CategoriaVendedor obj, int pos){
    FILE *p = fopen(nombre, "rb+");
    if(p == nullptr){
        return false;
    }
    fseek(p, sizeof obj * pos, 0);
    bool escribio = fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
    return escribio;
}

int ArchivoCategorias::contarRegistros(){
    FILE *p = fopen(nombre, "rb");
    if(p == nullptr){
        return -1;
    }
    fseek(p,0,2);
    int cant = ftell(p)/sizeof(CategoriaVendedor);
    fclose(p);
    return cant;
}

int ArchivoCategorias::contarRegistrosActivos(int ca){
    int cantActivos = 0;
    for(int i=0; i<ca; i++){
        CategoriaVendedor c = leerRegistro(i);
        if(c.getEstado()){
            cantActivos++;
        }
    }

    return cantActivos;
}


int ArchivoCategorias::buscarRegistro(int d){
    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++){
        CategoriaVendedor obj = leerRegistro(i);
        if(obj.getIdCategoria() == d && obj.getEstado()){
            return i;
        }
    }

    return -1;
}

int ArchivoCategorias::buscarRegistroxNombre(const char *n){

    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++){
        CategoriaVendedor obj = leerRegistro(i);
        if(strcmp(obj.getDescripcion(), n) == 0 && obj.getEstado()){
            return i;
        }
    }

    return -1;
}

int ArchivoCategorias::buscarRegistroxComision(float c){

    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++){
        CategoriaVendedor obj = leerRegistro(i);
        if( obj.getPorcentajeComision() == c && obj.getEstado()){
            return i;
        }
    }

    return -1;
}

void ArchivoCategorias::listarRegistros(){
    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++){
        CategoriaVendedor obj = leerRegistro(i);
        if(obj.getEstado()){
            obj.Mostrar();
            cout << endl;
        }
    }
}

void ArchivoCategorias::altaCategoria(){
    cout << "Ingrese el nombre de la categoria: ";
    char nombre[20];
    cargarCadena(nombre, 20);
    int pos = buscarRegistroxNombre(nombre);
    if(pos >= 0){
        cout << endl << "Error: Ya hay una categoria llamada " << nombre << endl;
        return;
    }
    float comision = cargarFlotante("Ingrese el porcentaje de comision de la categoria (numero flotante max 2 decimales o numero entero): ");
    int pos2 = buscarRegistroxComision(comision);
    if(pos2 >= 0){
        cout << endl << "Error: Ya hay una categoria con " << comision << "% de comision" <<endl;
        return;
    }
    CategoriaVendedor obj;
    int cant = contarRegistros();
    if(cant <0) cant = 0;
    int nro = cant + 1;
    obj.Cargar(nro, nombre, comision);
    if(grabarRegistro(obj)){
        cout<< endl <<"Registro grabado exitosamente!"<<endl;
        return;
    }else{
        cout<< endl <<"Error al grabar el registro"<<endl;
        return;
    }
}

void ArchivoCategorias::listadoFiltrado(int *l, const int TAM){
    CategoriaVendedor c;
    for(int i=0; i<TAM; i++){
        c = leerRegistro(l[i]);
        c.Mostrar();
    }
}

void ArchivoCategorias::buscarPorId(){
    int d = cargarEntero("Ingrese el ID de la categoria: ");
    int pos = buscarRegistro(d);
    if(pos < 0){
        cout << endl << "El ID ingresado no existe en el archivo" << endl;
        return;
    }
    CategoriaVendedor obj = leerRegistro(pos);
    obj.Mostrar();
}

void ArchivoCategorias::buscarPorNombre(){
    cout << "Ingrese el nombre de la categoria: ";
    char nombre[20];
    cargarCadena(nombre, 20);
    int pos = buscarRegistroxNombre(nombre);
    if(pos < 0){
        cout << endl << "No hay ninguna categoria llamada " << nombre << endl;
        return;
    }
    CategoriaVendedor obj = leerRegistro(pos);
    obj.Mostrar();
}

void ArchivoCategorias::buscarPorComision(){
    float comision=cargarFlotante("Ingrese el porcentaje de comision de la categoria (numero flotante max 2 decimales o numero entero): ");
    int pos = buscarRegistroxComision(comision);
    if(pos < 0){
        cout << endl << "No hay ninguna categoria con " << comision << "% de comision" <<  endl;
        return;
    }
    CategoriaVendedor obj = leerRegistro(pos);
    obj.Mostrar();
}

void ArchivoCategorias::modificarDescripcion(){
    int idCat = cargarEntero("Ingrese el ID de la categoria a modificar: ");
    int pos = buscarRegistro(idCat);
    if(pos < 0){
        cout << endl << "No existe una categoria con el ID ingresado" << endl;
        return;
    }
    char descAux[30];
    cout << "Ingrese la nueva descripcion: ";
    cargarCadena(descAux, 30);
    int pos2 = buscarRegistroxNombre(descAux);
    if(pos2 >= 0){
        cout << endl << "Error: Ya hay una categoria llamada " << descAux << endl;
        return;
    }
    CategoriaVendedor obj = leerRegistro(pos);
    obj.setDescripcion(descAux);
    if(modificarRegistro(obj, pos)){
        cout << endl << "Descripcion modificada correctamente!" << endl;
        return;
    }else{
        cout << "Error al modificar la descripcion." << endl;
        return;
    }
}

void ArchivoCategorias::modificarComision(){
    int idCat = cargarEntero("Ingrese el ID de la categoria a modificar: ");
    int pos = buscarRegistro(idCat);
    if(pos < 0){
        cout << endl << "No existe una categoria con el ID ingresado" << endl;
        return;
    }
    float pC = cargarFlotante("Ingrese el nuevo porcentaje de comision (numero flotante max 2 decimales o numero entero): ");
    int pos2 = buscarRegistroxComision(pC);
    if(pos2 >= 0){
        cout << endl << "Error: Ya hay una categoria con " << pC << "% de comision" <<  endl;
        return;
    }
    CategoriaVendedor obj = leerRegistro(pos);
    obj.setComision(pC);
    if(modificarRegistro(obj, pos)){
        cout << endl << "Comision modificada correctamente!" << endl;
        return;
    }else{
        cout << endl << "Error al modificar la comision." << endl;
        return;
    }
}

void ArchivoCategorias::bajaCategoria(){
    int idCat = cargarEntero("Ingrese el ID de la categoria a dar de baja: ");
    int pos = buscarRegistro(idCat);
    if(pos < 0){
        cout << endl << "No existe una categoria con el ID ingresado" << endl;
        return;
    }
    CategoriaVendedor obj = leerRegistro(pos);
    obj.setEstado(false);
    if(modificarRegistro(obj, pos)){
        cout << endl << "Baja realizada con exito." << endl;
        return;
    }else{
        cout << endl << "Error al procesar la baja." << endl;
        return;
    }
}


ArchivoCategorias::~ArchivoCategorias(){
}
