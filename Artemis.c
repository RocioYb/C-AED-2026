#include <stdio.h>
#include "Artemis.h"
#include "validaciones.h"

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
    int c;

    printf("\n--- INGRESO DE PARAMETROS ---\n");

    // 1. Velocidad inicial
    printf("Velocidad inicial (m/s): ");
    if (scanf("%lf", &nuevos.v0) != 1) {
        while ((c = getchar()) != '\n' && c != EOF);
        printf("\n[Error] Entrada invalida.\n");
        return 0;
    }
    if (nuevos.v0 < 0) {
        while ((c = getchar()) != '\n' && c != EOF);
        printf("\n[Error] La velocidad inicial no puede ser negativa.\n");
        return 0;
    }

    // 2. Altura inicial
    printf("Altura inicial (m): ");
    if (scanf("%lf", &nuevos.y0) != 1) {
        while ((c = getchar()) != '\n' && c != EOF);
        printf("\n[Error] Entrada invalida.\n");
        return 0;
    }
    if (nuevos.y0 < 0) {
        while ((c = getchar()) != '\n' && c != EOF);
        printf("\n[Error] La altura inicial no puede ser negativa.\n");
        return 0;
    }

    // 3. Aceleracion fase 1
    printf("Aceleracion fase 1 (m/s2): ");
    if (scanf("%lf", &nuevos.a1) != 1) {
        while ((c = getchar()) != '\n' && c != EOF);
        printf("\n[Error] Entrada invalida.\n");
        return 0;
    }
    if (nuevos.a1 <= 0) {
        while ((c = getchar()) != '\n' && c != EOF);
        printf("\n[Error] La aceleracion de la fase 1 debe ser mayor a 0.\n");
        return 0;
    }

    // 4. Tiempo de desacople
    printf("Tiempo de desacople (s): ");
    if (scanf("%lf", &nuevos.t1) != 1) {
        while ((c = getchar()) != '\n' && c != EOF);
        printf("\n[Error] Entrada invalida.\n");
        return 0;
    }
    if (nuevos.t1 <= 0) {
        while ((c = getchar()) != '\n' && c != EOF);
        printf("\n[Error] El tiempo de desacople debe ser mayor a 0.\n");
        return 0;
    }

    // 5. Aceleracion fase 2
    printf("Aceleracion fase 2 (m/s2): ");
    if (scanf("%lf", &nuevos.a2) != 1) {
        while ((c = getchar()) != '\n' && c != EOF);
        printf("\n[Error] Entrada invalida.\n");
        return 0;
    }
    if (nuevos.a2 <= 0) {
        while ((c = getchar()) != '\n' && c != EOF);
        printf("\n[Error] La aceleracion de la fase 2 debe ser mayor a 0.\n");
        return 0;
    }

    // Calculamos la altura de desacople automáticamente
    double altura_desacople = nuevos.y0 + (nuevos.v0 * nuevos.t1) + (0.5 * nuevos.a1 * nuevos.t1 * nuevos.t1);

    // 6. Altura de apagado con reintento inteligente
    int h_valido = 0;
    do {
        printf("\n[Info] Altura estimada de desacople: %.2f m\n", altura_desacople);
        printf("Altura de apagado (m): ");
        
        if (scanf("%lf", &nuevos.h) != 1) {
            while ((c = getchar()) != '\n' && c != EOF);
            printf("[Error] Entrada invalida. Intente de nuevo.\n");
            continue;
        }

        if (nuevos.h <= altura_desacople) {
            while ((c = getchar()) != '\n' && c != EOF);
            printf("[Error] Demasiado baja. Debe ser mayor a la altura de desacople (%.2f m).\n", altura_desacople);
        } else {
            h_valido = 1; // ¡Valor correcto, salimos del bucle!
        }
    } while (!h_valido);

    // 7. Gravedad terrestre
    printf("Gravedad terrestre (m/s2): ");
    if (scanf("%lf", &nuevos.g) != 1) {
        while ((c = getchar()) != '\n' && c != EOF);
        printf("\n[Error] Entrada invalida.\n");
        return 0;
    }
    if (nuevos.g <= 0) {
        while ((c = getchar()) != '\n' && c != EOF);
        printf("\n[Error] La gravedad debe ser mayor a 0.\n");
        return 0;
    }

    // Limpiar el búfer al finalizar con éxito todo el proceso
    while ((c = getchar()) != '\n' && c != EOF);

    // Guardar los valores solamente si pasaron todas las pruebas paso a paso
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
