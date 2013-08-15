#include "internal.h"

ljit_value _ljit_new_temporary(ljit_function *fun, ljit_types type)
{
    ljit_value val = NULL;

    if ((val = ljit_new_value(type)) == NULL)
        return NULL;

    val->is_tmp = 1;
    val->index = fun->uniq_index++;

    return val;
}
