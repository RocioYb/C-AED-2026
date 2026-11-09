#include <stdio.h>
#include "validaciones.h"

void limpiar_pantalla(void) {
  #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

void pausar_consola(void) {
    printf("\nPresione ENTER para continuar...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


int opcion_menu(int *opcion) {
    int leidos;
    int c;

    leidos = scanf("%d", opcion);
    if (leidos == EOF) {
        *opcion = 0;
        return 0; 
    } else {
        
        while ((c = getchar()) != '\n' && c != EOF) { }
        
        if (leidos != 1) {
            *opcion = -1; 
            return 0;
        }
    }
    return 1; 
}

int validar_parametros_fisicos(const ParametrosD *p) {
    if (p->v0 < 0 || p->y0 < 0 ||
        p->a1 <= 0 || p->t1 <= 0 ||
        p->a2 <= 0 || p->h <= p->y0 ||
        p->g <= 0) {
        
        printf("\n  [Error de Rango] Se ingresaron valores fisicos invalidos o incoherentes.\n");
        return 0; 
    }
    return 1;
}
