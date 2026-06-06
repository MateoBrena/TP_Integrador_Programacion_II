#include <iostream>
#include <cstring>
#include "clsArchivoVentas.h"
#include "clsArchivoClientes.h"
#include "clsArchivosVendedores.h"
#include "clsArchivoVehiculos.h"
#include "clsArchivoMarcas.h"
#include "cargarCadena.h"
using namespace std;

ArchivoVentas::ArchivoVentas(const char *n){
    strcpy(nombre, n);
}

Venta ArchivoVentas::leerRegistro(int pos){
    FILE *p = fopen(nombre,"rb");
    Venta obj;
    if(p == nullptr){
        obj.setNroVenta(-2);
        return obj;
    }
    obj.setNroVenta(-1);
    fseek(p,  sizeof obj * pos, 0);
    fread(&obj, sizeof obj, 1, p);
    fclose(p);

    return obj;

}

bool ArchivoVentas::grabarRegistro(Venta obj){
    FILE *p = fopen(nombre, "ab");
    if(p == nullptr){
        return false;
    }
    bool escribio = fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
    return escribio;
}

bool ArchivoVentas::modificarRegistro(Venta obj, int pos){
    FILE *p = fopen(nombre, "rb+");
    if(p == nullptr){
        return false;
    }
    fseek(p, sizeof obj * pos, 0);
    bool escribio = fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
    return escribio;
}

int ArchivoVentas::contarRegistros(){
    FILE *p = fopen(nombre, "rb");
    if(p == nullptr){
        return -1;
    }
    fseek(p,0,2);
    int cant = ftell(p)/sizeof(Venta);
    fclose(p);
    return cant;
}

int ArchivoVentas::contarRegistrosActivos(int ca){
    int cantActivos = 0;
    for(int i=0; i<ca; i++){
        Venta c = leerRegistro(i);
        if(c.getEstado()){
            cantActivos++;
        }
    }

    return cantActivos;
}


int ArchivoVentas::buscarRegistro(int d){
    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++){
        Venta obj = leerRegistro(i);
        if(obj.getNroVenta() == d && obj.getEstado()){
            return i;
        }
    }

    return -1;
}

int ArchivoVentas::buscarRegistroxCliente(int d){
    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++){
        Venta obj = leerRegistro(i);
        if(obj.getNroCliente() == d && obj.getEstado()){
            return i;
        }
    }

    return -1;
}

int ArchivoVentas::buscarRegistroxVendedor(int d){
    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++){
        Venta obj = leerRegistro(i);
        if(obj.getNroVendedor() == d && obj.getEstado()){
            return i;
        }
    }

    return -1;
}

int ArchivoVentas::buscarRegistroxVehiculo(int d){
    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++){
        Venta obj = leerRegistro(i);
        if(obj.getNroVehiculo() == d && obj.getEstado()){
            return i;
        }
    }

    return -1;
}

int ArchivoVentas::buscarRegistroxMarca(int d){
    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++){
        Venta obj = leerRegistro(i);
        if(obj.getIdMarcaVehiculo() == d && obj.getEstado()){
            return i;
        }
    }

    return -1;
}


void ArchivoVentas::listarRegistros(){
    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++){
        Venta obj = leerRegistro(i);
        if(obj.getEstado()){
            obj.Mostrar();
            cout << endl;
        }
    }
}

void ArchivoVentas::altaVenta(){
    int nC = cargarEntero("Ingrese el numero de cliente del comprador: ");
    ArchivoClientes arcCli;
    int pos = arcCli.buscarRegistro(nC);
    if(pos < 0){
        cout << endl << "Error: No existe un cliente activo con el numero de cliente ingresado" << endl;
        return;
    }
    int nV = cargarEntero("Ingrese el numero del vendedor que realiza la venta: ");
    ArchivoVendedores arcVen;
    pos = arcVen.buscarRegistro(nV);
    if(pos < 0){
        cout << endl << "Error: No existe un vendedor activo con el numero de vendedor ingresado" << endl;
        return;
    }
    Vehiculo obj;
    int nVeh = cargarEntero("Ingrese el numero de vehiculo a vender: ");
    ArchivoVehiculos arcVeh;
    pos = arcVeh.buscarRegistro(nVeh);
    if(pos < 0){
        cout << endl << "Error: No existe un vehiculo activo con el numero de vehiculo ingresado." << endl;
        return;
    }
    obj = arcVeh.leerRegistro(pos);
    int idMarca = obj.getIdMarca();
    Fecha f;
    Fecha hoy;
    hoy.setHoy();
    f.cargarFecha();
    if(f > hoy){
        cout << endl << "Error: No se puede ingresar una fecha futura." << endl;
        return;
    }
    obj = arcVeh.leerRegistro(pos);
    float m = obj.getPrecio();
    obj.setEstado(false);
    arcVeh.modificarRegistro(obj,pos);
    int cant = contarRegistros();
    if(cant <0) cant = 0;
    int nro = cant + 1;
    Venta v;
    v.Cargar(nro, f, nC, nV, nVeh, idMarca, m);
    if(grabarRegistro(v)){
        cout<< endl <<"Registro grabado exitosamente!"<<endl;
        return;
    }else{
        cout<< endl <<"Error al grabar el registro"<<endl;
        return;
    }
}

