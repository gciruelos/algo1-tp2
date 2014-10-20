#include "pixel.h"
#include "imagen.h"
#include "galeria_imagenes.h"
		

void analizarInput(char c){
    int i = 0;
}


int main(){
	char input = ' ';
    GaleriaImagenes galeriaCargada;

	while(input != 'x'){
	
        
        cout << "________________________________________"<< endl;
        cout << "|                                      |"<< endl;
        cout << "| 1. blur                              |"<< endl;
        cout << "| 2. acuarela                          |"<< endl;
        cout << "| 3. cargar galeria                    |"<< endl;
        cout << "| 4. dividir y agregar                 |"<< endl;
        cout << "| 5. posiciones mas oscuras            |"<< endl;
        cout << "| 6. la mas chiquita con punto blanco  |"<< endl;
        cout << "| 7. agregar imagen                    |"<< endl;
        cout << "| 8. votar                             |"<< endl;
        cout << "| 9. eliminar mas votada               |"<< endl;
        cout << "| 10. guardar galeria                  |"<< endl;
        cout << "|______________________________________|"<< endl;
		cout << "¿Que desea hacer? ";    
        cin >> input;
        cout << endl << endl;;
	}




    return 0;
}

