#include <ljit/core/function.h>

#include <sys/mman.h>
#include <alloca.h>

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
    new_function->code = NULL;

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

    if (fun->code)
        munmap(fun->code, 4096);

    free(fun);
}

ffi_type *ljit_type_to_ffi(ljit_types t)
{
    switch (t)
    {
        case LJIT_INT:
            return &ffi_type_sint;
        default:
            return 0;
    }
}

ffi_status ljit_create_ffi(ffi_cif *cif, int param_number, ljit_types ljit_ret,
                           ljit_types *ljit_param)
{
    ffi_type *ffi_ret = NULL;
    ffi_type **ffi_params = malloc(sizeof(ffi_type*) * param_number);

    ffi_ret = ljit_type_to_ffi(ljit_ret);

    for (int i = 0; i < param_number; ++i)
        ffi_params[i] = ljit_type_to_ffi(ljit_param[i]);

    return ffi_prep_cif(cif, FFI_DEFAULT_ABI, param_number, ffi_ret, ffi_params);
}

/** TODO : Check if one of the parameter as type VOID **/
int ljit_new_signature(ljit_function *fun,
                       ljit_types ret_type,
                       int param_number,
                       ljit_types *param_types)
{
    ljit_signature *sig = NULL;
    ffi_status status;

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

    sig->param_num = param_number;
    sig->ret_type = ret_type;

    status = ljit_create_ffi(&sig->cif, param_number, ret_type, param_types);

    if (status != FFI_OK)
    {
        ljit_free_signature(sig);
        return -1;
    }

    fun->signature = sig;

    return 0;
}

unsigned int ljit_signature_size(ljit_function *fun)
{
    unsigned int sig_size = 0;

    for (unsigned int i = 0; i < fun->signature->param_num; ++i)
        sig_size += ljit_type_get_size(fun->signature->params_type[i]);

    return sig_size;
}

int ljit_parameter_offset(ljit_function *fun, unsigned int param)
{
    int offset = 0;

    if (fun->signature->param_num >= param)
        return -1;

    for (int i = fun->signature->param_num - 1; i >= 0; --i)
    {
        if (i < (int)param)
            break;

        offset += ljit_type_get_size(fun->signature->params_type[i]);
    }

    return offset;
}
