#include <ljit/function.h>
#include "regalloc.h"
#include "internal.h"

static int _ljit_create_first_block(ljit_function *fun)
{
    ljit_label *entry_lbl = NULL;

    if ((fun->start_blk = ljit_new_block()) == NULL)
        return -1;

    if ((entry_lbl = ljit_new_label(fun)) == NULL)
        return -1;

    fun->current_blk = fun->start_blk;
    fun->last_blk = fun->start_blk;

    if (ljit_bind_label(fun, entry_lbl))
    {
        ljit_free_label(entry_lbl);
        return -1;
    }

    return 0;
}

ljit_function *ljit_new_function(ljit_instance *instance)
{
    ljit_function *new_function = NULL;

    if ((new_function = malloc(sizeof(ljit_function))) == NULL)
        return NULL;

    new_function->signature = NULL;
    new_function->instance = instance;
    new_function->uniq_index = 0;
    new_function->lbl_index = 0;

    /*
    Create the start block of the function.
    This block is also the current one
    */
    if (_ljit_create_first_block(new_function))
    {
        ljit_free_function(new_function);
        return NULL;
    }

    if (!new_function->start_blk)
    {
        ljit_free_function(new_function);
        return NULL;
    }

    return new_function;
}

static void ljit_free_signature(ljit_signature *sig)
{
    if (!sig)
        return;

    free(sig->params_type);
    free(sig);
}

void ljit_free_function(ljit_function *fun)
{
    if (!fun)
        return;

    /* Free all block contained by the function */
    ljit_block *b = fun->start_blk;
    ljit_block *tmp = NULL;

    while (b)
    {
        tmp = b->next;
        ljit_free_block(b);
        b = tmp;
    }

    ljit_free_signature(fun->signature);
    free(fun);
}

/** TODO : Check if one of the parameter as type VOID **/
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

        memcpy(sig->params_type, param_types,
               sizeof(ljit_types) * param_number);
    }
    else
        sig->params_type = NULL;

    sig->ret_type = ret_type;

    fun->signature = sig;

    return 0;
}

int ljit_function_compile(ljit_function *fun)
{
    if (!fun->instance || fun->instance->target_arch == LJIT_ARCH_NONE)
        return -1;

    /*
    First compute register allocation according to the
    platform specifications
    */
    if (_ljit_regalloc(fun))
        return -1;

    switch (fun->instance->target_arch)
    {
        case LJIT_ARCH_NONE:
            return -1;
        case LJIT_ARCH_X86:
            return x86_compile(fun);
        case LJIT_ARCH_X64:
            return 0;
    }
}
