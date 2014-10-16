#include "pixel.h"

Pixel::Pixel(int red, int green, int blue){
    if(red < 0 || red > 255) red = 0;
    if(green < 0 || green > 255) green = 0;
    if(blue < 0 || blue > 255) blue = 0;
    
    intensidades[0] = red;
    intensidades[1] = green;
    intensidades[2] = blue;
}

void Pixel::cambiarPixel(int red, int green, int blue){
    if(red < 0 || red > 255) red = 0;
    if(green < 0 || green > 255) green = 0;
    if(blue < 0 || blue > 255) blue = 0;
    
    intensidades[0] = red;
    intensidades[1] = green;
    intensidades[2] = blue;
}

int Pixel::red() const{
    return intensidades[0];
}

int Pixel::green() const{
    return intensidades[1];
}

int Pixel::blue() const{
    return intensidades[2];
}
