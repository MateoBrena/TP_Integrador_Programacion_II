#ifndef CLSMENUVENTA_H_INCLUDED
#define CLSMENUVENTA_H_INCLUDED

class menuVenta {
    private:

    public:
        menuVenta();
        void mostrarCabeceraTabla(int posX, int posY);
        void tablaVentas(int posX, int posY);
        void subMenuModificarVenta();
        void iniciar();
        ~menuVenta();
};

#endif // CLSMENUVENTA_H_INCLUDED
