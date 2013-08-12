#include "function.h"

ljit_function *ljit_create_function(void)
{
    ljit_function *new_function = NULL;

    if ((new_function = malloc(sizeof(ljit_function))) == NULL)
        return NULL;

    new_function->signature = NULL;

    return new_function;
}

void ljit_free_function(ljit_function *fun)
{
    free(fun);
}

int ljit_new_signature(ljit_function *fun,
                       ljit_types ret_type,
                       int param_number,
                       ljit_types *param_types)
{
    ljit_signature *sig = NULL;

    if (!fun)
        return -2;

    if ((sig = malloc(sizeof(ljit_signature))) == NULL)
        return -1;

    if (param_number)
    {
        if ((sig->params_type = malloc(sizeof(ljit_types) * param_number)) == NULL)
        {
            free(sig);
            return -1;
        }

        memcpy(sig->params_type, param_types, sizeof(param_types));
    }
    else
        sig->params_type = NULL;

    sig->ret_type = ret_type;

    fun->signature = sig;
}