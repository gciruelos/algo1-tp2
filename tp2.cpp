#include "pixel.h"
#include "imagen.h"
#include "galeria_imagenes.h"

#include <algorithm>

/*TEST*/
void printVect(vector<Pixel> pixs){
    for(int i = 0; i<pixs.size(); i++){
        Pixel p = pixs[i];
        cout << "(" << p.red() << "," << p.green() << "," << p.blue() << ") " << flush;
    }
    cout << endl;
}
void prntImg(Imagen im){
    for(int i = 0; i<im.alto(); i++){
        for(int j = 0; j<im.ancho(); j++){
            Pixel p =  im.obtenerPixel(i, j);  
            cout << "(" << p.red() << "," << p.green() << "," << p.blue() << ") " <<"\t" <<flush;
            
        }
        cout << endl;
    }
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
vector<Imagen> dividir (Imagen img, int n, int m){
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
            


//void dividirYAgregar(const Imagen &imagen, int n, int m){




bool test(){
    Pixel gris(128,128,128);
    Pixel azul(0,0,255);
    Pixel negro(0,0,0);

    Imagen prueba(10, 6);
    for(int i = 0; i<prueba.alto(); i++){
        for(int j = 0; j<prueba.ancho(); j++){
            if ((i-j)%4 == 0) prueba.modificarPixel(i, j, gris);
            if ((i-j)%4 == 1) prueba.modificarPixel(i, j, azul);
            if ((i-j)%4 == 2) prueba.modificarPixel(i, j, negro);
        }
    }
    cout << "PRUEBA" << endl;
    prntImg(prueba);
    /*
    prueba.blur(2);
    cout << "BLUR" <<endl;
    prntImg(prueba);

    prueba.acuarela(2);
    cout << "ACUARELA" <<endl;
    prntImg(prueba);
    */
	cout << endl;

	vector<Imagen> res = dividir(prueba, 2, 2);
    for(int i = 0; i<res.size(); i++){
		prntImg(res[i]);cout << endl;
	}


    return true;
}
int main(){
    test(); 
    return 0;
}

