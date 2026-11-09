#ifndef SIMULACION_H
#define SIMULACION_H

#include "Artemis.h"

/* Resultados calculados para el ascenso del SLS */
typedef struct {
    double velocidad_desacople;
    double altura_desacople;
    double velocidad_apagado;
    double tiempo_fase2;
    double tiempo_total;
    double altura_maxima;
    double aceleracion_g;
} ResultadosSimulacion;

int calcular_simulacion(ParametrosD *p, ResultadosSimulacion *r);
void mostrar_resultados(ResultadosSimulacion *r);

#endif