#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <fstream>
#include <conio.h>
#include <string.h>
#include <math.h>
#include <QString>
#include <QtDebug>

class FileManager
{
public:
    FileManager();
    void _ToGreyColour(std::string path, std::string savePath);
    void _MultiThreadToGreyColour(std::string path, std::string savePath);
};

#endif // FILEMANAGER_H
