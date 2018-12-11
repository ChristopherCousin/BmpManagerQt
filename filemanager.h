#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <fstream>
#include <conio.h>
#include <string.h>
#include <math.h>
#include <QString>
#include <QtDebug>
#include <thread>
#include <future>
#include <QElapsedTimer>

class FileManager
{
public:
    FileManager();
    // funcion que usaremos para pasar a gris la imagen SIN multihilo
    void _ToGreyColour(std::string path, std::string savePath);
    void ToGrey(int num);

    // funcion que usaremos para pasar a gris la imagen CON multihilo
    void _MultiThreadToGreyColour(std::string path, std::string savePath);

    static void static_primeraParte(FileManager * instance)
            {
                instance->ToGrey(0);
            }
    static void static_primeraParte2(FileManager * instance)
            {
                instance->ToGrey(1);
            }

    //Variable long long para almacenar el tiempo de conversion
    long long timeToFinish;

    int width = 0;
    int height = 0;

    //variable donde almacenaremos el total de pixeles del bmp
    int TotalPixel;
    //Variable donde almacenaremos el total de pixeles / 2 para partir el trabajo en 2
    int Mitadidx;


    std::ifstream in;  // Input archivo
    std::ofstream out; // El OutPut Archivo


    //declaramos la clase rgb para establecer los colores a escala de grises
    struct rgb {
        unsigned char b, g, r;
    }
    pixel;


};

#endif // FILEMANAGER_H
