#include <iostream>
#include <cstring>
#include <iomanip>
#include "clsArchivoVehiculos.h"
#include "clsArchivoMarcas.h"
#include "cargarCadena.h"
using namespace std;

ArchivoVehiculos::ArchivoVehiculos(const char *n){
    strcpy(nombre, n);
}

Vehiculo ArchivoVehiculos::leerRegistro(int pos){
    FILE *p = fopen(nombre, "rb");
    Vehiculo obj;
    if(p == nullptr){
        obj.setPatente("ERROR");
        return obj;
    }
    fseek(p, sizeof obj * pos, 0);
    fread(&obj, sizeof obj, 1, p);
    fclose(p);
    return obj;
}

bool ArchivoVehiculos::grabarRegistro(Vehiculo obj){
    FILE *p = fopen(nombre, "ab");
    if(p == nullptr){
        return false;
    }
    bool escribio = fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
    return escribio;
}

bool ArchivoVehiculos::modificarRegistro(Vehiculo obj, int pos){
    FILE *p = fopen(nombre, "rb+");
    if(p == nullptr){
        return false;
    }
    fseek(p, sizeof obj * pos, 0);
    bool escribio = fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
    return escribio;
}

int ArchivoVehiculos::contarRegistros(){
    FILE *p = fopen(nombre, "rb");
    if(p == nullptr){
        return -1;
    }
    fseek(p, 0, 2);
    int cant = ftell(p) / sizeof(Vehiculo);
    fclose(p);
    return cant;
}

int ArchivoVehiculos::contarRegistrosActivos(int ca){
    int cantActivos = 0;
    for(int i=0; i<ca; i++){
        Vehiculo v = leerRegistro(i);
        if(v.getEstado()){
            cantActivos++;
        }
    }
    return cantActivos;
}

int ArchivoVehiculos::buscarRegistro(int d){
    int cantReg = contarRegistros();
    for(int i = 0; i < cantReg; i++){
        Vehiculo obj = leerRegistro(i);
        if(obj.getId() == d && obj.getEstado()){
            return i;
        }
    }
    return -1;
}

int ArchivoVehiculos::buscarRegistroInactivo(int d){
    int cantReg = contarRegistros();
    for(int i = 0; i < cantReg; i++){
        Vehiculo obj = leerRegistro(i);
        if(obj.getId() == d){
            return i;
        }
    }
    return -1;
}

int ArchivoVehiculos::buscarRegistroPorPatente(const char *p){
    int cantReg = contarRegistros();
    for(int i = 0; i < cantReg; i++){
        Vehiculo obj = leerRegistro(i);
        if(strcmp(obj.getPatente(),p) == 0 && obj.getEstado()){
            return i;
        }
    }
    return -1;
}

void ArchivoVehiculos::listarRegistros(){
    int cantReg = contarRegistros();
    if(cantReg <= 0){
        cout << "No hay vehiculos registrados." << endl;
        return;
    }
    for(int i = 0; i < cantReg; i++){
        Vehiculo obj = leerRegistro(i);
        if(obj.getEstado()){
            obj.Mostrar();
        }
    }
}

void ArchivoVehiculos::listadoFiltrado(int *l, const int TAM){
    Vehiculo veh;
    for(int i=0; i<TAM; i++){
        veh = leerRegistro(l[i]);
        veh.Mostrar();
    }
}

void ArchivoVehiculos::buscarPorId(){
    int d = cargarEntero("Ingrese el ID del vehiculo: ");
    int cantReg = contarRegistros();
    for(int i = 0; i < cantReg; i++){
        Vehiculo obj = leerRegistro(i);
        if(obj.getId() == d && obj.getEstado()){
            obj.Mostrar();
            return;
        }
    }
    cout << endl << "No existe un vehiculo con el id: " << d << endl;
}

