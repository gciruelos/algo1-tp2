tp2: main.o pixel.o imagen.o galeria_imagenes.o
	g++ -O2 -Wall -Wextra -o tp2 main.o pixel.o imagen.o galeria_imagenes.o

main.o : main.cpp pixel.h imagen.h galeria_imagenes.h
	g++ -O2 -c main.cpp

pixel.o : pixel.cpp pixel.h
	g++ -O2 -c pixel.cpp

imagen.o : imagen.cpp imagen.h
	g++ -O2 -c imagen.cpp

galeria_imagenes.o : galeria_imagenes.cpp galeria_imagenes.h
	g++ -O2 -c galeria_imagenes.cpp

clean :
	rm main.o pixel.o imagen.o galeria_imagenes.o tp2
