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
    printf(" 6. Ver historial de simulaciones\n");
    printf(" 7. Modo mision\n");
    printf(" 0. Salir\n");
    printf("------------------------------------------\n");
}

static void menu_mision(RegistroSimulacion historial[], int *cantidad)
{
    int opcion;

    do {
        printf("\n==========================================\n");
        printf("               MODO MISION\n");
        printf("==========================================\n");
        printf(" 1. Reglas\n");
        printf(" 2. Jugar\n");
        printf(" 3. Ver resultados\n");
        printf(" 0. Volver al menu principal\n");
        printf("------------------------------------------\n");
        printf("Elija una opcion: ");
        opcion_menu(&opcion);

        switch (opcion) {
            case 1:
                limpiar_pantalla();
                mostrar_reglas();
                pausar_consola();
                break;
            case 2:
                limpiar_pantalla();
                jugar_mision(historial, cantidad);
                pausar_consola();
                break;
            case 3:
                limpiar_pantalla();
                mostrar_historial(historial, *cantidad, ORIGEN_MISION);
                pausar_consola();
                break;
            case 0:
                break;
            default:
                printf("\nOpcion invalida. Ingrese un numero del 0 al 3.\n");
                pausar_consola();
        }
    } while (opcion != 0);
}

int main(void)
{
    int opcion;
    int vuelo = 0;
    int parametros_cargados = 0;

    ParametrosD p;
    ResultadosSimulacion r;
    RegistroSimulacion historial[MAX_HISTORIAL];
    int cantidad_historial = 0;
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
    if (!parametros_cargados) {
        printf("\n[Error] Primero debe cargar los parametros de la mision.\n");
    } else if (calcular_simulacion(&p, &r)) {
        printf("\n Simulacion completada correctamente.\n");
        vuelo = 1;
        if (agregar_al_historial(historial, &cantidad_historial, &p, &r, ORIGEN_MANUAL, 0, 0)) {
            printf(" Intento Nro %d guardado en el historial.\n", cantidad_historial);
        } else {
            printf(" [Aviso] Historial lleno (%d intentos): este intento no se guardo.\n", MAX_HISTORIAL);
        }
    } else {
        vuelo = 0;
        printf("\n[Error] No se pudo simular: la altura de apagado debe superar la altura de desacople.\n");
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
            case 6:
              limpiar_pantalla();
                mostrar_historial(historial, cantidad_historial, ORIGEN_TODOS);
                break;
            case 7:
                limpiar_pantalla();
                menu_mision(historial, &cantidad_historial);
                break;
            case 0:
                printf("\nFin de la simulacion.\n");
                break;
            default:
                printf("\nOpcion invalida. Ingrese un numero del 0 al 7.\n");
                pausar_consola();
        }

    } while (opcion != 0);

    return 0;
}