void ArchivoVentas::listadoFiltrado(int *l, const int TAM){
    Venta v;
    for(int i=0; i<TAM; i++){
        v = leerRegistro(l[i]);
        v.Mostrar();
    }
}

void ArchivoVentas::buscarPorId(){
    int d = cargarEntero("Ingrese el numero de la venta a buscar: ");
    int pos = buscarRegistro(d);
    if(pos < 0){
        cout << endl << "Error: No existe una venta activa con el ID ingresado" << endl;
        return;
    }
    Venta v = leerRegistro(pos);
    v.Mostrar();
}

void ArchivoVentas::buscarPorFecha(){
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
    Venta v;
    for(int i=0; i<cant; i++){
        v = leerRegistro(i);
        if(v.getFechaVenta() >= desde && v.getFechaVenta() <= hasta && v.getEstado()){
            coinciden++;
        }
    }
    if(coinciden == 0){
        cout << endl << "No existe ninguna venta realizada entre el " << desde.mostrarFechaFormato() << " y el " << hasta.mostrarFechaFormato() << endl;
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
        if(v.getFechaVenta() >= desde && v.getFechaVenta() <= hasta && v.getEstado()){
            posCoinciden[posAsignadas] = i;
            posAsignadas++;
        }
    }
    cout << endl << "Cantidad de ventas realizadas entre el " << desde.mostrarFechaFormato() << " y el " << hasta.mostrarFechaFormato() << ": "<< TAM <<endl;
    listadoFiltrado(posCoinciden, TAM);
    delete[] posCoinciden;
}

void ArchivoVentas::buscarPorCliente(){
    int nroC = cargarEntero("Ingrese el numero de cliente: ");
    int pos = buscarRegistroxCliente(nroC);
    if(pos < 0){
        cout << endl << "Error: No existe ninguna venta realizada al cliente con el ID " << nroC << endl;
        return;
    }
    int cant = contarRegistros();
    int coinciden = 0;
    Venta v;
    for(int i=0; i<cant; i++){
        v = leerRegistro(i);
        if(v.getNroCliente() == nroC && v.getEstado()){
            coinciden++;
        }
    }
    if(coinciden == 0){
        cout << endl << "No existe ninguna venta realizada al cliente con el ID " << nroC << endl;
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
        if(v.getNroCliente() == nroC && v.getEstado()){
            posCoinciden[posAsignadas] = i;
            posAsignadas++;
        }
    }
    cout << endl << "Cantidad de ventas realizadas al cliente con ID " << nroC << ": " << TAM << endl;
    listadoFiltrado(posCoinciden, TAM);
    delete[] posCoinciden;
}

void ArchivoVentas::buscarPorVendedor(){
    int nroV = cargarEntero("Ingrese el numero de vendedor: ");
    int pos = buscarRegistroxVendedor(nroV);
    if(pos < 0){
        cout << endl << "Error: No existe ninguna venta realizada por el vendedor con el ID " << nroV << endl;
        return;
    }
    int cant = contarRegistros();
    int coinciden = 0;
    Venta v;
    for(int i=0; i<cant; i++){
        v = leerRegistro(i);
        if(v.getNroVendedor() == nroV && v.getEstado()){
            coinciden++;
        }
    }
    if(coinciden == 0){
        cout << endl << "No existe ninguna venta realizada por el vendedor con el ID " << nroV << endl;
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
        if(v.getNroVendedor() == nroV && v.getEstado()){
            posCoinciden[posAsignadas] = i;
            posAsignadas++;
        }
    }
    cout << endl << "Cantidad de ventas realizadas por el vendedor con ID " << nroV << ": " << TAM << endl;
    listadoFiltrado(posCoinciden, TAM);
    delete[] posCoinciden;
}