void ArchivoVehiculos::buscarPorPatente(){
    cout << "Ingrese la patente del vehiculo a buscar (Sin espacios): ";
    char auxPatente[10];
    cargarCadena(auxPatente,10);
    Vehiculo obj;
    obj.hacerMayusculas(auxPatente);
    if(!obj.validarPatente(auxPatente)){
        cout << endl << "Error: Patente ingresada con formato invalido." << endl;
        return;
    }
    int pos = buscarRegistroPorPatente(auxPatente);
    if(pos < 0){
        cout << endl << "No existe ningun vehiculo con la patente " << auxPatente << endl;
        return;
    }
    obj = leerRegistro(pos);
    obj.Mostrar();
}

void ArchivoVehiculos::buscarPorMarca(){
    cout << "Ingrese el nombre de la marca: ";
    char marca[20];
    cargarCadena(marca, 20);
    ArchivoMarcas arcMar;
    int pos = arcMar.buscarRegistroxNombre(marca);
    if(pos < 0){
        cout << endl << "Error: El nombre de marca ingresado no coincide con ninguna marca en el archivo" << endl;
        return;
    }
    int idMarca = pos + 1;
    int cant = contarRegistros();
    Vehiculo veh;
    int coinciden = 0;
    for(int i=0; i<cant; i++){
        veh = leerRegistro(i);
        if(veh.getIdMarca() == idMarca && veh.getEstado()){
            coinciden++;
        }
    }
    if(coinciden == 0){
        cout << endl << "Actualmente no poseemos ningun vehiculo de la marca " << marca << endl;
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
        veh = leerRegistro(i);
        if(veh.getIdMarca() == idMarca && veh.getEstado()){
            posCoinciden[posAsignadas] = i;
            posAsignadas++;
        }
    }
    cout << "Cantidad de vehiculos de la marca "<< marca <<": " << TAM << endl;
    listadoFiltrado(posCoinciden, TAM);
    delete[] posCoinciden;
}

void ArchivoVehiculos::buscarPorModelo(){
    cout << "Ingrese el modelo: ";
    char modelo[20];
    cargarCadena(modelo, 20);
    int cant = contarRegistros();
    Vehiculo veh;
    int coinciden = 0;
    for(int i=0; i<cant; i++){
        veh = leerRegistro(i);
        if(strcmp(veh.getModelo(),modelo) == 0 && veh.getEstado()){
            coinciden++;
        }
    }
    if(coinciden == 0){
        cout << endl << "Actualmente no poseemos ningun vehiculo modelo " << modelo << endl;
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
        veh = leerRegistro(i);
        if(strcmp(veh.getModelo(),modelo) == 0 && veh.getEstado()){
            posCoinciden[posAsignadas] = i;
            posAsignadas++;
        }
    }
    cout << "Cantidad de vehiculos modelo "<< modelo <<": " << TAM << endl;
    listadoFiltrado(posCoinciden, TAM);
    delete[] posCoinciden;
}

void ArchivoVehiculos::buscarPorAnio(){
    cout << "Ingrese el rango de anios: " << endl << endl;
    int desde = cargarEntero("Desde: ");
    if(desde < 0){
        cout << endl << "Error: El anio no puede ser negativo" << endl;
    }
    cout << endl;
    int hasta = cargarEntero("Hasta: ");
    if(hasta < desde){
        cout << endl << "Error: El rango de anios ingresado es invalido" << endl;
    }
    int cant = contarRegistros();
    Vehiculo veh;
    int coinciden = 0;
    for(int i=0; i<cant; i++){
        veh = leerRegistro(i);
        if(veh.getAnio() >= desde && veh.getAnio() <= hasta && veh.getEstado()){
            coinciden++;
        }
    }
    if(coinciden == 0){
        cout << endl << "Actualmente no poseemos ningun vehiculo fabricado entre " << desde << " y " << hasta <<endl;
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
        veh = leerRegistro(i);
        if(veh.getAnio() >= desde && veh.getAnio() <= hasta && veh.getEstado()){
            posCoinciden[posAsignadas] = i;
            posAsignadas++;
        }
    }
    cout << endl << "Cantidad de vehiculos fabricados entre " << desde << " y " << hasta << ": " << TAM << endl;
    listadoFiltrado(posCoinciden, TAM);
    delete[] posCoinciden;
}

