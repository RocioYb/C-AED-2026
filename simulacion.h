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

/* Cantidad maxima de simulaciones que guarda el historial */
#define MAX_HISTORIAL 10
/* Un intento: parametros usados + resultados obtenidos */
typedef struct {
    ParametrosD          parametros;
    ResultadosSimulacion resultados;
} RegistroSimulacion;

int calcular_simulacion(ParametrosD *p, ResultadosSimulacion *r);
void mostrar_resultados(ResultadosSimulacion *r);

/* Historial de simulaciones */
int agregar_al_historial(RegistroSimulacion historial[], int *cantidad,
                         const ParametrosD *p, const ResultadosSimulacion *r);
void mostrar_historial(const RegistroSimulacion historial[], int cantidad);


/* Modo mision : varios intentos, evaluacion y reporte final */
void jugar_mision(RegistroSimulacion historial[], int *cantidad);

#endif