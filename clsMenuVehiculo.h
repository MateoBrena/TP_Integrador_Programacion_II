#ifndef CLSMENUVEHICULO_H_INCLUDED
#define CLSMENUVEHICULO_H_INCLUDED

class menuVehiculo {
    private:

    public:
        menuVehiculo();
        void mostrarCabeceraTabla(int posX, int posY);
        void tablaVehiculos(int posX, int posY);
        void subMenuModificarVehiculo();
        void iniciar();
        ~menuVehiculo();
};

#endif // CLSMENUVEHICULO_H_INCLUDED
