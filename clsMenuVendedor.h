#ifndef CLSMENUVENDEDOR_H_INCLUDED
#define CLSMENUVENDEDOR_H_INCLUDED

class menuVendedor {
    private:

    public:
        menuVendedor();
        void iniciar();
        void subMenuModificarVendedor();
        static void mostrarCabeceraTabla(int posX, int posY);
        void tablaVendedores(int posX, int posY);
        ~menuVendedor();
};

#endif // CLSMENUVENDEDOR_H_INCLUDED
