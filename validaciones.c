#include <stdio.h>
#include <stdlib.h>
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
    // Calculamos la altura a la que ocurre el desacople para verificar 'h' correctamente
    double altura_desacople = p->y0 + p->v0 * p->t1 + (p->a1 * p->t1 * p->t1) / 2.0;

    if (p->v0 < 0) {
        printf("\n[Error] La velocidad inicial no puede ser negativa.\n");
        return 0;
    }
    if (p->y0 < 0) {
        printf("\n[Error] La altura inicial no puede ser negativa.\n");
        return 0;
    }
    if (p->a1 <= 0) {
        printf("\n[Error] La aceleracion de la fase 1 debe ser mayor a 0.\n");
        return 0;
    }
    if (p->t1 <= 0) {
        printf("\n[Error] El tiempo de desacople debe ser mayor a 0.\n");
        return 0;
    }
    if (p->a2 <= 0) {
        printf("\n[Error] La aceleracion de la fase 2 debe ser mayor a 0.\n");
        return 0;
    }
    if (p->h <= altura_desacople) {
        printf("\n[Error] La altura de apagado debe ser mayor que la altura de desacople (%.2f m).\n", altura_desacople);
        return 0;
    }
    if (p->g <= 0) {
        printf("\n[Error] La gravedad debe ser mayor a 0.\n");
        return 0;
    }
    return 1;
}