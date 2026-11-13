#include <stdio.h>
#include <stdlib.h>
#include "validaciones.h"
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <math.h>

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


int leer_double_seguro(const char *mensaje, double *valor) {

    char entrada[100];
    char *fin;
    double numero;

    if (valor == NULL) {
        return 0;
    }

    while (1) {

        printf("%s", mensaje);

        if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
            return 0;
        }

        // Detectar entradas demasiado largas
        if (strchr(entrada, '\n') == NULL && !feof(stdin)) {

            int c;
            while ((c = getchar()) != '\n' && c != EOF);

            printf("[Error] Entrada demasiado larga.\n");
            continue;
        }

        errno = 0;

        // Convertir texto a numero
        numero = strtod(entrada, &fin);

        if (fin == entrada) {
            printf("[Error] Debe ingresar un numero.\n");
            continue;
        }

        // Ignorar espacios al final
        while (isspace((unsigned char)*fin)) {
            fin++;
        }

        // Rechazar caracteres adicionales
        if (*fin != '\0') {
            printf("[Error] Entrada numerica invalida.\n");
            continue;
        }

        // Rechazar NaN, infinito y desbordamientos
        if (errno == ERANGE || !isfinite(numero)) {
            printf("[Error] El numero debe ser finito y valido.\n");
            continue;
        }

        *valor = numero;
        return 1;
    }
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