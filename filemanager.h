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
#include <vector>

class FileManager
{
public:
    FileManager();

    QElapsedTimer timer;
    // funcion que usaremos para pasar a gris la imagen SIN multihilo
    void _ToGreyColour(std::string path, std::string savePath);

    // funcion que usaremos para pasar a gris la imagen CON multihilo
    void _MultiThreadToGreyColour(std::string path, std::string savePath);

    static void static_toGrey(FileManager * instance)
            {
                instance->ToGray(0);
            }
    static void static_toGrey2(FileManager * instance)
            {
                instance->ToGray(1);
            }
    static void static_toGrey3(FileManager * instance)
            {
                instance->ToGray(2);
            }
    static void static_toGrey4(FileManager * instance)
            {
                instance->ToGray(3);
            }

    //Variable long long para almacenar el tiempo de conversion
    long long timeToFinish;

    int width = 0;
    int height = 0;

    //variable donde almacenaremos el total de pixeles del bmp
    int TotalPixel;
    //Variable donde almacenaremos el total de pixeles / 2 para partir el trabajo en 2
    int Mitadidx;

    void Read(std::string path);

    std::ofstream out; // El OutPut Archivo

    void Write(int offset);
    char grey(unsigned char g, unsigned char b, unsigned char r);
    void ToGray(int num); // esta es la funcion que pinta no la borres
    void CreateFile(std::string savePath);
    int bufferSize = 0;
     std::vector<char> buffer2;
    //declaramos la clase rgb para establecer los colores a escala de grises
    struct rgb {
        unsigned char b, g, r;
    }
    pixel;


};

#endif // FILEMANAGER_H