void ArchivoVehiculos::buscarPorColor(){
    cout << "Ingrese el modelo: ";
    char color[20];
    cargarCadena(color, 20);
    int cant = contarRegistros();
    Vehiculo veh;
    int coinciden = 0;
    for(int i=0; i<cant; i++){
        veh = leerRegistro(i);
        if(strcmp(veh.getColor(),color) == 0 && veh.getEstado()){
            coinciden++;
        }
    }
    if(coinciden == 0){
        cout << endl << "Actualmente no poseemos ningun vehiculo color " << color << endl;
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
        veh = leerRegistro(i);
        if(strcmp(veh.getColor(),color) == 0 && veh.getEstado()){
            posCoinciden[posAsignadas] = i;
            posAsignadas++;
        }
    }
    cout << "Cantidad de vehiculos color "<< color <<": " << TAM << endl;
    listadoFiltrado(posCoinciden, TAM);
    delete[] posCoinciden;
}

void ArchivoVehiculos::buscarPorKilometros(){
    cout << "Ingrese el rango de kilometros: " << endl << endl;
    int desde = cargarEntero("Desde: ");
    if(desde < 0){
        cout << endl << "Error: El kilometraje no puede ser negativo" << endl;
    }
    cout << endl;
    int hasta = cargarEntero("Hasta: ");
    if(hasta < desde){
        cout << endl << "Error: El rango de kilometros ingresado es invalido" << endl;
    }
    int cant = contarRegistros();
    Vehiculo veh;
    int coinciden = 0;
    for(int i=0; i<cant; i++){
        veh = leerRegistro(i);
        if(veh.getKilometros() >= desde && veh.getKilometros() <= hasta && veh.getEstado()){
            coinciden++;
        }
    }
    if(coinciden == 0){
        cout << endl << "Actualmente no poseemos ningun vehiculo con kilometraje entre " << desde << "km y " << hasta << "km" << endl;
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
        veh = leerRegistro(i);
        if(veh.getKilometros() >= desde && veh.getKilometros() <= hasta && veh.getEstado()){
            posCoinciden[posAsignadas] = i;
            posAsignadas++;
        }
    }
    cout << endl << "Cantidad de vehiculos con kilometraje entre " << desde << "km y " << hasta << "km: " << TAM << endl;
    listadoFiltrado(posCoinciden, TAM);
    delete[] posCoinciden;
}

void ArchivoVehiculos::buscarPorPrecio(){
    cout << fixed << setprecision(2);
    cout << "Ingresar rango de precio: " << endl << endl;
    float desde = cargarFlotante("Desde: $");
    if(desde < 0){
        cout << "Error: No se puede ingresar un monto negativo" << endl;
        return;
    }
    cout << endl;
    float hasta = cargarFlotante("Hasta: $");
    if(hasta < desde){
        cout << "Error: El rango ingresado es invalido" << endl;
        return;
    }
    int cant = contarRegistros();
    int coinciden = 0;
    Vehiculo v;
    for(int i=0; i<cant; i++){
        v = leerRegistro(i);
        if(v.getPrecio() >= desde && v.getPrecio() <= hasta && v.getEstado()){
            coinciden++;
        }
    }
    if(coinciden == 0){
        cout << endl << "No existe ninguna vehiculo con precio entre $" << desde << " y $" << hasta << endl;
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
        if(v.getPrecio() >= desde && v.getPrecio() <= hasta && v.getEstado()){
            posCoinciden[posAsignadas] = i;
            posAsignadas++;
        }
    }
    cout << endl << "Cantidad de vehiculos con precio entre $" << desde << " y $" << hasta << ": " << TAM <<endl;
    listadoFiltrado(posCoinciden, TAM);
    delete[] posCoinciden;
}

