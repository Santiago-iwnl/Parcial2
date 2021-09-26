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
    int posx = 0, posy = 0;
    float  posX = 0, posY = 0;
    fw = image.width()/leds;
    fh = image.height()/leds;
    w = round(image.width()/fw);
    h = image.height()/fh;

    imageE = new QImage(w,h,QImage::Format_RGB888);

    for(int m = 0; m < h; m++){
        for(int f = 0; f < w; f++){
            posX = f*fw;
            posY = m*fh;
            posx = posX;
            posy = posY;
            if((posX-posx > 0.5) && (posx+1 < w)){
                posx += 1;
                if((posY-posy > 0.5) && (posy+1 < h)) posy += 1;
            }
            imageE->setPixel(f,m,image.pixel(posx,posy));
        }
    }
    imageE->save("imagenescalada.jpg");
}



void pimage::colors() //Función que permite extraer los colores de la imagen redimensionada
{
    int red = 0, green = 0, blue = 0;
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
    archivo.open("DatosM.txt", ios::out);

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
