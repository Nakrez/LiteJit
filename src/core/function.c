#include <ljit/function.h>
#include "internal.h"

ljit_function *ljit_new_function(ljit_instance *instance)
{
    ljit_function *new_function = NULL;

    if ((new_function = malloc(sizeof(ljit_function))) == NULL)
        return NULL;

    new_function->signature = NULL;
    new_function->instance = instance;
    new_function->tmp_table_size = LJIT_TEMPORARY_TABLE_INIT_SIZE;

    /* Create the temporary table */
    if ((new_function->temporary_table = malloc(LJIT_TEMPORARY_TABLE_INIT_SIZE
                                                * sizeof(ljit_value))) == NULL)
    {
        free(new_function);
        return NULL;
    }

    memset(new_function->temporary_table, 0,
           LJIT_TEMPORARY_TABLE_INIT_SIZE * sizeof(ljit_value));

    /*
    Create the start block of the function.
    This block is also the current one
    */
    new_function->start_blk = ljit_new_block();
    new_function->current_blk = new_function->start_blk;
    new_function->uniq_index = 0;

    new_function->lbl_table_size = LJIT_TEMPORARY_TABLE_INIT_SIZE;

    if ((new_function->lbl_table = malloc(LJIT_TEMPORARY_TABLE_INIT_SIZE
                                          * sizeof(ljit_label*))) == NULL)
    {
        free(new_function->temporary_table);
        free(new_function);
        return NULL;
    }

    memset(new_function->lbl_table, 0,
           LJIT_TEMPORARY_TABLE_INIT_SIZE * sizeof(ljit_label*));

    /* Create the label table */
    new_function->lbl_index = 0;

    if (!new_function->start_blk)
    {
        free(new_function->temporary_table);
        free(new_function);
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

    /* Free the temporary table */
    for (unsigned short i = 0; i < fun->tmp_table_size; ++i)
    {
        if (fun->temporary_table[i])
        {
            free(fun->temporary_table[i]->data);
            free(fun->temporary_table[i]);
        }
    }

    /* Free the label table */
    for (unsigned short i = 0; i < fun->lbl_table_size; ++i)
    {
        if (fun->lbl_table[i])
        {
            free(fun->lbl_table[i]);
        }
    }

    free(fun->temporary_table);
    free(fun->lbl_table);
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
