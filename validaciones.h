#ifndef VALIDACIONES_H
#define VALIDACIONES_H
#include "Artemis.h"

int opcion_menu(int *opcion);
int leer_double_seguro(const char *mensaje, double *valor);
int validar_parametros_fisicos(const ParametrosD *p);
int leer_double(const char *mensaje, double min, double max, double *destino);
void pausar_consola(void);
void limpiar_pantalla(void);

#endif 