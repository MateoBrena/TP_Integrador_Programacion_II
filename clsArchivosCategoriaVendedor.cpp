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
        if(obj.getIdCategoria() == d){
            return i;
        }
    }

    return -1;
}

int ArchivoCategorias::buscarRegistroActivo(int d){
    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++){
        CategoriaVendedor obj = leerRegistro(i);
        if(obj.getIdCategoria() == d && obj.getEstado()){
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
    cout<<"Ingrese el ID de la categoria: ";
    cin>>d;
    int pos = buscarRegistro(d);
    if(pos < 0){
        cout << endl << "El ID ingresado no existe en el archivo" << endl;
        return;
    }
    CategoriaVendedor obj = leerRegistro(pos);
    if(obj.getEstado()){
        obj.Mostrar();
    }else{
        cout << endl << "Error: la categoria con ID " << d << " se encuentra dada de baja.";
    }
}

void ArchivoCategorias::altaCategoria(){
    CategoriaVendedor obj;
    int cant = contarRegistros();
    if(cant <0) cant = 0;
    int nro = cant + 1;
    obj.Cargar(nro);
    if(grabarRegistro(obj)){
        cout<< endl <<"Registro grabado exitosamente!"<<endl;
    }else{
        cout<< endl <<"Error al grabar el registro"<<endl;
    }
}


void ArchivoCategorias::modificarDescripcion(){
    int idCat;
    cout << "Ingrese el ID de la categoria a modificar: ";
    cin >> idCat;
    int pos = buscarRegistro(idCat);
    if(pos < 0){
        cout << endl << "El ID ingresado no existe." << endl;
        return;
    }
    CategoriaVendedor obj = leerRegistro(pos);
    char descAux[30];
    cout << "Ingrese la nueva descripcion: ";
    cargarCadena(descAux, 30);
    obj.setDescripcion(descAux);
    if(modificarRegistro(obj, pos)){
        cout << endl << "Descripcion modificada correctamente!" << endl;
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
        cout << endl << "El ID ingresado no existe." << endl;
        return;
    }
    CategoriaVendedor obj = leerRegistro(pos);
    float pC;
    cout << "Ingrese el nuevo porcentaje de comision (numero flotante max 2 decimales o numero entero): ";
    cin >> pC;
    obj.setComision(pC);
    if(modificarRegistro(obj, pos)){
        cout << endl << "Comision modificada correctamente!" << endl;
    }else{
        cout << endl << "Error al modificar la comision." << endl;
    }
}

void ArchivoCategorias::bajaCategoria(){
    int idCat;
    cout << "Ingrese el ID de la categoria a dar de baja: ";
    cin >> idCat;
    int pos = buscarRegistro(idCat);
    if(pos < 0){
        cout << endl << "El ID ingresado no existe." << endl;
        return;
    }
    CategoriaVendedor obj = leerRegistro(pos);
    if(!obj.getEstado()){
        cout << endl << "La categoria ya se encuentra dada de baja." << endl;
        return;
    }
    obj.setEstado(false);
    if(modificarRegistro(obj, pos)){
        cout << endl << "Baja realizada con exito." << endl;
    }else{
        cout << endl << "Error al procesar la baja." << endl;
    }
}


ArchivoCategorias::~ArchivoCategorias(){
}
