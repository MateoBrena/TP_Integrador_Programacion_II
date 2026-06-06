#ifndef CLSMENUCATEGORIAVENDEDOR_H_INCLUDED
#define CLSMENUCATEGORIAVENDEDOR_H_INCLUDED

class menuCategoriaVendedor {
    private:

    public:
        menuCategoriaVendedor();
        void mostrarCabeceraTabla(int posX, int posY);
        void tablaCategorias(int posX, int posY);
        void subMenuBuscarCategoria();
        void subMenuModificarCategoria();
        void iniciar();
        ~menuCategoriaVendedor();
};

#endif // CLSMENUCATEGORIAVENDEDOR_H_INCLUDED
