#ifndef CLSMENUCLIENTE_H_INCLUDED
#define CLSMENUCLIENTE_H_INCLUDED

class menuCliente {
    private:

    public:
        menuCliente();
        static void mostrarCabeceraTabla(int posX, int posY);
        void tablaClientes(int posX, int posY);
        void subMenuModificarCliente();
        void iniciar();
        ~menuCliente();
};

#endif // CLSMENUCLIENTE_H_INCLUDED
