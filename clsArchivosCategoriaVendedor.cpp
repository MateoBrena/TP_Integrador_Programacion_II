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

int ArchivoCategorias::buscarRegistro(int d){

    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++){
        CategoriaVendedor obj = leerRegistro(i);
        if(obj.getIdCategoria() == d){
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

void ArchivoCategorias::buscarPorId(){
    int d;
    cout<<"Ingrese el ID de la Categoria: ";
    cin>>d;
    int pos = buscarRegistro(d);
    if(pos < 0){
        cout << "El ID ingresado no existe en el archivo" << endl;
        return;
    }
    CategoriaVendedor obj = leerRegistro(pos);
    obj.Mostrar();
}

void ArchivoCategorias::altaCategoria(){
    CategoriaVendedor obj;
    int d;
    cout << "Ingrese el ID de la Categoria: ";
    cin >> d;
    if(d <= 0){
        cout << "Error: No se puede ingresar un ID igual o menor a cero" << endl;
        return;
    }
    int pos = buscarRegistro(d);
    if(pos >= 0){
        cout << endl << "Error: Ya existe una Categoria con ese ID" << endl;
        return;
    }
    obj.Cargar(d);
    obj.setEstado(true);
    if(grabarRegistro(obj)==false){
        cout<<"Error al grabar el registro"<<endl;
    }
}


void ArchivoCategorias::modificarDescripcion(){
    int idCat;
    cout << "Ingrese el ID de la categoria a modificar: ";
    cin >> idCat;

    int pos = buscarRegistro(idCat);
    if(pos < 0){
        cout << "El ID ingresado no existe." << endl;
        return;
    }

    CategoriaVendedor obj = leerRegistro(pos);
    char descAux[30];
    cout << "Ingrese la nueva descripcion: ";
    cargarCadena(descAux, 30);
    obj.setDescripcion(descAux);

    if(modificarRegistro(obj, pos)){
        cout << "Descripcion modificada correctamente!" << endl;
    }else{
        cout << "Error al modificar la descripcion." << endl;
    }
}

void ArchivoCategorias::modificarComision(){
    int idCat;
    cout << "Ingrese el ID de la categoria a modificar: ";
    cin >> idCat;

    int pos = buscarRegistro(idCat);
    if(pos < 0){
        cout << "El ID ingresado no existe." << endl;
        return;
    }

    CategoriaVendedor obj = leerRegistro(pos);
    int pC;
    cout << "Ingrese el nuevo porcentaje de comision (numero entero. Ej: 5): ";
    cin >> pC;
    obj.setComision((float)pC / 100);

    if(modificarRegistro(obj, pos)){
        cout << "Comision modificada correctamente!" << endl;
    }else{
        cout << "Error al modificar la comision." << endl;
    }
}

void ArchivoCategorias::bajaCategoria(){
    int idCat;
    cout << "Ingrese el ID de la categoria a dar de baja: ";
    cin >> idCat;

    int pos = buscarRegistro(idCat);
    if(pos < 0){
        cout << "El ID ingresado no existe." << endl;
        return;
    }

    CategoriaVendedor obj = leerRegistro(pos);
    if(!obj.getEstado()){
        cout << "La categoria ya se encuentra dada de baja." << endl;
        return;
    }

    obj.setEstado(false); // Baja lógica
    if(modificarRegistro(obj, pos)){
        cout << "Baja realizada con exito." << endl;
    }else{
        cout << "Error al procesar la baja." << endl;
    }


}
