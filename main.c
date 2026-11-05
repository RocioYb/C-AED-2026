#include <stdio.h>

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
                printf("\n[Pendiente] Cargar valores por defecto.\n");
                break;
            case 2:
                printf("\n[Pendiente] Ingreso manual de parametros.\n");
                break;
            case 3:
                printf("\n[Pendiente] Simulacion del ascenso.\n");
                break;
            case 4:
                printf("\n[Pendiente] Ver parametros actuales.\n");
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
