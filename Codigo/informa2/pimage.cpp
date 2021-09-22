#include "pimage.h"

pimage::pimage(string img)
{
    if(image.load(img.c_str()) == false){
        cout << "No se pudo cargar la imagen. Verifique la ruta ingresada" << endl;
    }
    else{
        cout << "Se cargo exitosamente la imagen" << endl;
        image = image.convertToFormat(QImage::Format_RGB888);
    }
}

QRgb pimage::promcolor(QRgb color1, QRgb color2)
{
    return qRgb((qRed(color1)+qRed(color2))/2,(qGreen(color1)+qGreen(color2))/2,(qBlue(color1)+qBlue(color2))/2);
}

void pimage::resize()
{
    QRgb mColor;

    fw = image.width()/leds;
    fh = image.height()/leds;
    w = round(image.width()/fw);
    h = image.height();

    imageE = new QImage(w,h/fh,QImage::Format_RGB888);

    for(int m = 0; m < h; m++){
        for(int f = 0; f < w; f++){
            if((f*fw)+1 < w){ //Ver si dejar el > o el < (signo)
                mColor = promcolor(image.pixel(f*fw,m),image.pixel((f*fw)+1,m));
            }
            else{
                mColor = image.pixel(f*fw,m);
            }
            image.setPixel(f,m,mColor);
        }
    }

    h = round(h/fh);

    for(int m = 0; m < w; m++){
        for(int f = 0; f < h; f++){
            if((f*fh)+1 < h){
                mColor = promcolor(image.pixel(m,f*fh),image.pixel(m,(f*fh)+1));
            }
            else{
                mColor = image.pixel(m,f*fh);
            }
            imageE->setPixel(m,f,mColor);
        }
    }

    imageE->save("imagenescalada.jpg");
}


