#include "pixel.h"
#include "imagen.h"
#include "galeria_imagenes.h"
		
#include <string>
#include <fstream>

int main(){
	string input = "";
    GaleriaImagenes galeriaCargada;
    string archivo_galeria;

	while(input != "x"){
	
        
        cout << "________________________________________"<< endl;
        cout << "|                                      |"<< endl;
        cout << "| 1. blur                              |"<< endl;
        cout << "| 2. acuarela                          |"<< endl;
        cout << "| 3. cargar galeria                    |"<< endl;
        cout << "| 4. dividir y agregar                 |"<< endl;
        cout << "| 5. posiciones mas oscuras            |"<< endl;
        cout << "| 6. top 10                            |"<< endl;
        cout << "| 7. la mas chiquita con punto blanco  |"<< endl;
        cout << "| 8. agregar imagen                    |"<< endl;
        cout << "| 9. votar                             |"<< endl;
        cout << "| 10. eliminar mas votada              |"<< endl;
        cout << "| 11. guardar galeria                  |"<< endl;
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
             
            cerr << "Cargo imagen"<< endl;
            im.blur(k);
            cerr << "Hizo blur" <<endl;

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
            archivo_galeria = archivo_in;
        }
        else if(input == "4"){
            string archivo_in, archivo_in2;
            int n, m;

            cout << "Ingrese el nombre del archivo de la galeria, el nombre del archivo de la imagen, el n y el m" << endl;

            cin >> archivo_in >> archivo_in2 >> n >> m;

            ifstream ifs_galeria(archivo_in.c_str());
            ifstream ifs_imagen(archivo_in2.c_str());

            galeriaCargada.cargar(ifs_galeria);

            Imagen im(1,1); im.cargar(ifs_imagen);

            galeriaCargada.dividirYAgregar(im, n, m);
        }
        else if(input == "5"){
            string archivo_in;

            cout << "Ingrese el nombre del archivo de la imagen" << endl;

            ifstream ifs(archivo_in.c_str());

            Imagen im(1,1); im.cargar(ifs);

            vector<pair<int, int> > resultado = im.posicionesMasOscuras();
            int i = 0;
            while(i<resultado.size()){
                cout <<"(" << resultado[i].first << "," << resultado[i].second << ")";
            }
            cout << endl;

            galeriaCargada.agregarImagen(im);
        }
        else if(input == "6"){
            string archivo_out;

            cout << "Ingrese el nombre del archivo para el output" << endl;

            ofstream ofs(archivo_out.c_str());

            vector<Imagen> top = galeriaCargada.top10();

            int i = 0;
            ofs << "[";
            while(i<top.size()){
                if (i!=0) ofs << ",";
                top[i].guardar(ofs);
            }
            ofs << "]";
        }
        else if(input == "7"){
            string archivo_out;

            cout << "Ingrese el nombre del archivo para el output" << endl;

            ofstream ofs(archivo_out.c_str());

            Imagen resultado = galeriaCargada.laMasChiquitaConPuntoBlanco();
            resultado.guardar(ofs);
        }
        else if(input == "8"){
            string archivo_in;

            cout << "Ingrese el nombre del archivo de la imagen" << endl;

            ifstream ifs(archivo_in.c_str());

            Imagen im(1,1); im.cargar(ifs);

            galeriaCargada.agregarImagen(im);
        }
        else if(input == "9"){
            string archivo_in;

            cout << "Ingrese el nombre del archivo de la imagen" << endl;

            ifstream ifs(archivo_in.c_str());

            Imagen im(1,1); im.cargar(ifs);

            galeriaCargada.votar(im);
        }
        else if(input == "10"){
            galeriaCargada.eliminarMasVotada();
        }
        else if(input == "11"){
            ofstream ofs(archivo_galeria.c_str());
            galeriaCargada.guardar(ofs);
        }
        else{
            if(input != "x") cout << "Opcion invalida, por favor seleccione una opcion valida (1-10, x)." << endl;
        }

	}

    return 0;
}

