#include "filemanager.h"

using namespace std;

FileManager::FileManager()
{

}

void FileManager::_ToGreyColour(string path, string savePath)
{
    struct rgb {
        unsigned char b, g, r;
    }
    pixel;

    char Header[54]; //Cabecera que contiene tipo de archivo y bits de la imágen

    int width = 0;
    int height = 0;

    ifstream in; //BMP en color
    ofstream out; //BMP blanco y negro

        //Abrir imágenes
        in.open(path, ios::in | ios::binary);
        out.open(savePath, ios::out | ios::binary);

        //Copiar cabecera
        in.read((char *)(&Header), sizeof(Header));
        out.write((char *)(&Header), sizeof(Header));

        //Usamos la funcion seekg para ir a la posicion de offset del
        //bmp 18 que es el width en pixeles de la imagen
        in.seekg(0x0012);
        in.read((char *)&width, 4);

        //Ahora vamos a la posicion del height
        in.seekg(0x0016);
        in.read((char *)&height, 4);

        //Ahora nos posicionamos de la tabla de colores
        in.seekg(0x0036);

        //Mientras no llegue al final
        while (!in.eof()) {
            in.read((char *)(&pixel), sizeof(pixel)); //Lee la composición del color (r, g, b)
            char grayColor = (pixel.b, pixel.g, pixel.r); //Variable que establece el color en 8 bits
            out << grayColor << grayColor << grayColor; //Asigna el nuevo color a r, g, b
        }
        in.close();
        out.close();
}

void FileManager::_MultiThreadToGreyColour(string path, string savePath)
{

    char Header[54]; //Cabecera que contiene tipo de archivo y bits de la imágen



        //Abrir imágenes
        in.open(path, ios::in | ios::binary);
        out.open(savePath, ios::out | ios::binary);

        //Copiar cabecera
        in.read((char *)(&Header), sizeof(Header));
        out.write((char *)(&Header), sizeof(Header));

        //Usamos la funcion seekg para ir a la posicion de offset del
        //bmp 18 que es el width en pixeles de la imagen
        in.seekg(0x0012);
        in.read((char *)&width, 4);
        in.read((char *)&height, 4);
        TotalPixel = width * height;
        //Ahora nos posicionamos de la tabla de colores

        int idx = 0;
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    idx += 3;
                }
            }
         Mitadidx = idx /2;
         //in.seekg(idx);

         FileManager * taskPtr = new FileManager();
         std::thread th(&FileManager::primeraParte, taskPtr, 0);
         primeraParte(1);
            in.close();
            out.close();

}

void FileManager::primeraParte(int num) {
    int e = 0;
    //Mientras no llegue al final

    // porque debugeas? va lento es este boton de
    if(num==0) {
        in.seekg(0x0036);
        while(in.tellg() >= 0x0036 && in.tellg() <= Mitadidx) {
            in.read((char*)(&pixel), sizeof(pixel)); //Lee la composición del color (r, g, b)
           char grayColor = (pixel.b, pixel.g, pixel.r); //Establece el color en 8 bits
           out << grayColor << grayColor << grayColor; //Asigna el nuevo color a r, g, b
        }
    }
    else {
        in.seekg(Mitadidx);
        while (!in.eof()){
            in.read((char*)(&pixel), sizeof(pixel)); //Lee la composición del color (r, g, b)
           char grayColor = (pixel.b, pixel.g, pixel.r); //Establece el color en 8 bits
           out << grayColor << grayColor << grayColor; //Asigna el nuevo color a r, g, b
        }
    }

}
