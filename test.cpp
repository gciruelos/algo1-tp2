#include "pixel.h"
#include "imagen.h"
#include "galeria_imagenes.h"

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
	cout << "]"<<endl;
}

int main(){
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
    outImagen(prueba);
  
    prueba.blur(2);
    cout << "BLUR" <<endl;
    prntImg(prueba);

    prueba.acuarela(2);
    cout << "ACUARELA" <<endl;
    prntImg(prueba);
  
    cout << endl;

    /*vector<Imagen> res = dividir(prueba, 2, 2);
    for(int i = 0; i<res.size(); i++){
        outImagen(res[i]);cout << endl;
    }*/
    
    return 0;
}

