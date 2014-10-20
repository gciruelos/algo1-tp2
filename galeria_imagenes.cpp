#include "galeria_imagenes.h"

void GaleriaImagenes::agregarImagen(const Imagen &imagen){
    vector<Imagen> imagenes_nuevas;
    vector<int> votos_nuevos;

	imagenes_nuevas.push_back(imagen);
	votos_nuevos.push_back(0);

	int i = 0;
	while(i < imagenes.size()){
		imagenes_nuevas.push_back(imagenes[i]);
		votos_nuevos.push_back(votos[i]);

		i++;
	}
}

void GaleriaImagenes::votar(const Imagen &imagen){
    int i = 0;
    while (i<imagenes.size()){
        if (imagenes[i] == imagen){
            votos[i]++;
        }
    }
}

void GaleriaImagenes::eliminarMasVotada(){
    if(imagenes.size()>0){
        imagenes.pop_back();
        votos.pop_back();
    }
}


vector<Imagen> dividir (const Imagen &img, int n, int m){
	vector<Imagen> resultado;

    int cols  = img.ancho() / n;
	int filas = img.alto() / m;

	int i = 0, j;
 	
	while(i<img.alto()){
		j = 0;
		while(j<img.ancho()){
			
			int i_img = 0, j_img;
			Imagen esta_imagen(filas, cols);

			while (i_img < filas){
				j_img = 0;
				while(j_img < cols){                   
					Pixel este_pixel = img.obtenerPixel(i+i_img, j+j_img);
					esta_imagen.modificarPixel(i_img, j_img, este_pixel);

					j_img++;
				}
				i_img++;
			}
			resultado.push_back(esta_imagen);
			j+=cols;
		}
		i+=filas;
	}

	return resultado;
}
            


void GaleriaImagenes::dividirYAgregar(const Imagen &imagen, int n, int m){
	int alto = imagen.alto();
	int ancho = imagen.ancho();

	if (alto%m==0 && ancho%n==0){
		vector<Imagen> dividida = dividir(imagen, n, m);
       
	    int i = 0;
		while(i<dividida.size()){
			this->agregarImagen(dividida[i]);
		}
	}
}
