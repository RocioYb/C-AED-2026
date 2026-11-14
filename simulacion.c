#include <stdio.h>
#include <math.h>
#include "simulacion.h"

int calcular_simulacion(ParametrosD *p, ResultadosSimulacion *r)
{
    double distancia_fase2;
    double velocidad_final_cuadrado;

    if (p == NULL || r == NULL) {
        return 0;
    }

    if (p->v0 < 0 || p->y0 < 0 ||
        p->a1 <= 0 || p->t1 <= 0 ||
        p->a2 <= 0 || p->h <= p->y0 ||
        p->g <= 0) {
        return 0;
    }

    /* Fase 1: velocidad y altura al desacople de los SRB */
    r->velocidad_desacople = p->v0 + p->a1 * p->t1;
    r->altura_desacople = p->y0 + p->v0 * p->t1
                         + (p->a1 * p->t1 * p->t1) / 2.0;

    if (r->altura_desacople >= p->h) {
        return 0;
    }

    /* Fase 2: velocidad al llegar a la altura de apagado */
    distancia_fase2 = p->h - r->altura_desacople;
    velocidad_final_cuadrado = r->velocidad_desacople * r->velocidad_desacople
                             + 2.0 * p->a2 * distancia_fase2;
    r->velocidad_apagado = sqrt(velocidad_final_cuadrado);

    r->tiempo_fase2 = (r->velocidad_apagado - r->velocidad_desacople) / p->a2;
    r->tiempo_total = p->t1 + r->tiempo_fase2;

    /* Altura extra si la nave sigue subiendo en caida libre */
    r->altura_maxima = p->h + (r->velocidad_apagado * r->velocidad_apagado)
                             / (2.0 * p->g);

    r->aceleracion_g = p->a1 / p->g;

    return 1;
}

void mostrar_resultados(ResultadosSimulacion *r)
{
    if (r == NULL) {
        return;
    }

    printf("\n========== RESULTADOS DE LA SIMULACION ==========\n");
    printf("Rapidez al desacople de los SRB: %.2f m/s\n", r->velocidad_desacople);
    printf("Altitud al desacople de los SRB: %.2f m\n", r->altura_desacople);
    printf("Rapidez al apagado de motores: %.2f m/s\n", r->velocidad_apagado);
    printf("Tiempo de la fase 2: %.2f s\n", r->tiempo_fase2);
    printf("Tiempo total de ascenso: %.2f s\n", r->tiempo_total);
    printf("Altitud maxima en caida libre: %.2f m\n", r->altura_maxima);
    printf("Aceleracion de la fase 1: %.2f g\n", r->aceleracion_g);
    printf("=================================================\n");
}

int agregar_al_historial(RegistroSimulacion historial[], int *cantidad,
                         const ParametrosD *p, const ResultadosSimulacion *r)
{
    if (historial == NULL || cantidad == NULL || p == NULL || r == NULL) {
        return 0;
    }

    if (*cantidad >= MAX_HISTORIAL) {
        return 0;   /* historial lleno */
    }

    historial[*cantidad].parametros = *p;
    historial[*cantidad].resultados = *r;
    (*cantidad)++;

    return 1;
}

void mostrar_historial(const RegistroSimulacion historial[], int cantidad)
{
    int i;

    if (cantidad <= 0) {
        printf("\nTodavia no hay simulaciones en el historial.\n");
        return;
    }

    printf("\n=================== HISTORIAL DE SIMULACIONES ===================\n");
    printf("Nro |   a1  |   t1  |   a2  | h apag [m] | v2 [m/s] | h max [m] |   g\n");
    printf("----+-------+-------+-------+------------+----------+-----------+------\n");

    for (i = 0; i < cantidad; i++) {
        printf(" %2d | %5.1f | %5.1f | %5.1f | %10.0f | %8.1f | %9.0f | %4.2f\n",
               i + 1,
               historial[i].parametros.a1,
               historial[i].parametros.t1,
               historial[i].parametros.a2,
               historial[i].parametros.h,
               historial[i].resultados.velocidad_apagado,
               historial[i].resultados.altura_maxima,
               historial[i].resultados.aceleracion_g);
    }

    printf("=================================================================\n");
    printf("Intentos guardados: %d de %d\n", cantidad, MAX_HISTORIAL);
}

