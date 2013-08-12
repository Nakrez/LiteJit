#include "function.h"

ljit_function *ljit_create_function(void)
{
    ljit_function *new_function = NULL;

    if ((new_function = malloc(sizeof(ljit_function))) == NULL)
        return NULL;

    return new_function;
}

void ljit_free_function(ljit_function *fun)
{
    free(fun);
}