void ArchivoVehiculos::buscarPorCombustible(){
    cout << "Ingrese el tipo de combustible: ";
    char combustible[10];
    cargarCadena(combustible, 10);
    int cant = contarRegistros();
    Vehiculo veh;
    int coinciden = 0;
    for(int i=0; i<cant; i++){
        veh = leerRegistro(i);
        if(strcmp(veh.getCombustible(),combustible) == 0 && veh.getEstado()){
            coinciden++;
        }
    }
    if(coinciden == 0){
        cout << endl << "Actualmente no poseemos ningun vehiculo con combustible " << combustible << endl;
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
        veh = leerRegistro(i);
        if(strcmp(veh.getCombustible(),combustible) == 0 && veh.getEstado()){
            posCoinciden[posAsignadas] = i;
            posAsignadas++;
        }
    }
    cout << "Cantidad de vehiculos con combustible "<< combustible <<": " << TAM << endl;
    listadoFiltrado(posCoinciden, TAM);
    delete[] posCoinciden;
}

void ArchivoVehiculos::buscarPorFechaIngreso(){
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
    Vehiculo v;
    for(int i=0; i<cant; i++){
        v = leerRegistro(i);
        if(v.getFechaIngreso() >= desde && v.getFechaIngreso() <= hasta && v.getEstado()){
            coinciden++;
        }
    }
    if(coinciden == 0){
        cout << endl << "No existe ninguna vehiculo ingresado entre el " << desde.mostrarFechaFormato() << " y el " << hasta.mostrarFechaFormato() << endl;
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
        if(v.getFechaIngreso() >= desde && v.getFechaIngreso() <= hasta && v.getEstado()){
            posCoinciden[posAsignadas] = i;
            posAsignadas++;
        }
    }
    cout << endl << "Cantidad de vehiculos ingresados entre el " << desde.mostrarFechaFormato() << " y el " << hasta.mostrarFechaFormato() << ": "<< TAM <<endl;
    listadoFiltrado(posCoinciden, TAM);
    delete[] posCoinciden;
}

void ArchivoVehiculos::altaVehiculo(){
    Vehiculo obj;
    char patente[10];
    cout << "Ingrese la patente (Sin espacios): ";
    cargarCadena(patente,10);
    obj.hacerMayusculas(patente);
    if(!obj.validarPatente(patente)){
        cout << endl << "Error: Patente ingresada con formato invalido." << endl;
        return;
    }
    int pos = buscarRegistroPorPatente(patente);
    if(pos >= 0){
        cout << endl << "Error: Ya existe un vehiculo registrado con la patente " << patente << endl;
        return;
    }
    int idMarca = cargarEntero("Ingrese el id de la marca: ");
    ArchivoMarcas arcMarcas;
    int posMarca = arcMarcas.buscarRegistro(idMarca);
    Marca m;
    m = arcMarcas.leerRegistro(posMarca);
    if(posMarca == -1 || !m.getEstado()){
        cout << endl << "Error: No existe ninguna marca con id " << idMarca << endl;
        return;
    }
    int cant = contarRegistros();
    if(cant <0) cant = 0;
    int nro = cant + 1;
    obj.Cargar(nro, patente, idMarca);
    if(grabarRegistro(obj)){
        cout<< endl <<"Registro grabado exitosamente!"<<endl;
        return;
    }else{
        cout<< endl <<"Error al grabar el registro"<<endl;
        return;
    }
}

void ArchivoVehiculos::modificarPatente(){
    int nV = cargarEntero("Ingrese el ID del vehiculo a modificar: ");
    int pos = buscarRegistro(nV);
    if(pos < 0){
        cout << endl << "Error: No existe un vehiculo activo con el ID ingresado" << endl;
        return;
    }
    Vehiculo obj;
    cout << "Ingrese la nueva patente (Sin espacios): ";
    char patenteAux[10];
    cargarCadena(patenteAux,10);
    obj.hacerMayusculas(patenteAux);
    if(!obj.validarPatente(patenteAux)){
        cout << endl << "Error: Patente ingresada con formato invalido." << endl;
        return;
    }
    int pos2 = buscarRegistroPorPatente(patenteAux);
    if(pos2 > 0){
        cout << endl << "Error: Ya existe un vehiculo con esa patente." << endl;
        return;
    }
    obj = leerRegistro(pos);
    obj.setPatente(patenteAux);
    if(modificarRegistro(obj, pos)){
        cout << endl << "Patente modificada con exito!" << endl;
        return;
    } else {
        cout << endl << "Error al guardar la modificacion." << endl;
        return;
    }
}

