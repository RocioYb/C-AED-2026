#include <stdio.h>
#include "Artemis.h"
#include "validaciones.h"
#include "simulacion.h"

#define ALTURA_MAXIMA 1000000.0   /* limite superior para la altura de apagado [m] */

void iniciar_parametros_por_defecto(ParametrosD *p) {
    p->v0 = V0_DEFECTO;
    p->y0 = Y0_DEFECTO;
    p->a1 = A1_DEFECTO;
    p->t1 = T1_DEFECTO;
    p->a2 = A2_DEFECTO;
    p->h  = H_DEFECTO;
    p->g  = G_TERRESTRE;
}

int cargar_parametros_manual(ParametrosD *p) {

    ParametrosD nuevos;
    double altura_desacople;

    printf("\n--- INGRESO DE PARAMETROS ---\n");

    if (!leer_double("Velocidad inicial (m/s)",   0.0, 1000.0,   &nuevos.v0)) return 0;

    if (!leer_double("Altura inicial (m)",        0.0, 10000.0, &nuevos.y0)) return 0;

    if (!leer_double("Aceleracion fase 1 (m/s2)", 0.1, 100.0, &nuevos.a1)) return 0;

    if (!leer_double("Tiempo de desacople (s)",   1.0, 600.0, &nuevos.t1)) return 0;

    if (!leer_double("Aceleracion fase 2 (m/s2)", 0.1, 100.0, &nuevos.a2)) return 0;

    /* La altura de apagado tiene que superar la altura ya recorrida en la fase 1 */
     altura_desacople = nuevos.y0 + nuevos.v0 * nuevos.t1
                     + (nuevos.a1 * nuevos.t1 * nuevos.t1) / 2.0;
    if (altura_desacople + 1.0 > ALTURA_MAXIMA) {
         printf("\n  [Error de Rango] Con esa a1 y ese t1 el desacople ya supera los %.0f m.\n", ALTURA_MAXIMA);
        return 0;
    }
    printf("(Altura al desacople con estos datos: %.2f m)\n", altura_desacople);
    if (!leer_double("Altura de apagado (m)", altura_desacople + 1.0, ALTURA_MAXIMA, &nuevos.h)) return 0;
    printf("Gravedad terrestre (m/s2): ");
    
    if (!leer_double("Gravedad terrestre (m/s2)", 1.0, 20.0, &nuevos.g)) return 0;

    if (!validar_parametros_fisicos(&nuevos)) {
        return 0; 
    }

    // Guardar los valores solamente si son validos
    *p = nuevos;

    printf("\nParametros cargados correctamente.\n");

    return 1;
}

void mostrar_parametros(ParametrosD *p) {

    printf("\n========== PARAMETROS ACTUALES ==========\n");

    printf("Velocidad inicial: %.2f m/s\n", p->v0);
    printf("Altura inicial: %.2f m\n", p->y0);
    printf("Aceleracion fase 1: %.2f m/s2\n", p->a1);
    printf("Tiempo de desacople: %.2f s\n", p->t1);
    printf("Aceleracion fase 2: %.2f m/s2\n", p->a2);
    printf("Altura de apagado: %.2f m\n", p->h);
    printf("Gravedad terrestre: %.2f m/s2\n", p->g);

    printf("=========================================\n");
}
