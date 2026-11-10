#include <stdio.h>
#include "Artemis.h"
#include "validaciones.h"
#include "simulacion.h"

static void mostrar_menu(void)
{
    printf("\n==========================================\n");
    printf("   SIMULADOR ARTEMIS - ASCENSO CON EL SLS\n");
    printf("==========================================\n");
    printf(" 1. Cargar valores por defecto de la mision\n");
    printf(" 2. Ingresar parametros manualmente\n");
    printf(" 3. Ejecutar simulacion\n");
    printf(" 4. Ver parametros actuales\n");
    printf(" 5. Ver resultados / reporte\n");
    printf(" 0. Salir\n");
    printf("------------------------------------------\n");
}

int main(void)
{
    int opcion;
    int vuelo = 0;
    int parametros_cargados = 0;

    ParametrosD p;
    ResultadosSimulacion r;
<<<<<<< HEAD

=======
>>>>>>> 14067f23cd3b738bcceee7eecc1828ec88487ce8
    do {
        mostrar_menu();
        printf("Elija una opcion: ");
        opcion_menu(&opcion);

        switch (opcion) {

            case 1:
                limpiar_pantalla();
                iniciar_parametros_por_defecto(&p);
                parametros_cargados = 1;
                vuelo = 0;
                printf("\nParametros predeterminados cargados.\n");
                pausar_consola();
                break;

            case 2:

                limpiar_pantalla();
                if (cargar_parametros_manual(&p)) {
                    parametros_cargados = 1;
                    vuelo = 0;
                } else {
                    printf("\n Paramentros incorrectos. No se pudieron cargar los parametros.\n");
                }

                pausar_consola();
                break;

            case 3:

                limpiar_pantalla();
                if (parametros_cargados) {
                    calcular_simulacion(&p, &r);
                    printf("\n Simulacion completada correctamente.\n");
                    vuelo = 1;
                } else {
                    printf("\n[Error] Primero debe cargar los parametros de la mision.\n");
                }
                break;
            
            case 4:
                limpiar_pantalla();
                if (parametros_cargados) {
                    mostrar_parametros(&p);
                } else {
                    printf("\nPrimero debe cargar los parametros.\n");
                }

                break;

            case 5:

                limpiar_pantalla();
                if (vuelo) {
                    mostrar_resultados(&r);
                } else {
                    printf("\n[Error] Primero debe ejecutar la simulacion.\n");
                }

                break;
            case 0:

                printf("\nFin de la simulacion.\n");

                break;

            default:

                printf("\nOpcion invalida. Ingrese un numero del 0 al 5.\n");
                pausar_consola();
        }

    } while (opcion != 0);

    return 0;
}
