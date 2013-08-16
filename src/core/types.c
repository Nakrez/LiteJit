#include <ljit/types.h>
#include "internal.h"

ljit_value ljit_new_value(ljit_types type)
{
    ljit_value val = NULL;

    if ((val = malloc(sizeof(struct ljit_value_s))) == NULL)
        return NULL;

    val->type = type;
    val->is_cst = 0;
    val->is_tmp = 0;
    val->index = 0;
    val->data = NULL;
    val->count = 1;

    return val;
}

void ljit_free_value(ljit_value value)
{
    if (!value)
        return;

    --value->count;

    if (value->count > 0)
    {
        if (value->type == LJIT_LABEL)
            ljit_free_label(value->data);
        return;
    }

    if (value->type != LJIT_LABEL)
        free(value->data);
    else
        ljit_free_label(value->data);

    free(value);
}

ljit_value ljit_new_uchar_cst(ljit_uchar value)
{
    ljit_value cst = ljit_new_value(LJIT_UCHAR);
    ljit_uchar *val = NULL;

    if (!cst)
        return NULL;

    if ((val = malloc(sizeof(ljit_uchar))) == NULL)
    {
        ljit_free_value(cst);
        return NULL;
    }

    *val = value;
    cst->data = val;
    cst->is_cst = 1;

    /* Every constant is considered as non assigned when created */
    cst->count = 0;

    return cst;
}
