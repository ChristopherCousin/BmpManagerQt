#include "filemanager.h"

using namespace std;

FileManager::FileManager()
{
}

void FileManager::_ToGreyColour(string path, string savePath)
{
    timer.start();

    char Header[54]; //Cabecera que contiene tipo de archivo y bits de la imágen

    int width = 0;
    int height = 0;

    ifstream in; //BMP en color
    ofstream out; //BMP blanco y negro

    //Abrir imágenes
    in.open(path, ios::in | ios::binary);
    out.open(savePath, ios::out | ios::binary);

    //Copiar cabecera
    in.read((char*)(&Header), sizeof(Header));
    out.write((char*)(&Header), sizeof(Header));

    //Usamos la funcion seekg para ir a la posicion de offset del
    //bmp 18 que es el width en pixeles de la imagen
    in.seekg(0x0012);
    in.read((char*)&width, 4);
    in.read((char*)&height, 4);

    //Ahora nos posicionamos de la tabla de colores
    in.seekg(0x0036);

    //Mientras no llegue al final
    while (!in.eof()) {
        in.read((char*)(&pixel), sizeof(pixel)); //Lee la composición del color (r, g, b)
        char grayColor = (pixel.b, pixel.g, pixel.r); //Variable que establece el color en 8 bits
        out << grayColor << grayColor << grayColor; //Asigna el nuevo color a r, g, b
    }
    in.close();
    out.close();
    timeToFinish = timer.elapsed();
}

void FileManager::_MultiThreadToGreyColour(string path, string savePath)
{
    timer.start();

    Read(path);
    std::thread t1(static_toGrey, this);
    std::thread t2(static_toGrey2, this);
    std::thread t3(static_toGrey3, this);
    std::thread t4(static_toGrey4, this);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    CreateFile(savePath);

    timeToFinish = timer.elapsed();
}

void FileManager::Read(string path)
{
    ifstream file(path, std::ios::binary | std::ios::ate);
    streamsize size = file.tellg();
    vector<char> buffer(size);
    file.seekg(0, std::ios::beg);
    if (file.read(buffer.data(), size)) {
        /* worked! */
    }

    bufferSize = buffer.size();
    buffer2 = buffer;

    file.close();
}

char FileManager::grey(unsigned char g, unsigned char b, unsigned char r)
{
    return 0.72 * g + 0.07 * b + 0.21 * r;
}

void FileManager::Write(int offset)
{
    char grayColor = grey(buffer2[offset], buffer2[offset + 1], buffer2[offset + 2]);
    buffer2[offset++] = grayColor;
    buffer2[offset++] = grayColor;
    buffer2[offset++] = grayColor;
}

void FileManager::CreateFile(string savePath)
{
    out.open(savePath, ios::out | ios::binary);
    for (int i = 0; i < bufferSize; i++) {
        out << buffer2[i];
    }
    out.close();
}

void FileManager::ToGray(int num)
{
    if (num == 0) {
        int offset = 54; // 54 para ignorar Header
        while (offset < bufferSize / 4) { // mientras offset sea menor a la mitad del archivo
            Write(offset);
            offset += 3;
        }
    }
    else if(num == 1)
    {
        int offset = bufferSize / 4; // asignar offset a la mitad del archivo
        while (offset < bufferSize / 3)
        {
            Write(offset);
            offset += 3;
        }
    } else if(num == 2) {
        int offset = bufferSize / 3; // asignar offset a la mitad del archivo
        while (offset < bufferSize / 2)
        {
            Write(offset);
            offset += 3;
        }
    } else {
        int offset = bufferSize / 2; // asignar offset a la mitad del archivo
        while (offset < bufferSize)
        {
            Write(offset);
            offset += 3;
        }
    }
}
