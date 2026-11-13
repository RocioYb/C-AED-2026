#include <stdio.h>
#include "Artemis.h"
#include "validaciones.h"
#include <math.h>

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

    if (p == NULL) {
        return 0;
    }

    printf("\n--- INGRESO DE PARAMETROS ---\n");

    // 1. Velocidad inicial
    if (!leer_double_seguro("Velocidad inicial (m/s): ", &nuevos.v0))
        return 0;

    if (nuevos.v0 < 0) {
        printf("\n[Error] La velocidad inicial no puede ser negativa.\n");
        return 0;
    }

    // 2. Altura inicial
    if (!leer_double_seguro("Altura inicial (m): ", &nuevos.y0))
        return 0;

    if (nuevos.y0 < 0) {
        printf("\n[Error] La altura inicial no puede ser negativa.\n");
        return 0;
    }

    // 3. Aceleracion fase 1
    if (!leer_double_seguro("Aceleracion fase 1 (m/s2): ", &nuevos.a1))
        return 0;

    if (nuevos.a1 <= 0) {
        printf("\n[Error] La aceleracion de la fase 1 debe ser mayor a 0.\n");
        return 0;
    }

    // 4. Tiempo de desacople
    if (!leer_double_seguro("Tiempo de desacople (s): ", &nuevos.t1))
        return 0;

    if (nuevos.t1 <= 0) {
        printf("\n[Error] El tiempo de desacople debe ser mayor a 0.\n");
        return 0;
    }

    // 5. Aceleracion fase 2
    if (!leer_double_seguro("Aceleracion fase 2 (m/s2): ", &nuevos.a2))
        return 0;

    if (nuevos.a2 <= 0) {
        printf("\n[Error] La aceleracion de la fase 2 debe ser mayor a 0.\n");
        return 0;
    }

    // Calcular altura de desacople
    double altura_desacople =
        nuevos.y0 + nuevos.v0 * nuevos.t1 +
        (nuevos.a1 * nuevos.t1 * nuevos.t1) / 2.0;

    // 6. Altura de apagado
    int h_valido = 0;

    do {
        printf("\n[Info] Altura estimada de desacople: %.2f m\n",
               altura_desacople);

        if (!leer_double_seguro("Altura de apagado (m): ", &nuevos.h))
            return 0;

        if (nuevos.h <= altura_desacople) {
            printf("[Error] La altura debe ser mayor a %.2f m.\n",
                   altura_desacople);
        } else {
            h_valido = 1;
        }

    } while (!h_valido);

    // 7. Gravedad terrestre
    if (!leer_double_seguro("Gravedad terrestre (m/s2): ", &nuevos.g))
        return 0;

    if (nuevos.g <= 0) {
        printf("\n[Error] La gravedad debe ser mayor a 0.\n");
        return 0;
    }

    // Conservar la validacion fisica general existente
    if (!validar_parametros_fisicos(&nuevos)) {
        return 0;
    }

    // Guardar los parametros
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