void ArchivoVentas::buscarPorVehiculo(){
    int d = cargarEntero("Ingrese el numero de vehiculo: ");
    int pos = buscarRegistroxVehiculo(d);
    if(pos < 0){
        cout << endl << "Error: No existe una venta activa con el ID de vehiculo ingresado" << endl;
        return;
    }
    Venta v = leerRegistro(pos);
    v.Mostrar();
}

void ArchivoVentas::buscarPorMarca(){
    cout << "Ingrese el nombre de la marca: ";
    char nombre[20];
    cargarCadena(nombre, 20);
    ArchivoMarcas arcMar;
    int pos = arcMar.buscarRegistroxNombre(nombre);
    if(pos < 0){
        cout << endl << "No hay ninguna marca llamada " << nombre << endl;
        return;
    }
    Marca m;
    m = arcMar.leerRegistro(pos);
    int cant = contarRegistros();
    int coinciden = 0;
    Venta v;
    for(int i=0; i<cant; i++){
        v = leerRegistro(i);
        if(v.getIdMarcaVehiculo() == m.getId() && v.getEstado()){
            coinciden++;
        }
    }
    if(coinciden == 0){
        cout << endl << "No existe ninguna venta de un vehiculo de marca " << nombre << endl;
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
        if(v.getIdMarcaVehiculo() == m.getId() && v.getEstado()){
            posCoinciden[posAsignadas] = i;
            posAsignadas++;
        }
    }
    cout << endl << "Cantidad de ventas de vehiculos de marca " << nombre << ": " << TAM << endl;
    listadoFiltrado(posCoinciden, TAM);
    delete[] posCoinciden;
}

void ArchivoVentas::buscarPorMonto(){
    cout << "Ingresar rango de monto de venta: " << endl << endl;
    float desde = cargarFlotante("Desde: $");
    if(desde < 0){
        cout << "Error: No se puede ingresar un monto negativo" << endl;
        return;
    }
    cout << endl;
    float hasta = cargarFlotante("Hasta: $");
    if(hasta < desde){
        cout << "Error: El rango ingresado es incorrecto" << endl;
        return;
    }
    int cant = contarRegistros();
    int coinciden = 0;
    Venta v;
    for(int i=0; i<cant; i++){
        v = leerRegistro(i);
        if(v.getMonto() >= desde && v.getMonto() <= hasta && v.getEstado()){
            coinciden++;
        }
    }
    if(coinciden == 0){
        cout << endl << "No existe ninguna venta realizada con monto entre $" << desde << " y $" << hasta << endl;
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
        if(v.getMonto() >= desde && v.getMonto() <= hasta && v.getEstado()){
            posCoinciden[posAsignadas] = i;
            posAsignadas++;
        }
    }
    cout << endl << "Cantidad de ventas realizadas con monto entre $" << desde << " y $" << hasta << ": " << TAM <<endl;
    listadoFiltrado(posCoinciden, TAM);
    delete[] posCoinciden;
}

