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