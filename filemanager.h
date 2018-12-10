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
    void _ToGreyColour(std::string path, std::string savePath);
    void _MultiThreadToGreyColour(std::string path, std::string savePath);
    void primeraParte(int num);

    long long timeToFinish;
    int width = 0;
    int height = 0;
    int TotalPixel;
    std::ifstream in; //BMP en color
    std::ofstream out; //BMP blanco y negro
    struct rgb {
        unsigned char b, g, r;
    }
    pixel;

    int idx;
    int Mitadidx;
    int e = 0;


};

#endif // FILEMANAGER_H
