tp2: main.o pixel.o imagen.o galeria_imagenes.o
	g++ -Wall -Wextra -o tp2 main.o pixel.o imagen.o galeria_imagenes.o

main.o : main.cpp pixel.h imagen.h galeria_imagenes.h
	g++ -c main.cpp

pixel.o : pixel.cpp pixel.h
	g++ -c pixel.cpp

imagen.o : imagen.cpp imagen.h
	g++ -c imagen.cpp

galeria_imagenes.o : galeria_imagenes.cpp galeria_imagenes.h
	g++ -c galeria_imagenes.cpp

clean :
	rm main.o pixel.o imagen.o galeria_imagenes.o tp2
