#include <iostream>
#include <cstring>
#include <limits>
using namespace std;

void cargarCadena(char *palabra, int tam){
    string texto;
    if(cin.peek()=='\n'){
        cin.ignore();
    }
    getline(cin, texto);
    strncpy(palabra, texto.c_str(), tam);
    palabra[tam-1]='\0';
}

int cargarEntero(string mensaje){
    int numero;
    while (true) {
        cout << mensaje;
        if (!(cin >> numero)) {
            //si el usuario ingresa texto en lugar de un número
            cout << endl << "Error: Ingreso invalido. Debes ingresar un numero entero" << endl << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            //se leyó un número.
            //por las dudas limpiamos cualquier basura extra que el usuario haya puesto después del número
            //incluyendo el'\n' del Enter para que no quede trabado
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            return numero;
        }
    }
}

float cargarFlotante(string mensaje){
    float numero;
    while (true) {
        cout << mensaje;
        if (!(cin >> numero)) {
            cout << endl << "Error: Ingreso invalido. Debes ingresar un numero flotante" << endl << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return numero;
        }
    }
}
