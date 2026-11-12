#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#define TAM_LINEA 100
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
/* Pide un numero decimal y repite la pregunta hasta que sea valido y este
   entre min y max, devuelve 1 si se cargo el dato y 0 si se cerro la entrada. */
int leer_double(const char *mensaje, double min, double max, double *destino) {
    char linea[TAM_LINEA];
    char *fin;
    char *c;
    double valor;
    int ch;

    while (1) {
        printf("%s [%.2f a %.2f]: ", mensaje, min, max);

        if (fgets(linea, TAM_LINEA, stdin) == NULL) {
            return 0;   /* se cerro la entrada */
        }

        if (strchr(linea, '\n') == NULL && !feof(stdin)) {  /* linea demasiado larga */
            while ((ch = getchar()) != '\n' && ch != EOF) { }
            printf("  [Error] Entrada demasiado larga. Intente de nuevo.\n");
            continue;
        }

        /* aceptar coma decimal (12,5) ademas de punto (12.5) */
        for (c = linea; *c != '\0'; c++) {
            if (*c == ',') {
                *c = '.';
            }
        }

        errno = 0;
        valor = strtod(linea, &fin);

        if (fin == linea) {
            printf("  [Error] Debe ingresar un numero (sin letras).\n");
            continue;
        }

        while (isspace((unsigned char)*fin)) {
            fin++;
        }
        if (*fin != '\0') {
            printf("  [Error] Hay caracteres no validos despues del numero.\n");
            continue;
        }

        /* la forma !(a && b) tambien rechaza nan e inf */
        if (errno == ERANGE || !(valor >= min && valor <= max)) {
            printf("  [Error] Valor fuera de rango. Debe estar entre %.2f y %.2f.\n", min, max);
            continue;
        }

        *destino = valor;
        return 1;
    }
}