void ArchivoVentas::modificarFechaVenta(){
    int id = cargarEntero("Ingrese el ID de la venta a modificar: ");
    int pos = buscarRegistro(id);
    if(pos < 0){
        cout << endl << "Error: No existe una venta activa con el ID ingresado" << endl;
        return;
    }
    cout << "Ingrese la nueva fecha: " << endl;
    Fecha fAux;
    fAux.cargarFecha();
    Fecha hoy;
    hoy.setHoy();
    if(fAux > hoy){
        cout << endl << "Error: No se puede ingresar una fecha futura a la de hoy" << endl;
        return;
    }
    Venta v;
    v = leerRegistro(pos);
    v.setFechaVenta(fAux);
    if(modificarRegistro(v,pos)){
        cout<< endl <<"Registro grabado exitosamente!"<<endl;
        return;
    }else{
        cout<< endl <<"Error al grabar el registro"<<endl;
        return;
    }

}
void ArchivoVentas::modificarNroCliente(){
    int id = cargarEntero("Ingrese el ID de la venta a modificar: ");
    int pos = buscarRegistro(id);
    if(pos < 0){
        cout << endl << "Error: No existe una venta activa con el ID ingresado" << endl;
        return;
    }
    int cAux = cargarEntero("Ingrese el nuevo numero de cliente: ");
    ArchivoClientes arcCli;
    int pos2 = arcCli.buscarRegistro(cAux);
    if(pos2 < 0){
        cout << endl << "Error: No existe un cliente activo con el ID ingresado" << endl;
        return;
    }
    Venta v;
    v = leerRegistro(pos);
    v.setNroCliente(cAux);
    if(modificarRegistro(v,pos)){
        cout<< endl <<"Registro grabado exitosamente!"<<endl;
        return;
    }else{
        cout<< endl <<"Error al grabar el registro"<<endl;
        return;
    }
}
void ArchivoVentas::modificarNroVendedor(){
    int id = cargarEntero("Ingrese el ID de la venta a modificar: ");
    int pos = buscarRegistro(id);
    if(pos < 0){
        cout << endl << "Error: No existe una venta activa con el ID ingresado" << endl;
        return;
    }
    int nvAux = cargarEntero("Ingrese el nuevo numero de vendedor: ");
    ArchivoVendedores arcVen;
    int pos2 = arcVen.buscarRegistro(nvAux);
    if(pos2 < 0){
        cout << endl << "Error: No existe un vendedor activo con el ID ingresado" << endl;
        return;
    }
    Venta v;
    v = leerRegistro(pos);
    v.setNroVendedor(nvAux);
    if(modificarRegistro(v,pos)){
        cout<< endl <<"Registro grabado exitosamente!"<<endl;
        return;
    }else{
        cout<< endl <<"Error al grabar el registro"<<endl;
        return;
    }

}
void ArchivoVentas::modificarNroVehiculo(){
    int id = cargarEntero("Ingrese el ID de la venta a modificar: ");
    int pos = buscarRegistro(id);
    if(pos < 0){
        cout << endl << "Error: No existe una venta activa con el ID ingresado" << endl;
        return;
    }
    int nVeh = cargarEntero("Ingrese el nuevo numero de vehiculo: ");
    ArchivoVehiculos arcVeh;
    int pos2 = arcVeh.buscarRegistro(nVeh);
    if(pos2 < 0){
        cout << endl << "Error: No existe un vehiculo activo con el ID ingresado" << endl;
        return;
    }
    Vehiculo vNuevo;
    vNuevo = arcVeh.leerRegistro(pos2);
    int nuevaMarca = vNuevo.getIdMarca();
    float nuevoMonto = vNuevo.getPrecio();
    vNuevo.setEstado(false);
    Venta v;
    v = leerRegistro(pos);
    int nVehiculoAnt = v.getNroVehiculo();
    int posVehAnt = arcVeh.buscarRegistroInactivo(nVehiculoAnt);
    Vehiculo vAnt;
    vAnt = arcVeh.leerRegistro(posVehAnt);
    vAnt.setEstado(true);
    v.setNroVehiculo(nVeh);
    v.setIdMarcaVehiculo(nuevaMarca);
    v.setMonto(nuevoMonto);
    if(modificarRegistro(v,pos) && arcVeh.modificarRegistro(vNuevo, pos2) && arcVeh.modificarRegistro(vAnt, posVehAnt)){
        cout<< endl <<"Registro grabado exitosamente!"<<endl;
        return;
    }else{
        cout<< endl <<"Error al grabar el registro"<<endl;
        return;
    }
}

//void ArchivoVentas::modificarMonto(){
//    int id = cargarEntero("Ingrese el ID de la venta a modificar: ");
//    int pos = buscarRegistro(id);
//    if(pos < 0){
//        cout << endl << "Error: No existe una venta con el ID ingresado" << endl;
//        return;
//    }
//    float mAux = cargarFlotante("Ingrese el nuevo monto: ");
//    if(mAux < 0){
//        cout << endl << "Error: La venta no puede tener un monto negativo" << endl;
//        return;
//    }
//    Venta v;
//    v = leerRegistro(pos);
//    v.setMonto(mAux);
//    if(modificarRegistro(v,pos)){
//        cout<< endl <<"Registro grabado exitosamente!"<<endl;
//        return;
//    }else{
//        cout<< endl <<"Error al grabar el registro"<<endl;
//        return;
//    }
//}

void ArchivoVentas::bajaVenta(){
    int d = cargarEntero("Ingrese el ID de la venta a dar de baja: ");
    int pos = buscarRegistro(d);
    if(pos < 0){
        cout << endl << "Error: No existe una venta activa con el ID ingresado" <<endl;
        return;
    }
    Venta obj;
    obj = leerRegistro(pos);
    ArchivoVehiculos arcVeh;
    Vehiculo veh;
    int pos2 = arcVeh.buscarRegistroInactivo(obj.getNroVehiculo());
    veh = arcVeh.leerRegistro(pos2);
    veh.setEstado(true);
    obj.setEstado(false);
    if(modificarRegistro(obj, pos) && arcVeh.modificarRegistro(veh,pos2)){
        cout << endl <<"Baja realizada correctamente"<<endl;
        return;
    }else{
        cout << endl <<"Error al realizar la baja"<<endl;
        return;
    }
}

ArchivoVentas::~ArchivoVentas(){
}
