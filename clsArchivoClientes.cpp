#include <iostream>
#include <cstring>
#include "clsArchivoClientes.h"
#include "clsArchivosVendedores.h"
#include "cargarCadena.h"
using namespace std;

ArchivoClientes::ArchivoClientes(const char *n){
    strcpy(nombre, n);
}

Cliente ArchivoClientes::leerRegistro(int pos){

    FILE *p = fopen(nombre,"rb");
    Cliente obj;
    if(p == nullptr){
        obj.setNroCliente(-2);
        return obj;
    }
    obj.setNroCliente(-1);
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
        if(obj.getNroCliente() == d && obj.getEstado()){
            return i;
        }
    }
    return -1;
}

int ArchivoClientes::buscarRegistroxDNI(const char *d){
    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++){
        Cliente obj = leerRegistro(i);
        if(strcmp(obj.getDni(),d) == 0){
            return i;
        }
    }
    return -1;
}

int ArchivoClientes::buscarRegistroxCUIT(const char *c){
    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++){
        Cliente obj = leerRegistro(i);
        if(strcmp(obj.getCuit(),c) == 0){
            return i;
        }
    }
    return -1;
}

int ArchivoClientes::buscarRegistroxMail(const char *m){
    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++){
        Cliente obj = leerRegistro(i);
        if(strcmp(obj.getMail(),m) == 0){
            return i;
        }
    }
    return -1;
}

