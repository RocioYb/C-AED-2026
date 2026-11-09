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