/* Evalua un intento de la mision y devuelve su puntaje (0 a 100).
   40 pts por llegar a la altitud de apagado, 30 por no pasar el limite de g
   y 30 por cumplir el tiempo objetivo. */
static int evaluar_intento(const ParametrosD *p, const ResultadosSimulacion *r)
{
    int puntaje = 40;
    double g_max = (p->a1 > p->a2 ? p->a1 : p->a2) / p->g;   /* la mayor de las dos fases */

    printf("\n--- Evaluacion del intento ---\n");
    printf("[OK] Altitud de apagado alcanzada (+40)\n");

    if (g_max <= LIMITE_G) {
        puntaje += 30;
        printf("[OK] Aceleracion maxima %.2f g, dentro del limite de %.1f g (+30)\n", g_max, LIMITE_G);
    } else {
        printf("[X ] Aceleracion maxima %.2f g, supera el limite de %.1f g (+0)\n", g_max, LIMITE_G);
    }

    if (r->tiempo_total <= TIEMPO_OBJETIVO) {
        puntaje += 30;
        printf("[OK] Tiempo de ascenso %.2f s, dentro de los %.0f s (+30)\n", r->tiempo_total, TIEMPO_OBJETIVO);
    } else {
        printf("[X ] Tiempo de ascenso %.2f s, supera los %.0f s (+0)\n", r->tiempo_total, TIEMPO_OBJETIVO);
    }

    printf("Puntaje del intento: %d de %d\n", puntaje, PUNTAJE_MAXIMO);
    return puntaje;
}

void jugar_mision(RegistroSimulacion historial[], int *cantidad)
{
    ParametrosD p;
    ResultadosSimulacion r;
    const char *calificacion;
    int turno;
    int usados = 0;
    int puntaje;
    int mejor = 0;
    int cumplida = 0;

    printf("\n============= MODO MISION: ASCENSO DEL SLS =============\n");
    printf("Objetivo: llegar a %.0f m en %.0f s o menos.\n", H_DEFECTO, TIEMPO_OBJETIVO);
    printf("La tripulacion no tolera mas de %.1f g.\n", LIMITE_G);
    printf("Tenes %d intentos: en cada uno elegis a1, t1 y a2.\n", MAX_INTENTOS);

    for (turno = 1; turno <= MAX_INTENTOS && !cumplida; turno++) {
        printf("\n--- Intento %d de %d ---\n", turno, MAX_INTENTOS);

        if (!cargar_parametros_mision(&p)) {
            break;                          /* se cerro la entrada */
        }
        usados++;

        if (!calcular_simulacion(&p, &r)) {
            printf("\n[Fallo] No se pudo simular este intento. Intento perdido.\n");
            continue;
        }

        mostrar_resultados(&r);
        puntaje = evaluar_intento(&p, &r);

        if (!agregar_al_historial(historial, cantidad, &p, &r)) {
            printf("(Historial lleno: este intento no se guardo en el historial)\n");
        }

        if (puntaje > mejor) {
            mejor = puntaje;
        }
        if (puntaje == PUNTAJE_MAXIMO) {
            cumplida = 1;
        }
    }

    if (mejor == PUNTAJE_MAXIMO) {
        calificacion = "Excelente";
    } else if (mejor >= 70) {
        calificacion = "Aceptable";
    } else {
        calificacion = "Insuficiente";
    }

    printf("\n============ REPORTE FINAL DE DESEMPENO ============\n");
    printf("Intentos utilizados: %d de %d\n", usados, MAX_INTENTOS);
    printf("Mejor puntaje      : %d de %d\n", mejor, PUNTAJE_MAXIMO);
    printf("Calificacion       : %s\n", calificacion);
    printf("Resultado          : %s\n", cumplida ? "MISION CUMPLIDA" : "MISION NO CUMPLIDA");
    printf("====================================================\n");
}