void ArchivoVehiculos::modificarMarca(){
    int nV = cargarEntero("Ingrese el ID del vehiculo a modificar: ");
    int pos = buscarRegistro(nV);
    if(pos < 0){
        cout << endl << "Error: No existe un vehiculo activo con el ID ingresado" << endl;
        return;
    }
    Vehiculo obj;
    obj = leerRegistro(pos);
    int nuevaMarca = cargarEntero("Ingrese el ID de la nueva marca: ");
    ArchivoMarcas arcMarcas;
    int posMarca = arcMarcas.buscarRegistro(nuevaMarca);
    if(posMarca < 0){
        cout << endl << "Error: No existe una marca activa con el ID ingresado" << endl;
        return;
    }
    obj.setIdMarca(nuevaMarca);
    if(modificarRegistro(obj, pos)){
        cout << endl << "Marca modificada con exito!" << endl;
        return;
    } else {
        cout << endl << "Error al guardar la modificacion." << endl;
        return;
    }
}

void ArchivoVehiculos::modificarModelo(){
    int nV = cargarEntero("Ingrese el ID del vehiculo a modificar: ");
    int pos = buscarRegistro(nV);
    if(pos < 0){
        cout << endl << "Error: No existe un vehiculo activo con el ID ingresado" << endl;
        return;
    }
    Vehiculo obj;
    obj = leerRegistro(pos);
    char nuevoModelo[20];
    cout << "Ingrese el nuevo modelo: ";
    cargarCadena(nuevoModelo, 20);
    obj.setModelo(nuevoModelo);
    if(modificarRegistro(obj, pos)){
        cout << endl << "Modelo modificado con exito!" << endl;
        return;
    } else {
        cout << endl << "Error al guardar la modificacion." << endl;
        return;
    }
}

void ArchivoVehiculos::modificarAnio(){
    int nV = cargarEntero("Ingrese el ID del vehiculo a modificar: ");
    int pos = buscarRegistro(nV);
    if(pos < 0){
        cout << endl << "Error: No existe un vehiculo activo con el ID ingresado" << endl;
        return;
    }
    Vehiculo obj;
    obj = leerRegistro(pos);
    int nuevoAnio = cargarEntero("Ingrese el nuevo anio: ");
    obj.setAnio(nuevoAnio);
    Fecha hoy;
    hoy.setHoy();
    if(nuevoAnio > hoy.getAnio()){
        cout << "Error: No se puede ingresar un anio futuro" << endl;
        return;
    }
    if(modificarRegistro(obj, pos)){
        cout << endl << "Anio modificado con exito!" << endl;
        return;
    } else {
        cout << endl << "Error al guardar la modificacion." << endl;
        return;
    }
}

void ArchivoVehiculos::modificarColor(){
    int nV = cargarEntero("Ingrese el ID del vehiculo a modificar: ");
    int pos = buscarRegistro(nV);
    if(pos < 0){
        cout << endl << "Error: No existe un vehiculo activo con el ID ingresado" << endl;
        return;
    }
    Vehiculo obj;
    obj = leerRegistro(pos);
    char nuevoColor[20];
    cout << "Ingrese el nuevo color: ";
    cargarCadena(nuevoColor, 20);
    obj.setColor(nuevoColor);
    if(modificarRegistro(obj, pos)){
        cout << endl << "Color modificado con exito!" << endl;
        return;
    } else {
        cout << endl << "Error al guardar la modificacion." << endl;
        return;
    }
}

