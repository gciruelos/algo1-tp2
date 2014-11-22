CC=g++
CFLAGS= -O2 -Wall

tp2: main.o pixel.o imagen.o galeria_imagenes.o
	$(CC) $(CFLAGS) -Wextra -o tp2 main.o pixel.o imagen.o galeria_imagenes.o

main.o : src/main.cpp src/pixel.h src/imagen.h src/galeria_imagenes.h
	$(CC) $(CFLAGS) -c src/main.cpp

pixel.o : src/pixel.cpp src/pixel.h
	$(CC) $(CFLAGS) -c src/pixel.cpp

imagen.o : src/imagen.cpp src/imagen.h
	$(CC) $(CFLAGS) -c src/imagen.cpp

galeria_imagenes.o : src/galeria_imagenes.cpp src/galeria_imagenes.h
	$(CC) $(CFLAGS) -c src/galeria_imagenes.cpp

clean :
	rm main.o pixel.o imagen.o galeria_imagenes.o tp2
