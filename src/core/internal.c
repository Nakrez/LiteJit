#include "internal.h"

ljit_value _ljit_new_temporary(ljit_types type)
{
    ljit_value val = NULL;

    if ((val = ljit_new_value(type)) == NULL)
        return NULL;

    val->is_tmp = 1;

    /* FIXME : Fill index member */

    return val;
}
