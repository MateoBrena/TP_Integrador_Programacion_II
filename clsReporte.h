#ifndef CLSREPORTE_H_INCLUDED
#define CLSREPORTE_H_INCLUDED

#include "clsArchivoClientes.h"
#include "clsArchivosVendedores.h"
#include "clsArchivosCategoriaVendedor.h"
#include "clsArchivoMarcas.h"
#include "clsArchivoVehiculos.h"
#include "clsArchivoVentas.h"

class Reporte{
    private:
    public:
        Reporte();
        int buscarMayor(int *vec, int tam);
        int buscarMayor(float *vec, int tam);
        void cantVendedoresSinventas();
        void clienteMasComproUnidades();
        void clienteMasComproMonto();
        void mayorVendedor();
        void marcaMasVendida();
        void ventasxMes();
        ~Reporte();
};

#endif // CLSREPORTE_H_INCLUDED
