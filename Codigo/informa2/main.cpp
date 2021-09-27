#include "pimage.h"

int main()
{
    string ruta;

    cout << "Ingrese la ruta de la imagen: ";
    getline(cin, ruta);
    fflush(stdin);

    pimage imagen(ruta);

    imagen.resize();
    imagen.colors();
    imagen.escribir();

    return 0;
}
