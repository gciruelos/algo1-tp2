tp2: main.o pixel.o imagen.o galeria_imagenes.o
	g++ -O2 -Wall -Wextra -o tp2 main.o pixel.o imagen.o galeria_imagenes.o

main.o : src/main.cpp src/pixel.h src/imagen.h src/galeria_imagenes.h
	g++ -O2 -Wall -c src/main.cpp

pixel.o : src/pixel.cpp src/pixel.h
	g++ -O2 -Wall -c src/pixel.cpp

imagen.o : src/imagen.cpp src/imagen.h
	g++ -O2 -Wall -c src/imagen.cpp

galeria_imagenes.o : src/galeria_imagenes.cpp src/galeria_imagenes.h
	g++ -O2 -Wall -c src/galeria_imagenes.cpp

clean :
	rm main.o pixel.o imagen.o galeria_imagenes.o tp2
