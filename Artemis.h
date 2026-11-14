//Guardar variables fijas y las que se van cargando
#ifndef ARTEMIS_H
#define ARTEMIS_H

//Constantes del escenario
#define G_TERRESTRE   9.80      // gravedad [m/s^2]
#define V0_DEFECTO    0.0       // velocidad inicial [m/s]
#define Y0_DEFECTO    0.0       // altitud inicial [m]
#define A1_DEFECTO    20.0      // aceleracion fase 1 [m/s^2]
#define T1_DEFECTO    120.0     // tiempo de desacople de los SRB [s]
#define A2_DEFECTO    12.5      // aceleracion fase 2 [m/s^2]
#define H_DEFECTO     160000.0  // altitud de apagado de motores [m]

// Reglas del modo mision
#define MAX_INTENTOS     3       // turnos disponibles para cumplir la mision
#define LIMITE_G         3.0     // maxima aceleracion tolerable por la tripulacion [g]
#define TIEMPO_OBJETIVO  120.0   // tiempo maximo de ascenso para cumplir la mision [s]
#define PUNTAJE_MAXIMO   100     // puntaje de un intento que cumple todo

// Registro para almacenar los parámetros de entrada
typedef struct {
    double v0;       // Velocidad inicial (m/s)
    double y0;       // Altura inicial en plataforma (m)
    double a1;       // Aceleración en Fase 1  (m/s^2)
    double t1;       // Tiempo de desacople (s)
    double a2;       // Aceleración en Fase 2 (m/s^2)
    double h; // Altura de apagado de motores (m)
    double g;        // gravedad (m/s^2)
} ParametrosD;

//  Prototipos de funciones públicas del simulador
void iniciar_parametros_por_defecto(ParametrosD *p);

int cargar_parametros_manual(ParametrosD *p);

void mostrar_parametros(ParametrosD *p);

int cargar_parametros_mision(ParametrosD *p);

#endif
