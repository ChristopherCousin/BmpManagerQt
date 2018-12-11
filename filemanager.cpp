#include "filemanager.h"

using namespace std;

FileManager::FileManager()
{

}

void FileManager::_ToGreyColour(string path, string savePath)
{
    QElapsedTimer timer;
    timer.start();
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
        timeToFinish = timer.elapsed();
}

void FileManager::_MultiThreadToGreyColour(string path, string savePath)
{
    QElapsedTimer timer;
    timer.start();

    char Header[54]; //Cabecera que contiene tipo de archivo y bits de la imágen



        //Abrir imágenes
        in.open(path, ios::in | ios::binary);
        out.open(savePath, ios::out | ios::binary);

        //Copiar cabecera
        in.read((char *)(&Header), sizeof(Header));
        out.write((char *)(&Header), sizeof(Header));

        //Usamos la funcion seekg para ir a la posicion de offset del
        //bmp 12 que es el width en pixeles de la imagen y en la siguiente esta el heigth
        in.seekg(0x0012);
        in.read((char *)&width, 4);
        in.read((char *)&height, 4);
        TotalPixel = width * height;

        //Calculo los pixeles de la imagen
        int offsets = TotalPixel * 3;

            //la mitad
         Mitadidx = offsets /2;

         //
         std::thread t1(static_primeraParte,this);
         std::thread t2(static_primeraParte2,this);
         t1.join();
         t2.join();
         in.close();
         out.close();
         timeToFinish = timer.elapsed();
}
void FileManager::ToGrey(int num) {

    if(num==0) {

        //Ahora nos posicionamos de la tabla de colores
        in.seekg(0x0036);
        while(in.tellg() >= 0x0036 && in.tellg() <= Mitadidx)
        {
           in.read((char*)(&pixel), sizeof(pixel)); // Hacemos un read en el puntero que hemos indicado anteriormente con el puntero de pixel y
                                                    // el tamaño a extraer en caracteres que es el sizeofpixel

           char grayColor = (pixel.b, pixel.g, pixel.r); //Establece el color en 8 bits
           out << grayColor << grayColor << grayColor; //Asigna el nuevo color a r, g, b
        }
    } else {

        //ponemos la posicion del proximo caracter que es la mitad del total de pixeles.
        in.seekg(Mitadidx);
        while (!in.eof()){
           in.read((char*)(&pixel), sizeof(pixel));
           char grayColor = (pixel.b, pixel.g, pixel.r);
           out << grayColor << grayColor << grayColor;
        }
    } // END If

}
