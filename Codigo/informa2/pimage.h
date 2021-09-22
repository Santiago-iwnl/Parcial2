#ifndef PIMAGE_H
#define PIMAGE_H

#include <iostream>
#include <QImage>
#include "string"
#include <math.h>
#include <fstream>

using namespace std;

constexpr int filas = 3, pixeles = 16;

class pimage
{

private:

    QImage image, *imageE;
    int w = 0, h = 0;
    int matriz[filas][pixeles][pixeles];
    float leds = 16, fw = 1,fh = 1;

public:
    pimage(string img);
    QRgb promcolor(QRgb color1, QRgb color2);
    void resize();
    void colors();
    void escribir();
};

#endif // PIMAGE_H
