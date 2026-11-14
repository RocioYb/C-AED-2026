# Makefile - Simulador Artemis (Grupo 11, Comision B)
#
# Uso:
#   make          compila el proyecto y genera el ejecutable "artemis"
#   make clean    borra el ejecutable
#
# En Windows con MinGW/MSYS2 puede ser necesario usar "mingw32-make".

CC     = gcc
CFLAGS = -Wall -Wextra
SRC    = main.c Artemis.c simulacion.c validaciones.c
HDR    = Artemis.h simulacion.h validaciones.h
TARGET = artemis

$(TARGET): $(SRC) $(HDR)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) -lm

clean:
	rm -f $(TARGET) $(TARGET).exe

.PHONY: clean
