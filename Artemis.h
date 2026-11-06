//Guardar variables fijas y las que se van cargando
#ifndef ARTEMIS_H
#define ARTEMIS_H

//Constantes del escenario
#define G_TERRESTRE   9.81      // gravedad [m/s^2]
#define V0_DEFECTO    0.0       // velocidad inicial [m/s]
#define Y0_DEFECTO    0.0       // altitud inicial [m]
#define A1_DEFECTO    20.0      // aceleracion fase 1 [m/s^2]
#define T1_DEFECTO    120.0     // tiempo de desacople de los SRB [s]
#define A2_DEFECTO    12.5      // aceleracion fase 2 [m/s^2]
#define H_DEFECTO     160000.0  // altitud de apagado de motores [m]

// Datos de entrada de la mision
typedef struct {
    double a1;   // aceleracion fase 1 (motores + SRB)
    double t1;   // tiempo hasta el desacople de los SRB
    double a2;   // aceleracion fase 2 (solo el nucleo)
    double h;    // altitud a la que se apagan los motores
} Mision;

#endif