int ArchivoClientes::buscarRegistroxTelefono(const char *t){
    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++){
        Cliente obj = leerRegistro(i);
        if(strcmp(obj.getTelefono(),t) == 0){
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

void ArchivoClientes::altaCliente(){
    Cliente obj;
    char d[9];
    cout << "Ingrese el DNI del cliente: ";
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
    ArchivoVendedores arcVen;
    int pos2 = arcVen.buscarRegistroxDNI(d);
    if(pos >= 0 || pos2 >= 0){
        cout << endl << "Error: Ya existe una persona con ese DNI" << endl;
        return;
    }
    cout << "Ingrese el numero de CUIT (Formato: XX-XXXXXXXX-X): ";
    char c[15];
    cargarCadena(c,15);
    if(!obj.validarCuit(c,d)){
        cout << "Error: Verifique el formato y contenido del CUIT ingresado" << endl;
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
    int cant = contarRegistros();
    if(cant <0) cant = 0;
    int nro = cant + 1;
    obj.Cargar(d, nro, c, fN);
    if(grabarRegistro(obj)){
        cout << endl << "Registro grabado exitosamente!" << endl;
        return;
    }else{
        cout << endl <<"Error al grabar el registro"<<endl;
        return;
    }
}

void ArchivoClientes::listadoFiltrado(int *l, const int TAM){
    Cliente veh;
    for(int i=0; i<TAM; i++){
        veh = leerRegistro(l[i]);
        veh.Mostrar();
    }
}

void ArchivoClientes::buscarPorId(){
    int d = cargarEntero("Ingrese el ID del cliente: ");
    int pos = buscarRegistro(d);
    if(pos < 0){
        cout << endl << "No existe ningun cliente con el ID ingresado" << endl;
        return;
    }
    Cliente c;
    c = leerRegistro(pos);
    c.Mostrar();
}

void ArchivoClientes::buscarPorDni(){
    char d[9];
    cout<<"Ingrese el DNI del cliente: ";
    cargarCadena(d,9);
    if(strlen(d) < 8){
        cout << endl << "Error: El DNI debe contener 8 caracteres. Si contiene 7, coloque un 0 adelante y luego el DNI" << endl;
        return;
    }
    Cliente c;
    if(!c.validarDni(d)){
        cout << endl << "Error: DNI ingresado en formato invalido" << endl;
        return;
    }
    int pos = buscarRegistroxDNI(d);
    if(pos < 0){
        cout << endl << "No existe ningun cliente con el DNI ingresado" << endl;
        return;
    }
    c = leerRegistro(pos);
    c.Mostrar();
}

void  ArchivoClientes::buscarPorNombre(){
    cout << "Ingrese el nombre: ";
    char nombre[20];
    cargarCadena(nombre, 20);
    int cant = contarRegistros();
    Cliente c;
    int coinciden = 0;
    for(int i=0; i<cant; i++){
        c = leerRegistro(i);
        if(strcmp(c.getNombre(),nombre) == 0 && c.getEstado()){
            coinciden++;
        }
    }
    if(coinciden == 0){
        cout << endl << "No existe ningun cliente con el nombre " << nombre << endl;
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
        c = leerRegistro(i);
        if(strcmp(c.getNombre(),nombre) == 0 && c.getEstado()){
            posCoinciden[posAsignadas] = i;
            posAsignadas++;
        }
    }
    cout << "Cantidad de clientes con el nombre "<< nombre <<": " << TAM << endl;
    listadoFiltrado(posCoinciden, TAM);
    delete[] posCoinciden;
}

void  ArchivoClientes::buscarPorApellido(){
    cout << "Ingrese el apellido: ";
    char apellido[20];
    cargarCadena(apellido, 20);
    int cant = contarRegistros();
    Cliente c;
    int coinciden = 0;
    for(int i=0; i<cant; i++){
        c = leerRegistro(i);
        if(strcmp(c.getApellido(),apellido) == 0 && c.getEstado()){
            coinciden++;
        }
    }
    if(coinciden == 0){
        cout << endl << "No existe ningun cliente con el apellido " << apellido << endl;
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
        c = leerRegistro(i);
        if(strcmp(c.getApellido(),apellido) == 0 && c.getEstado()){
            posCoinciden[posAsignadas] = i;
            posAsignadas++;
        }
    }
    cout << "Cantidad de clientes con el apellido "<< apellido <<": " << TAM << endl;
    listadoFiltrado(posCoinciden, TAM);
    delete[] posCoinciden;
}

void  ArchivoClientes::buscarPorMail(){
    cout << "Ingrese el mail: ";
    char mail[20];
    cargarCadena(mail, 20);
    int pos = buscarRegistroxMail(mail);
    if(pos < 0){
        cout << endl << "No existe un cliente con el mail ingresado" << endl;
        return;
    }
    Cliente c;
    c = leerRegistro(pos);
    c.Mostrar();
}

void  ArchivoClientes::buscarPorFechaNac(){
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
    Cliente c;
    for(int i=0; i<cant; i++){
        c = leerRegistro(i);
        if(c.getFechaNacimiento() >= desde && c.getFechaNacimiento() <= hasta && c.getEstado()){
            coinciden++;
        }
    }
    if(coinciden == 0){
        cout << endl << "No existe ningun cliente nacido entre el " << desde.mostrarFechaFormato() << " y el " << hasta.mostrarFechaFormato() << endl;
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
        c = leerRegistro(i);
        if(c.getFechaNacimiento() >= desde && c.getFechaNacimiento() <= hasta && c.getEstado()){
            posCoinciden[posAsignadas] = i;
            posAsignadas++;
        }
    }
    cout << endl << "Cantidad de clientes nacidos entre el " << desde.mostrarFechaFormato() << " y el " << hasta.mostrarFechaFormato() << ": "<< TAM <<endl;
    listadoFiltrado(posCoinciden, TAM);
    delete[] posCoinciden;
}

void  ArchivoClientes::buscarPorCuit(){
    cout << "Ingrese el numero de CUIT (Formato: XX-XXXXXXXX-X): ";
    char cu[15];
    cargarCadena(cu,15);
    Cliente c;
    if(!c.validarCuitFormato(cu)){
        cout << endl << "Error: CUIT ingresado en formato invalido" << endl;
        return;
    }
    int pos = buscarRegistroxCUIT(cu);
    if(pos < 0){
        cout << endl << "No existe ningun cliente con el CUIT ingresado" << endl;
        return;
    }
    c = leerRegistro(pos);
    c.Mostrar();
}

void  ArchivoClientes::buscarPorTelefono(){
    cout << "Ingrese el telefono: ";
    char t[12];
    cargarCadena(t, 12);
    int pos = buscarRegistroxTelefono(t);
    if(pos < 0){
        cout << endl << "No existe ningun cliente con el numero de telefono ingresado" << endl;
        return;
    }
    Cliente c;
    c = leerRegistro(pos);
    c.Mostrar();
}

void ArchivoClientes::modificarNombre(){
    int d = cargarEntero("Ingrese el ID del cliente a modificar: ");
    int pos = buscarRegistro(d);
    if(pos < 0){
        cout << endl << "Error: No existe un cliente activo con el ID ingresado" << endl;
        return;
    }
    Cliente obj;
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

void ArchivoClientes::modificarApellido(){
    int d = cargarEntero("Ingrese el ID del cliente a modificar: ");
    int pos = buscarRegistro(d);
    if(pos < 0){
        cout << endl << "Error: No existe un cliente activo con el ID ingresado" << endl;
        return;
    }
    Cliente obj;
    obj = leerRegistro(pos);
    char apAux[20];
    cout << "Ingrese el nuevo apellido: ";
    cargarCadena(apAux, 20);
    obj.setApellido(apAux);
    if(modificarRegistro(obj, pos)){
        cout << endl << "Apellido modificado!" << endl;
        return;
    }else{
        cout << endl << "Error al modificar el apellido" << endl;
        return;
    }
}

void ArchivoClientes::modificarFechaNacimiento(){
    int d = cargarEntero("Ingrese el ID del cliente a modificar: ");
    int pos = buscarRegistro(d);
    if(pos < 0){
        cout << endl << "Error: No existe un cliente activo con el ID ingresado" << endl;
        return;
    }
    Cliente obj;
    obj = leerRegistro(pos);
    Fecha faux;
    cout << "Ingrese la nueva fecha de nacimiento: " << endl;
    faux.cargarFecha();
    Fecha hoy;
    hoy.setHoy();
    if(faux > hoy){
        cout << endl << "Error: No puede ingresar una fecha futura a la de hoy" << endl;
        return;
    }
    obj.setFechaNacimiento(faux);
    if(modificarRegistro(obj, pos)){
        cout << endl << "Fecha de nacimiento modificada!" << endl;
        return;
    }else{
        cout << endl << "Error al modificar la fecha de nacimiento" << endl;
        return;
    }
}

void ArchivoClientes::modificarMail(){
    int d = cargarEntero("Ingrese el ID del cliente a modificar: ");
    int pos = buscarRegistro(d);
    if(pos < 0){
        cout << endl << "Error: No existe un cliente activo con el ID ingresado" << endl;
        return;
    }
    char mAux[30];
    cout << "Ingrese el nuevo mail: ";
    cargarCadena(mAux, 30);
    int pos2 = buscarRegistroxMail(mAux);
    if(pos2 >= 0){
        cout << endl << "Error: Ya existe un cliente con ese mail" << endl;
        return;
    }
    Cliente obj;
    obj = leerRegistro(pos);
    obj.setMail(mAux);
    if(modificarRegistro(obj, pos)){
        cout << endl << "Mail modificado!" << endl;
        return;
    }else{
        cout << endl << "Error al modificar el mail" << endl;
        return;
    }
}

void ArchivoClientes::modificarDomicilio(){
    int d = cargarEntero("Ingrese el ID del cliente a modificar: ");
    int pos = buscarRegistro(d);
    if(pos < 0){
        cout << endl << "Error: No existe un cliente activo con el ID ingresado" << endl;
        return;
    }
    Cliente obj;
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

void ArchivoClientes::modificarCuit(){
    int d = cargarEntero("Ingrese el ID del cliente a modificar: ");
    int pos = buscarRegistro(d);
    if(pos < 0){
        cout << endl << "Error: No existe un cliente activo con el ID ingresado" << endl;
        return;
    }
    Cliente obj;
    obj = leerRegistro(pos);
    char cAux[15];
    cout << "Ingrese el numero de CUIT (Formato: XX-XXXXXXXX-X): ";
    cargarCadena(cAux,15);
    if(!obj.validarCuit(cAux, obj.getDni())){
        cout << endl << "Error: Verfique el formato o el contenido del CUIT ingresado" << endl;
        return;
    }
    obj.setCuit(cAux);
    if(modificarRegistro(obj, pos)){
        cout << endl << "CUIT modificado!" << endl;
        return;
    }else{
        cout << endl << "Error al modificar el CUIT" << endl;
        return;
    }
}

void ArchivoClientes::modificarTelefono(){
    int d = cargarEntero("Ingrese el ID del cliente a modificar: ");
    int pos = buscarRegistro(d);
    if(pos < 0){
        cout << endl << "Error: No existe un cliente activo con el ID ingresado" << endl;
        return;
    }
    char tAux[12];
    cout << "Ingrese el nuevo telefono: ";
    cargarCadena(tAux, 12);
    int pos2 = buscarRegistroxTelefono(tAux);
    if(pos2 >= 0){
        cout << endl << "Error: Ya existe un cliente con ese numero de telefono" << endl;
        return;
    }
    Cliente obj;
    obj = leerRegistro(pos);
    obj.setTelefono(tAux);
    if(modificarRegistro(obj, pos)){
        cout << endl << "Telefono modificado!" << endl;
        return;
    }else{
        cout << endl << "Error al modificar el telefono" << endl;
        return;
    }
}

void ArchivoClientes::bajaCliente(){
    int d = cargarEntero("Ingrese el ID del cliente a dar de baja: ");
    int pos = buscarRegistro(d);
    if(pos < 0){
        cout << endl << "Error: No existe un cliente activo con el ID ingresado" << endl;
        return;
    }
    Cliente obj;
    obj = leerRegistro(pos);
    obj.setEstado(false);
    if(modificarRegistro(obj, pos)){
        cout << endl <<"Baja realizada correctamente"<<endl;
        return;
    }else{
        cout << endl <<"Error al realizar la baja"<<endl;
        return;
    }
}

ArchivoClientes::~ArchivoClientes(){
}
