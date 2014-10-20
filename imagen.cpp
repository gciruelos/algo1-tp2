#include "imagen.h"
#include <algorithm>

Imagen::Imagen(int alto_param, int ancho_param){
    Pixel negro(0,0,0);
    Pixel1DContainer filaNegra(ancho_param, negro);

    int i = 0;
    while (i<alto_param){
        pixels.push_back(filaNegra);
        i++;
    }
}

Pixel Imagen::obtenerPixel(int fila, int columna) const{
    return pixels[fila][columna];
}

void Imagen::modificarPixel(int fila, int columna, const Pixel &pixel){
    pixels[fila][columna] = pixel;
}

int Imagen::alto() const{
    return pixels.size();
}

int Imagen::ancho() const{
    return pixels[0].size();
}

int abs(int x){
    return x > 0 ? x : -x;
}

vector<Pixel> kVecinos(Pixel2DContainer pixels, int pixel_i, int pixel_j, int k){
    int alto = pixels.size();
    int ancho = pixels[0].size();
    
    vector<Pixel> resultado;
    int i = 0, j;
    while(i<alto){
        j = 0;
        while(j<ancho){
            if(abs(pixel_i-i)<k && abs(pixel_j-j)<k)
                resultado.push_back(pixels[i][j]);
            j++;
        }
        i++;
    }

    return resultado;
}

Pixel promedio(vector<Pixel> pixels){
    int r = 0, g = 0, b = 0;
    int cantidad = pixels.size();

    int i = 0;
    while (i<cantidad){
        r += pixels[i].red();
        g += pixels[i].green();
        b += pixels[i].blue();
        
        i++;
    }

    Pixel resultado(r/cantidad, g/cantidad, b/cantidad);
    return resultado;
}

void Imagen::blur(int k){
    int i = 0, j;

    Pixel pixel_negro(0,0,0);

    Pixel2DContainer nuevo_pixels;  

    Pixel1DContainer filaNegra(ancho(), pixel_negro);
    int iter = 0;
    while (iter<alto()){
        nuevo_pixels.push_back(filaNegra);
        iter++;
    }
  
    while (i<alto()){
        j = 0;
        while (j<ancho()){
            vector<Pixel> kVec = kVecinos(pixels, i, j, k); 

            if(kVec.size() == (2*k-1)*(2*k-1))
                nuevo_pixels[i][j] = promedio(kVec);
            else nuevo_pixels[i][j] = pixel_negro;
            
            j++;
        }
        i++;
    }
    pixels = nuevo_pixels;
}

Pixel mediana(vector<Pixel> pixels){
    vector<int> reds, greens, blues;
    int cantidad = pixels.size();

    int i = 0;
    while (i<cantidad){
        reds.push_back(pixels[i].red());
        greens.push_back(pixels[i].green());
        blues.push_back(pixels[i].blue()); 
        
        i++;
    }

    sort(reds.begin(), reds.end());
    sort(greens.begin(), greens.end());
    sort(blues.begin(), blues.end());
    
    Pixel resultado(reds[cantidad/2], greens[cantidad/2], blues[cantidad/2]);
    return resultado;
}

void Imagen::acuarela(int k){
    int i = 0, j;

    Pixel pixel_negro(0,0,0);

    Pixel2DContainer nuevo_pixels;  

    Pixel1DContainer filaNegra(ancho(), pixel_negro);
    int iter = 0;
    while (iter<alto()){
        nuevo_pixels.push_back(filaNegra);
        iter++;
    }
  
    while (i<alto()){
        j = 0;
        while (j<ancho()){
            vector<Pixel> kVec = kVecinos(pixels, i, j, k); 

            if(kVec.size() == (2*k-1)*(2*k-1))
                nuevo_pixels[i][j] = mediana(kVec);
            else nuevo_pixels[i][j] = pixel_negro;
            
            j++;
        }
        i++;
    }
    pixels = nuevo_pixels;
}



vector<pair<int,int> > Imagen::posicionesMasOscuras() const{
    int colorMasOscuro = 255*3;

    vector<pair<int, int> > resultado;

    int i = 0, j;
    while (i<alto()){
        j = 0;
        while (j<ancho()){
            Pixel estePixel = pixels[i][j];
            int colorPixel = estePixel.red()+estePixel.green()+estePixel.blue();

            if (colorPixel<colorMasOscuro) colorMasOscuro = colorPixel;
        }
    }


    i = 0;
    while (i<alto()){
        j = 0;
        while (j<ancho()){
            Pixel estePixel = pixels[i][j];
            int colorPixel = estePixel.red()+estePixel.green()+estePixel.blue();

            if (colorPixel<colorMasOscuro) resultado.push_back(make_pair(i, j));
        }
    }



    return resultado;
}
    

bool Imagen::operator==(const Imagen &otra) const{
    bool resultado = true;

    if(alto() != otra.alto() || ancho() != otra.ancho())
        resultado = false;
    else{
        int i = 0, j;
        while (i<alto()){
            j = 0;
            while (j<ancho()){
                Pixel p1 = pixels[i][j];
                Pixel p2 = otra.obtenerPixel(i,j);
                if (p1.red() != p2.red() || p1.green() != p2.green() || p1.blue() != p2.blue()) resultado = false;
            }
        }
    }
    
    return resultado;
}


