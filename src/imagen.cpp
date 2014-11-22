#include "imagen.h"

void sort(vector <int> &v) {
    //algoritmo de burbujeo
    int sz = v.size();
    int i = 0;
    while(i < sz) {
        int j = 0;
        while(j < sz - 1 - i) {
            if (!(v[j] <= v[j + 1])) {
                int temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
            j++;
        }
        i++;
    }
}

Imagen::Imagen(int alto_param, int ancho_param) {
    Pixel negro(0, 0, 0);
    Pixel1DContainer filaNegra(ancho_param, negro);

    int i = 0;
    while (i < alto_param) {
        pixels.push_back(filaNegra);
        i++;
    }
}

Pixel Imagen::obtenerPixel(int fila, int columna) const {
    return pixels[fila][columna];
}

void Imagen::modificarPixel(int fila, int columna, const Pixel &pixel) {
    pixels[fila][columna] = pixel;
}

int Imagen::alto() const {
    return pixels.size();
}

int Imagen::ancho() const {
    return pixels[0].size();
}

int max(int a, int b) {
    return a > b ? a : b;
}
int min(int a, int b) {
    return a > b ? b : a;
}

vector<Pixel> kVecinos(Pixel2DContainer pixels, int pixel_i, int pixel_j, int k) {
    int alto = pixels.size();
    int ancho = pixels[0].size();

    vector<Pixel> resultado;
    int i = max(0, pixel_i - k + 1);
    while(i < min(alto, pixel_i + k)) {
        int j = max(0, pixel_j - k + 1);
        while(j < min(ancho, pixel_j + k)) {
            resultado.push_back(pixels[i][j]);
            j++;
        }
        i++;
    }

    return resultado;
}

Pixel promedio(vector<Pixel> pixels) {
    int r = 0, g = 0, b = 0;
    int cantidad = pixels.size();

    int i = 0;
    while (i < cantidad) {
        r += pixels[i].red();
        g += pixels[i].green();
        b += pixels[i].blue();

        i++;
    }

    Pixel resultado(r / cantidad, g / cantidad, b / cantidad);
    return resultado;
}

void Imagen::blur(int k) {
    int i = 0;

    Pixel pixel_negro(0, 0, 0);

    Pixel2DContainer nuevo_pixels;

    Pixel1DContainer filaNegra(ancho(), pixel_negro);
    int iter = 0;
    while (iter < alto()) {
        nuevo_pixels.push_back(filaNegra);
        iter++;
    }

    int kVecCompletos = (2 * k - 1) * (2 * k - 1);
    while (i < alto()) {
        int j = 0;
        while (j < ancho()) {
            vector<Pixel> kVec = kVecinos(pixels, i, j, k);

            if(kVec.size() == kVecCompletos)
                nuevo_pixels[i][j] = promedio(kVec);
            else nuevo_pixels[i][j] = pixel_negro;

            j++;
        }

        i++;
    }

    pixels = nuevo_pixels;
}

Pixel mediana(vector<Pixel> pixels) {
    vector<int> reds, greens, blues;
    int cantidad = pixels.size();

    int i = 0;
    while (i < cantidad) {
        reds.push_back(pixels[i].red());
        greens.push_back(pixels[i].green());
        blues.push_back(pixels[i].blue());

        i++;
    }

    sort(reds);
    sort(greens);
    sort(blues);

    Pixel resultado(reds[cantidad / 2], greens[cantidad / 2], blues[cantidad / 2]);
    return resultado;
}

void Imagen::acuarela(int k) {
    Pixel pixel_negro(0, 0, 0);

    Pixel2DContainer nuevo_pixels;

    Pixel1DContainer filaNegra(ancho(), pixel_negro);
    int iter = 0;
    while (iter < alto()) {
        nuevo_pixels.push_back(filaNegra);
        iter++;
    }

    int i = 0;
    while (i < alto()) {
        int j = 0;
        while (j < ancho()) {
            vector<Pixel> kVec = kVecinos(pixels, i, j, k);

            if(kVec.size() == (2 * k - 1) * (2 * k - 1))
                nuevo_pixels[i][j] = mediana(kVec);
            else nuevo_pixels[i][j] = pixel_negro;

            j++;
        }
        i++;
    }
    pixels = nuevo_pixels;
}



vector<pair<int, int> > Imagen::posicionesMasOscuras() const {
    int colorMasOscuro = 255 * 3;

    vector<pair<int, int> > resultado;

    int i = 0;
    while (i < alto()) {
        int j = 0;
        while (j < ancho()) {
            Pixel estePixel = pixels[i][j];
            int colorPixel = estePixel.red() + estePixel.green() + estePixel.blue();

            if (colorPixel < colorMasOscuro) colorMasOscuro = colorPixel;

            j++;
        }
        i++;
    }


    i = 0;
    while (i < alto()) {
        int j = 0;
        while (j < ancho()) {
            Pixel estePixel = pixels[i][j];
            int colorPixel = estePixel.red() + estePixel.green() + estePixel.blue();

            if (colorPixel == colorMasOscuro) resultado.push_back(make_pair(i, j));
            j++;
        }
        i++;
    }

    return resultado;
}


bool Imagen::operator==(const Imagen &otra) const {
    bool resultado = true;

    if(alto() != otra.alto() || ancho() != otra.ancho())
        resultado = false;
    else {
        int i = 0;
        while (i < alto()) {
            int j = 0;
            while (j < ancho()) {
                Pixel p1 = pixels[i][j];
                Pixel p2 = otra.obtenerPixel(i, j);
                if (p1.red() != p2.red() ||
                        p1.green() != p2.green() ||
                        p1.blue() != p2.blue())
                    resultado = false;
                j++;
            }
            i++;
        }
    }

    return resultado;
}

void Imagen::guardar(std::ostream& os) const {
    os << alto() << " " << ancho() << " ";
    int i = 0;
    os << "[";
    while (i < alto()) {
        int j = 0;
        while (j < ancho()) {
            if(i != 0 || j != 0) os << ",";
            pixels[i][j].guardar(os);

            j++;
        }
        i++;
    }
    os << "]";
}

void Imagen::cargar(std::istream& is) {
    int alto, ancho;
    is >> alto;
    is >> ancho;

    char charMolesto;
    is >> charMolesto; //corchete o coma

    vector<vector<Pixel> > nueva_imagen;

    int i = 0;
    while(i < alto) {
        int j = 0;
        vector<Pixel> fila;
        while(j < ancho) {
            Pixel este_pixel(0, 0, 0);
            este_pixel.cargar(is);

            is >> charMolesto;

            fila.push_back(este_pixel);
            j++;
        }

        nueva_imagen.push_back(fila);
        i++;
    }

    pixels = nueva_imagen;
}

