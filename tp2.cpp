#include "pixel.h"
#include "imagen.h"
#include "galeria_imagenes.h"


//#include "test.h"

#include <algorithm>

/*TEST*/
void outImagen(Imagen im){
	cout << im.alto() << " ";
	cout << im.ancho() << " ";

	int i = 0;
	cout << "[";
	while(i<im.alto()){
		int j = 0;
	    while(j<im.ancho()){
			Pixel p = im.obtenerPixel(i, j);
			cout << "(" << p.red() << ";" << p.green() << ";" << p.blue()  << ")";
			
			if(j!=im.ancho()-1 || i!=im.alto()-1) cout << ",";

			j++;
		}
		i++;
	}
	cout << "]";
}
/*FIN TEST*/


//PIXEL
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

//IMAGEN
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


//GALERIA

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
		
int main(){
	bool salir = false;
	while(!salir){
		cout << "¿Que desea hacer?" << endl;
		salir = true;
	}




    return 0;
}

