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
#define MAX_HISTORIAL 15

/* De donde viene cada simulacion guardada en el historial */
#define ORIGEN_MANUAL 0
#define ORIGEN_MISION 1
#define ORIGEN_TODOS  2  

/* Un intento: parametros usados + resultados obtenidos + origen */
typedef struct {
    ParametrosD          parametros;
    ResultadosSimulacion resultados;
     int                  nro_mision;  /* numero de mision (0 si es manual) */
     int                  puntaje;     /* puntaje del intento (0 si es manual) */
     int                  origen;      /* ORIGEN_MANUAL u ORIGEN_MISION */
} RegistroSimulacion;

int calcular_simulacion(ParametrosD *p, ResultadosSimulacion *r);
void mostrar_resultados(ResultadosSimulacion *r);

/* Historial de simulaciones */
int agregar_al_historial(RegistroSimulacion historial[], int *cantidad,
const ParametrosD *p, const ResultadosSimulacion *r,
int origen, int nro_mision, int puntaje);
void mostrar_historial(const RegistroSimulacion historial[], int cantidad, int origen);


/* Modo mision : varios intentos, evaluacion y reporte final */
void jugar_mision(RegistroSimulacion historial[], int *cantidad);

/* Pantalla con las reglas del modo mision */
void mostrar_reglas(void);

#endif