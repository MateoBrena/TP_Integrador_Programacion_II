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
        obj.setNroVendedor(-2);
        return obj;
    }
    obj.setNroVendedor(-1);
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

int ArchivoVendedores::contarRegistrosActivos(int ca){
    int cantActivos = 0;
    for(int i=0; i<ca; i++){
        Vendedor v = leerRegistro(i);
        if(v.getEstado()){
            cantActivos++;
        }
    }
    return cantActivos;
}

int ArchivoVendedores::buscarRegistro(int d){

    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++){
        Vendedor obj = leerRegistro(i);
        if(obj.getNroVendedor() == d && obj.getEstado()){
            return i;
        }
    }

    return -1;
}

int ArchivoVendedores::buscarRegistroxDNI(const char *d){

    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++){
        Vendedor obj = leerRegistro(i);
        if(strcmp(obj.getDni(), d) == 0){
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

void ArchivoVendedores::altaVendedor(){
    Vendedor obj;
    char d[9];
    cout << "Ingrese el DNI del vendedor: ";
    cargarCadena(d,9);
    if(strlen(d) < 8){
        cout << endl << "Error: El DNI debe contener 8 caracteres. Si contiene 7, coloque un 0 adelante y luego el DNI" << endl;
        return;
    }
    if(!obj.validarDni(d)){
        cout << "Error: DNI ingresado en formato invalido" << endl;
        return;
    }
    int pos = buscarRegistroxDNI(d);
    ArchivoClientes arcCli;
    int pos2 = arcCli.buscarRegistroxDNI(d);
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
    int cat = cargarEntero("Ingrese el ID de categoria del vendedor: ");
    ArchivoCategorias arcCat;
    pos = arcCat.buscarRegistro(cat);
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

void ArchivoVendedores::listadoFiltrado(int *l, const int TAM){
    Vendedor ven;
    for(int i=0; i<TAM; i++){
        ven = leerRegistro(l[i]);
        ven.Mostrar();
    }
}

void ArchivoVendedores::buscarPorId(){
    int d = cargarEntero("Ingrese el ID del vendedor: ");
    int cantReg = contarRegistros();
    for(int i = 0; i < cantReg; i++){
        Vendedor obj = leerRegistro(i);
        if(obj.getNroVendedor() == d && obj.getEstado()){
            obj.Mostrar();
            return;
        }
    }
    cout << endl << "No existe un vendedor con el ID: " << d << endl;
}

void ArchivoVendedores::buscarPorDni(){
    char d[9];
    cout<<"Ingrese el DNI del vendedor: ";
    cargarCadena(d,9);
    if(strlen(d) < 8){
        cout << endl << "Error: El DNI debe contener 8 caracteres. Si contiene 7, coloque un 0 adelante y luego el DNI" << endl;
        return;
    }
    Vendedor obj;
    if(!obj.validarDni(d)){
        cout << endl << "Error: DNI ingresado en formato invalido" << endl;
        return;
    }
    int cantReg = contarRegistros();
    for(int i = 0; i < cantReg; i++){
        obj = leerRegistro(i);
        if(strcmp(obj.getDni(),d) == 0 && obj.getEstado()){
            obj.Mostrar();
            return;
        }
    }
    cout << endl << "No existe un vendedor con el DNI: " << d << endl;
}

void ArchivoVendedores::buscarPorNombre(){
    cout << "Ingrese el nombre: ";
    char nombre[20];
    cargarCadena(nombre, 20);
    int cant = contarRegistros();
    Vendedor v;
    int coinciden = 0;
    for(int i=0; i<cant; i++){
        v = leerRegistro(i);
        if(strcmp(v.getNombre(),nombre) == 0 && v.getEstado()){
            coinciden++;
        }
    }
    if(coinciden == 0){
        cout << endl << "No existe ningun vendedor con el nombre " << nombre << endl;
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
        v = leerRegistro(i);
        if(strcmp(v.getNombre(),nombre) == 0 && v.getEstado()){
            posCoinciden[posAsignadas] = i;
            posAsignadas++;
        }
    }
    cout << "Cantidad de vendedores con el nombre "<< nombre <<": " << TAM << endl;
    listadoFiltrado(posCoinciden, TAM);
    delete[] posCoinciden;
}

void ArchivoVendedores::buscarPorApellido(){
    cout << "Ingrese el apellido: ";
    char apellido[20];
    cargarCadena(apellido, 20);
    int cant = contarRegistros();
    Vendedor v;
    int coinciden = 0;
    for(int i=0; i<cant; i++){
        v = leerRegistro(i);
        if(strcmp(v.getApellido(),apellido) == 0 && v.getEstado()){
            coinciden++;
        }
    }
    if(coinciden == 0){
        cout << endl << "No existe ningun vendedor con el apellido " << apellido << endl;
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
        v = leerRegistro(i);
        if(strcmp(v.getApellido(),apellido) == 0 && v.getEstado()){
            posCoinciden[posAsignadas] = i;
            posAsignadas++;
        }
    }
    cout << "Cantidad de vendedores con el apellido "<< apellido <<": " << TAM << endl;
    listadoFiltrado(posCoinciden, TAM);
    delete[] posCoinciden;
}

void ArchivoVendedores::buscarPorMail(){
    cout << "Ingrese el mail: ";
    char mail[20];
    cargarCadena(mail, 20);
    int cantReg = contarRegistros();
    for(int i = 0; i < cantReg; i++){
        Vendedor obj = leerRegistro(i);
        if(strcmp(obj.getMail(), mail) == 0 && obj.getEstado()){
            obj.Mostrar();
            return;
        }
    }
    cout << endl << "No existe un vendedor con el mail: " << mail << endl;
}

void ArchivoVendedores::buscarPorFechaNac(){
    cout << "Ingresar rango de fechas: " << endl;
    cout << endl << "Desde: " << endl;
    Fecha desde;
    desde.cargarFecha();
    Fecha hoy;
    hoy.setHoy();
    if(desde > hoy){
        cout << endl << "Error: No se puede ingresar una fecha futura a la de hoy" << endl;
        return;
    }
    cout << endl << "Hasta" << endl;
    Fecha hasta;
    hasta.cargarFecha();
    if(hasta > hoy){
        cout << endl << "Error: No se puede ingresar una fecha futura a la de hoy" << endl;
        return;
    }
    if(hasta < desde){
        cout << endl << "Error: El rango de fechas ingresado es invalido" << endl;
        return;
    }
    int cant = contarRegistros();
    int coinciden = 0;
    Vendedor v;
    for(int i=0; i<cant; i++){
        v = leerRegistro(i);
        if(v.getFechaNacimiento() >= desde && v.getFechaNacimiento() <= hasta && v.getEstado()){
            coinciden++;
        }
    }
    if(coinciden == 0){
        cout << endl << "No existe ningun vendedor nacido entre el " << desde.mostrarFechaFormato() << " y el " << hasta.mostrarFechaFormato() << endl;
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
        v = leerRegistro(i);
        if(v.getFechaNacimiento() >= desde && v.getFechaNacimiento() <= hasta && v.getEstado()){
            posCoinciden[posAsignadas] = i;
            posAsignadas++;
        }
    }
    cout << endl << "Cantidad de vendedores nacidos entre el " << desde.mostrarFechaFormato() << " y el " << hasta.mostrarFechaFormato() << ": "<< TAM <<endl;
    listadoFiltrado(posCoinciden, TAM);
    delete[] posCoinciden;
}

void ArchivoVendedores::buscarPorFechaCont(){
   cout << "Ingresar rango de fechas: " << endl;
    cout << endl << "Desde: " << endl;
    Fecha desde;
    desde.cargarFecha();
    Fecha hoy;
    hoy.setHoy();
    if(desde > hoy){
        cout << endl << "Error: No se puede ingresar una fecha futura a la de hoy" << endl;
        return;
    }
    cout << endl << "Hasta" << endl;
    Fecha hasta;
    hasta.cargarFecha();
    if(hasta > hoy){
        cout << endl << "Error: No se puede ingresar una fecha futura a la de hoy" << endl;
        return;
    }
    if(hasta < desde){
        cout << endl << "Error: El rango de fechas ingresado es invalido" << endl;
        return;
    }
    int cant = contarRegistros();
    int coinciden = 0;
    Vendedor v;
    for(int i=0; i<cant; i++){
        v = leerRegistro(i);
        if(v.getFechaContratacion() >= desde && v.getFechaContratacion() <= hasta && v.getEstado()){
            coinciden++;
        }
    }
    if(coinciden == 0){
        cout << endl << "No existe ningun vendedor contratado entre el " << desde.mostrarFechaFormato() << " y el " << hasta.mostrarFechaFormato() << endl;
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
        v = leerRegistro(i);
        if(v.getFechaContratacion() >= desde && v.getFechaContratacion() <= hasta && v.getEstado()){
            posCoinciden[posAsignadas] = i;
            posAsignadas++;
        }
    }
    cout << endl << "Cantidad de vendedores contratados entre el " << desde.mostrarFechaFormato() << " y el " << hasta.mostrarFechaFormato() << ": "<< TAM <<endl;
    listadoFiltrado(posCoinciden, TAM);
    delete[] posCoinciden;
}

void ArchivoVendedores::buscarPorCat(){
    cout << "Ingrese el nombre de la categoria: ";
    char categoria[30];
    cargarCadena(categoria, 30);
    ArchivoCategorias arcCat;
    int pos = arcCat.buscarRegistroxNombre(categoria);
    if(pos < 0){
        cout << endl << "Error: El nombre de categoria ingresado no coincide con ninguna categoria en el archivo" << endl;
        return;
    }
    int idCategoria = pos + 1;
    int cant = contarRegistros();
    Vendedor ven;
    int coinciden = 0;
    for(int i=0; i<cant; i++){
        ven = leerRegistro(i);
        if(ven.getCategoria() == idCategoria && ven.getEstado()){
            coinciden++;
        }
    }
    if(coinciden == 0){
        cout << endl << "Actualmente no poseemos ningun vendedor con categoria " << categoria << endl;
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
        ven = leerRegistro(i);
        if(ven.getCategoria() == idCategoria && ven.getEstado()){
            posCoinciden[posAsignadas] = i;
            posAsignadas++;
        }
    }
    cout << "Cantidad de vendedores con la categoria "<< categoria <<": " << TAM << endl;
    listadoFiltrado(posCoinciden, TAM);
    delete[] posCoinciden;
}

void ArchivoVendedores::modificarNombre(){
    int d = cargarEntero("Ingrese el ID del vendedor a modificar: ");
    int pos = buscarRegistro(d);
    if(pos < 0){
        cout << endl << "El ID ingresado no existe en el archivo" << endl;
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
    int d = cargarEntero("Ingrese el ID del vendedor a modificar: ");
    int pos = buscarRegistro(d);
    if(pos < 0){
        cout << endl << "El ID ingresado no existe en el archivo" << endl;
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
    int d = cargarEntero("Ingrese el ID del vendedor a modificar: ");
    int pos = buscarRegistro(d);
    if(pos < 0){
        cout << endl << "El ID ingresado no existe en el archivo" << endl;
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
    int d = cargarEntero("Ingrese el ID del vendedor a modificar: ");
    int pos = buscarRegistro(d);
    if(pos < 0){
        cout << "El ID ingresado no existe en el archivo" << endl;
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
    int d = cargarEntero("Ingrese el ID del vendedor a modificar: ");
    int pos = buscarRegistro(d);
    if(pos < 0){
        cout << endl << "El ID ingresado no existe en el archivo" << endl;
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
    int d = cargarEntero("Ingrese el ID del vendedor a modificar: ");
    int pos = buscarRegistro(d);
    if(pos < 0){
        cout << endl << "El ID ingresado no existe en el archivo" << endl;
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
    int d = cargarEntero("Ingrese el ID del vendedor a modificar: ");
    int posVen = buscarRegistro(d);
    if(posVen < 0){
        cout << endl << "El ID ingresado no existe en el archivo." << endl;
        return;
    }
    Vendedor obj = leerRegistro(posVen);
    int nuevaCat;
    nuevaCat = cargarEntero("Ingrese el ID de la nueva categoria: ");
    ArchivoCategorias arcCat;
    int posCat = arcCat.buscarRegistro(nuevaCat);
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
    int d = cargarEntero("Ingrese el ID del vendedor a dar de baja: ");
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
