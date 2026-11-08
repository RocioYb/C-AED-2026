#include <stdio.h>
#include "Artemis.h"

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
    int leidos;
    int c;
    int parametros_cargados = 0;

    ParametrosD parametros;

    do {
        mostrar_menu();
        printf("Elija una opcion: ");

        leidos = scanf("%d", &opcion);
        if (leidos == EOF) {
            opcion = 0;
        } else {
            while ((c = getchar()) != '\n' && c != EOF) { }  /* limpiar */
            if (leidos != 1)
                opcion = -1;
        }

        switch (opcion) {

            case 1:

                iniciar_parametros_por_defecto(&parametros);

                parametros_cargados = 1;

                printf("\nParametros predeterminados cargados.\n");

                break;

            case 2:

                if (cargar_parametros_manual(&parametros)) {
                    parametros_cargados = 1;
                } else {
                    printf("\nNo se pudieron cargar los parametros.\n");
                }

                while ((c = getchar()) != '\n' && c != EOF) { }

                break;

            case 3:

                printf("\n[Pendiente] Simulacion del ascenso.\n");

                break;

            case 4:

                if (parametros_cargados) {
                    mostrar_parametros(&parametros);
                } else {
                    printf("\nPrimero debe cargar los parametros.\n");
                }

                break;

            case 5:

                printf("\n[Pendiente] Reporte de resultados.\n");

                break;

            case 0:

                printf("\nFin de la simulacion.\n");

                break;

            default:

                printf("\nOpcion invalida. Ingrese un numero del 0 al 5.\n");
        }

    } while (opcion != 0);

    return 0;
}