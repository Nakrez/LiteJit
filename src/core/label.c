#include "internal.h"

ljit_label *ljit_new_label(ljit_function *fun)
{
    ljit_label *lbl = NULL;

    if ((lbl = malloc(sizeof(ljit_label))) == NULL)
        return NULL;

    lbl->instr = NULL;
    lbl->next_lbl = NULL;
    lbl->index = fun->lbl_index++;

    return lbl;
}
