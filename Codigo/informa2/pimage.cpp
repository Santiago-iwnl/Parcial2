#include "pimage.h"

pimage::pimage(string img)
{
    if(image.load(img.c_str()) == false){
        cout << "No se pudo cargar la imagen. Verifique la ruta ingresada" << endl;
    }
    else{
        image = image.convertToFormat(QImage::Format_RGB888); // cada pixel tiene 3bytes (3 canales)
    }
}

void pimage::resize()
{
    //Método del vecino más cercano
    fw = image.width()/leds;
    fh = image.height()/leds;
    w = round(image.width()/fw);
    h = image.height()/fh;

    imageE = new QImage(w,h,QImage::Format_RGB888);

    for(int m = 0; m < h; m++){
        for(int f = 0; f < w; f++){
            X = f*fw;
            Y = m*fh;
            x = X;
            y = Y;
            if((X-x > 0.5) && (x+1 < w)){
                x += 1;
                if((Y-y > 0.5) && (y+1 < h)) y += 1;
            }
            imageE->setPixel(f,m,image.pixel(x,y));
        }
    }
    imageE->save("imagenescalada.jpg");


}



void pimage::colors() //Función que permite extraer los colores de la imagen redimensionada
{
    for(int f = 0; f < imageE->height(); f++){
        for(int c = 0; c < imageE->width(); c++){
            red = imageE->pixelColor(c,f).red();
            green = imageE->pixelColor(c,f).green();
            blue = imageE->pixelColor(c,f).blue();
            if((red == 255) && (green == 255) && (blue == 255)){
                red = 254;
                green = 254;
                blue = 254;
            }
            matriz[0][f][c] = red;
            matriz[1][f][c] = green;
            matriz[2][f][c] = blue;
        }
    }
}

void pimage::escribir()
{
    ofstream archivo;
    archivo.open("Datos.txt", ios::out);

    archivo << "{" << endl;
    for(int f = 0; f < 3; f++){
        archivo << "{" << endl;
        for(int c = 0; c < pixeles; c++){
            archivo << "{";
            for(int d = 0; d < pixeles; d++){
                archivo << matriz[f][c][d];
                if(d < pixeles-1) archivo << ",";
            }
            if(c < pixeles-1) archivo << "},";
            else archivo << "}";
        }
        archivo << endl;
        if(f < 2) archivo << "}," << endl;
        else archivo << "}" << endl;
    }

    archivo << "};";
    archivo.close();
}

pimage::~pimage()
{
    delete imageE;
}
