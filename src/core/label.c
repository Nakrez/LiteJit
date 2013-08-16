#include "internal.h"

ljit_label *ljit_new_label(ljit_function *fun)
{
    ljit_label *lbl = NULL;

    if ((lbl = malloc(sizeof(ljit_label))) == NULL)
        return NULL;

    lbl->instr = NULL;
    lbl->next_lbl = NULL;
    lbl->index = fun->lbl_index++;

    /* Label are considered as non assigned when created */
    lbl->count = 0;

    return lbl;
}

void ljit_free_label(ljit_label *lbl)
{
    if (!lbl)
        return;

    --lbl->count;

    if (lbl->count > 0)
        return;

    free(lbl);
}
