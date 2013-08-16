#include "internal.h"

ljit_block *ljit_new_block(void)
{
    ljit_block *block = NULL;

    if ((block = malloc(sizeof(ljit_block))) == NULL)
        return NULL;

    block->next = NULL;
    block->previous = NULL;

    if ((block->instrs = ljit_new_bytecode_list()) == NULL)
    {
        free(block);
        return NULL;
    }

    return block;
}

void ljit_free_block(ljit_block *block)
{
    if (!block)
        return;

    ljit_free_bytecode_list(block->instrs);

    free(block);
}
