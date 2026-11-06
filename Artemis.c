#include <stdio.h>
#include "Artemis.h"

void iniciar_parametros_por_defecto(ParametrosD *p) {
    p->v0 = V0_DEFECTO;
    p->y0 = Y0_DEFECTO;
    p->a1 = A1_DEFECTO;
    p->t1 = T1_DEFECTO;
    p->a2 = A2_DEFECTO;
    p->h  = H_DEFECTO;
    p->g  = G_TERRESTRE;
}
