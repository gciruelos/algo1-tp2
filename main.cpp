#include "pixel.h"
#include "imagen.h"
#include "galeria_imagenes.h"
		
#include <string>
#include <fstream>

int main(){
	string input = "";
    GaleriaImagenes galeriaCargada;

	while(input != "x"){
	
        
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
        cout << endl;
        if (input == "1"){
            int k;
            string archivo_in;
            string archivo_out;

            cout << "Ingrese un k, el nombre del archivo de entrada y el de salida" << endl;
            cin >> k >> archivo_in >> archivo_out;

            ifstream ifs(archivo_in.c_str());
            ofstream ofs(archivo_out.c_str());

            Imagen im(1,1); im.cargar(ifs);

            im.blur(k);

            im.guardar(ofs);
        }
        else if(input == "2"){
            int k;
            string archivo_in;
            string archivo_out;

            cout << "Ingrese un k, el nombre del archivo de entrada y el de salida" << endl;
            cin >> k >> archivo_in >> archivo_out;

            ifstream ifs(archivo_in.c_str());
            ofstream ofs(archivo_out.c_str());

            Imagen im(1,1); im.cargar(ifs);

            im.blur(k);

            im.guardar(ofs);
        }
        else if(input == "3"){
            string archivo_in;

            cout << "Ingrese el nombre del archivo" << endl;
            cin >> archivo_in;

            ifstream ifs(archivo_in.c_str());
            galeriaCargada.cargar(ifs);
        }
        else if(input == "4"){
            string archivo_in;
        }
        else if(input == "5"){
            string archivo_in;
        }
        else if(input == "6"){
            string archivo_in;
        }
        else if(input == "7"){
            string archivo_in;
        }
        else if(input == "8"){
            string archivo_in;
        }
        else if(input == "9"){
            string archivo_in;
        }
        else if(input == "10"){
            string archivo_in;
        }
        else{
            if(input != "x") cout << "Opcion invalida, por favor seleccione una opcion valida (1-10, x)." << endl;
        }

	}

    return 0;
}

