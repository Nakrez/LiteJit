#define _GNU_SOURCE
#include <sys/mman.h>
#include "internal.h"
#include "regalloc.h"

static void _ljit_compile_block(ljit_codegen *cg, ljit_block *block)
{
    struct _ljit_bytecode_list_element_s *instr = block->instrs->head;

    while (instr)
    {
        ljit_compile_instr(cg, instr->instr);
        instr = instr->next;
    }
}

int ljit_function_compile(ljit_function *fun)
{
    ljit_block *block = NULL;
    ljit_codegen *cg = NULL;

    if (!fun->instance || fun->instance->target_arch == LJIT_ARCH_NONE)
        return -1;

    /*
    First compute register allocation according to the
    platform specifications
    */
    if (_ljit_regalloc(fun))
        return -1;

    /* Allocate some space for the generated code */
    if ((cg = ljit_new_codegen(fun)) == NULL)
        return -1;

    /* Generates the prologue of the function */
    ljit_gen_prolog(cg);

    /* Compile every basic block */
    block = fun->start_blk;

    while (block)
    {
        _ljit_compile_block(cg, block);
        block = block->next;
    }

    fun->size_code = cg->current - cg->start;

    ljit_free_codegen(cg);

    return 0;
}
