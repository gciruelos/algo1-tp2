#include "galeria_imagenes.h"


Imagen GaleriaImagenes::laMasChiquitaConPuntoBlanco () const {
    vector<Imagen> imagenes_blancas;
    vector<int> tamanio_imagenes;

    int k = 0;
    while (k < imagenes.size()) {
        int n = imagenes[k].alto();
        int m = imagenes[k].ancho();
        int i = 0;
        while (i < n) {
            int j = 0;
            while (j < m) {
                Pixel este_pixel = imagenes[k].obtenerPixel(i, j);
                if (este_pixel.red() == 255 && este_pixel.blue() == 255 && este_pixel.green() == 255) {
                    imagenes_blancas.push_back(imagenes[k]);
                    tamanio_imagenes.push_back(m * n);
                    j = m;  // para que termine el ciclo
                    i = n;  // porque ya encontramos el pixel
                }
                j++;

            }
            i++;
        }
        k++;
    }

    int mas_chica = tamanio_imagenes[0];
    int i_mas_chica = 0;
    int i = 1;
    while(i < imagenes_blancas.size()) {
        if(tamanio_imagenes[i] < mas_chica) {
            i_mas_chica = i;
            mas_chica = tamanio_imagenes[i];
        }
        i++;
    }
    return imagenes_blancas[i_mas_chica];

}


void GaleriaImagenes::agregarImagen(const Imagen &imagen) {
    vector<Imagen> imagenes_nuevas;
    vector<int> votos_nuevos;

    imagenes_nuevas.push_back(imagen);
    votos_nuevos.push_back(0);

    int i = 0;
    while(i < imagenes.size()) {
        imagenes_nuevas.push_back(imagenes[i]);
        votos_nuevos.push_back(votos[i]);

        i++;
    }
    imagenes = imagenes_nuevas;
    votos = votos_nuevos;
}

void GaleriaImagenes::votar(const Imagen &imagen) {
    int i = 0;
    std::vector<Imagen> imagenes_nuevas;
    std::vector<int> votos_nuevos;

    int votos_imagen;
    while (i < imagenes.size() && !(imagenes[i] == imagen)) {
        imagenes_nuevas.push_back(imagenes[i]);
        votos_nuevos.push_back(votos[i]);


        i++;
    }

    // requerimos que la imagen este, entonces en este estado i<imagenes.size() e imagenes[i]==imagen
    votos_imagen = votos[i];
    i++;


    while (votos[i] == votos_imagen && i < imagenes.size()) {
        imagenes_nuevas.push_back(imagenes[i]);
        votos_nuevos.push_back(votos[i]);

        i++;
    }

    imagenes_nuevas.push_back(imagen);
    votos_nuevos.push_back(votos_imagen + 1);

    while (i < imagenes.size()) {
        imagenes_nuevas.push_back(imagenes[i]);
        votos_nuevos.push_back(votos[i]);

        i++;
    }

    imagenes = imagenes_nuevas;
    votos = votos_nuevos;
}

void GaleriaImagenes::eliminarMasVotada() {
    imagenes.pop_back();
    votos.pop_back();
}


vector<Imagen> GaleriaImagenes::top10 () const {
    int i = 0;
    vector <Imagen> result;
    while (i < 10 && imagenes.size() - i - 1 < imagenes.size()) {
        result.push_back(imagenes[imagenes.size() - i - 1]);
        i++;
    }
    return result;
}


vector<Imagen> dividir (const Imagen &img, int n, int m) {
    vector<Imagen> resultado;

    int cols  = img.ancho() / n;
    int filas = img.alto() / m;

    int i = 0;

    while(i < img.alto()) {
        int j = 0;
        while(j < img.ancho()) {

            Imagen esta_imagen(filas, cols);

            int i_img = 0;
            while (i_img < filas) {
                int j_img = 0;
                while(j_img < cols) {
                    Pixel este_pixel = img.obtenerPixel(i + i_img, j + j_img);
                    esta_imagen.modificarPixel(i_img, j_img, este_pixel);

                    j_img++;
                }
                i_img++;
            }
            resultado.push_back(esta_imagen);
            j += cols;
        }
        i += filas;
    }

    return resultado;
}



void GaleriaImagenes::dividirYAgregar(const Imagen &imagen, int n, int m) {
    int alto = imagen.alto();
    int ancho = imagen.ancho();

    if (alto % m == 0 && ancho % n == 0) {
        vector<Imagen> dividida = dividir(imagen, n, m);

        int i = 0;
        while(i < dividida.size()) {
            this->agregarImagen(dividida[i]);
            i++;
        }
    }
}

void GaleriaImagenes::guardar(std::ostream& os) const {
    os << "[";

    int i = 0;
    while(i < imagenes.size()) {
        if (i != 0) os << ",";
        os << "(";
        imagenes[i].guardar(os);
        os << "," << votos[i] << ")";

        i++;
    }
    os << "]" << endl;
}

void GaleriaImagenes::cargar(std::istream& is) {
    Imagen im(1, 1);
    int numero_de_votos;

    vector<Imagen> imagenes_nuevas;
    vector<int> votos_nuevos;

    char charMolesto; // parentesis, coma o chorchete
    is >> charMolesto; // '['

    is >> charMolesto; // '(' o ']'
    while(charMolesto != ']') {  
        im.cargar(is);

        is >> charMolesto; // ','
        is >> numero_de_votos;
        is >> charMolesto; // ')'

        imagenes_nuevas.push_back(im);
        votos_nuevos.push_back(numero_de_votos);
        
        is >> charMolesto; // ',' o ']' y se termina el ciclo
        if(charMolesto == ',') is >>charMolesto; // '('
    }
    imagenes = imagenes_nuevas;
    votos = votos_nuevos;
}



