#include "types.h"

ljit_value ljit_new_value(ljit_types type)
{
    ljit_value val = NULL;

    if ((val = malloc(sizeof(ljit_value))) == NULL)
        return NULL;

    val->type = type;
    val->is_cst = 0;
    val->data = NULL;

    return val;
}

ljit_value ljit_new_uchar_cst(ljit_uchar value)
{
    ljit_value cst = ljit_new_value(LJIT_UCHAR);
    ljit_uchar *val = NULL;

    if (!cst)
        return NULL;

    if ((val = malloc(sizeof(ljit_uchar))) == NULL)
    {
        free(cst);
        return NULL;
    }

    *val = value;
    cst->data = val;
    cst->is_cst = 1;

    return cst;
}