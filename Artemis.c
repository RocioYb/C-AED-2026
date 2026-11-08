#include <stdio.h>
#include "Artemis.h"

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

    printf("\n--- INGRESO DE PARAMETROS ---\n");

    printf("Velocidad inicial (m/s): ");
    if (scanf("%lf", &nuevos.v0) != 1) return 0;

    printf("Altura inicial (m): ");
    if (scanf("%lf", &nuevos.y0) != 1) return 0;

    printf("Aceleracion fase 1 (m/s2): ");
    if (scanf("%lf", &nuevos.a1) != 1) return 0;

    printf("Tiempo de desacople (s): ");
    if (scanf("%lf", &nuevos.t1) != 1) return 0;

    printf("Aceleracion fase 2 (m/s2): ");
    if (scanf("%lf", &nuevos.a2) != 1) return 0;

    printf("Altura de apagado (m): ");
    if (scanf("%lf", &nuevos.h) != 1) return 0;

    printf("Gravedad terrestre (m/s2): ");
    if (scanf("%lf", &nuevos.g) != 1) return 0;

    // Validaciones basicas
    if (nuevos.v0 < 0 || nuevos.y0 < 0 ||
        nuevos.a1 <= 0 || nuevos.t1 <= 0 ||
        nuevos.a2 <= 0 || nuevos.h <= nuevos.y0 ||
        nuevos.g <= 0) {

        printf("\nError: se ingresaron valores fuera de rango.\n");
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