void ArchivoVehiculos::modificarKilometros(){
    int nV = cargarEntero("Ingrese el ID del vehiculo a modificar: ");
    int pos = buscarRegistro(nV);
    if(pos < 0){
        cout << endl << "Error: No existe un vehiculo activo con el ID ingresado" << endl;
        return;
    }
    Vehiculo obj;
    obj = leerRegistro(pos);
    int nuevosKms = cargarEntero("Ingrese el nuevo kilometraje: ");
    if(nuevosKms <= 0){
        cout << endl << "Error: No se puede colocar 0 o menos como kilometraje" << endl;
    }
    obj.setKilometros(nuevosKms);
    if(modificarRegistro(obj, pos)){
        cout << endl << "Kilometros modificados con exito!" << endl;
        return;
    } else {
        cout << endl << "Error al guardar la modificacion." << endl;
        return;
    }
}

void ArchivoVehiculos::modificarPrecio(){
    int nV = cargarEntero("Ingrese el ID del vehiculo a modificar: ");
    int pos = buscarRegistro(nV);
    if(pos < 0){
        cout << endl << "Error: No existe un vehiculo activo con el ID ingresado" << endl;
        return;
    }
    Vehiculo obj;
    obj = leerRegistro(pos);
    float nuevoPrecio = cargarFlotante("Ingrese el nuevo precio: ");
    if(nuevoPrecio <= 0){
        cout << endl << "Error: No se puede colocar 0 o menos como precio" << endl;
        return;
    }
    obj.setPrecio(nuevoPrecio);
    if(modificarRegistro(obj, pos)){
        cout << endl << "Precio modificado con exito!" << endl;
        return;
    } else {
        cout << endl << "Error al guardar la modificacion." << endl;
        return;
    }
}

void ArchivoVehiculos::modificarCombustible(){
    int nV = cargarEntero("Ingrese el ID del vehiculo a modificar: ");
    int pos = buscarRegistro(nV);
    if(pos < 0){
        cout << endl << "Error: No existe un vehiculo activo con el ID ingresado" << endl;
        return;
    }
    Vehiculo obj;
    obj = leerRegistro(pos);
    char nuevoCombustible[10];
    cout << "Ingrese el nuevo tipo de combustible: ";
    cargarCadena(nuevoCombustible, 10);
    obj.setCombustible(nuevoCombustible);
    if(modificarRegistro(obj, pos)){
        cout << endl << "Tipo de combustible modificado con exito!" << endl;
        return;
    } else {
        cout << endl << "Error al guardar la modificacion." << endl;
        return;
    }
}

void ArchivoVehiculos::modificarFechaIngreso(){
    int nV = cargarEntero("Ingrese el ID del vehiculo a modificar: ");
    int pos = buscarRegistro(nV);
    if(pos < 0){
        cout << endl << "Error: No existe un vehiculo activo con el ID ingresado" << endl;
        return;
    }
    Vehiculo obj;
    obj = leerRegistro(pos);
    Fecha nuevaFecha;
    cout << "Ingrese la nueva fecha de ingreso: " << endl;
    nuevaFecha.cargarFecha();
    Fecha hoy;
    hoy.setHoy();
    if(nuevaFecha > hoy){
        cout << endl << "Error: No se puede cargar una fecha futura a la de hoy" << endl;
        return;
    }
    obj.setFechaIngreso(nuevaFecha);
    if(modificarRegistro(obj, pos)){
        cout << endl << "Fecha de ingreso modificada con exito!" << endl;
        return;
    } else {
        cout << endl << "Error al guardar la modificacion." << endl;
        return;
    }
}

void ArchivoVehiculos::bajaVehiculo(){
    int nV = cargarEntero("Ingrese el ID del vehiculo a dar de baja: ");
    int pos = buscarRegistro(nV);
    if(pos < 0){
        cout << endl << "Error: No existe un vehiculo activo con el ID ingresado" << endl;
        return;
    }
    Vehiculo obj;
    obj = leerRegistro(pos);
    obj.setEstado(false);
    if(modificarRegistro(obj, pos)){
        cout << endl << "Baja del vehiculo realizada." << endl;
        return;
    } else {
        cout << endl << "Error al procesar la baja en el archivo." << endl;
        return;
    }
}

ArchivoVehiculos::~ArchivoVehiculos(){
}
