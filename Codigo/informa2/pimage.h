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
    float fw = 1.0,fh = 1.0;

public:
    pimage(string img);
    void resize();
    void colors();
    void escribir();
    ~pimage();
};

#endif // PIMAGE_H
