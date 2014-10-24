#include "pixel.h"

Pixel::Pixel(int red, int green, int blue) {
    if(red < 0 || red > 255) red = 0;
    if(green < 0 || green > 255) green = 0;
    if(blue < 0 || blue > 255) blue = 0;

    intensidades[0] = red;
    intensidades[1] = green;
    intensidades[2] = blue;
}

void Pixel::cambiarPixel(int red, int green, int blue) {
    if(red < 0 || red > 255) red = 0;
    if(green < 0 || green > 255) green = 0;
    if(blue < 0 || blue > 255) blue = 0;

    intensidades[0] = red;
    intensidades[1] = green;
    intensidades[2] = blue;
}

int Pixel::red() const {
    return intensidades[0];
}

int Pixel::green() const {
    return intensidades[1];
}

int Pixel::blue() const {
    return intensidades[2];
}

void Pixel::guardar(std::ostream& os) const {
    os << "(" << intensidades[0] << ";" << intensidades[1] << ";" << intensidades[2] << ")";
}

void Pixel::cargar(std::istream& is) {
    char charMolesto; //punto y coma o parentesis
    is >> charMolesto;

    int colores = 0;
    while(colores < 3) {
        int este_color;
        is >> este_color;
        intensidades[colores] = este_color;

        is >> charMolesto;
        colores++;
    }
}
