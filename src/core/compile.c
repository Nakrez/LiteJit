#define _GNU_SOURCE
#include <sys/mman.h>
#include "internal.h"
#include "regalloc.h"

static void _ljit_compile_block(ljit_block *block)
{
    struct _ljit_bytecode_list_element_s *instr = block->instrs->head;

    while (instr)
    {
        ljit_compile_instr(instr->instr);
        instr = instr->next;
    }
}

int ljit_function_compile(ljit_function *fun)
{
    ljit_block *block = NULL;

    if (!fun->instance || fun->instance->target_arch == LJIT_ARCH_NONE)
        return -1;

    /*
    First compute register allocation according to the
    platform specifications
    */
    if (_ljit_regalloc(fun))
        return -1;

    /* Allocate some space for the generated code */
    /* FIXME : Review allocation process */
    if ((fun->code = mmap(NULL, 4096, PROT_EXEC | PROT_READ | PROT_WRITE,
                          MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == (void *)-1)
    {
        fun->code = NULL;
        return -1;
    }

    /* Compile every basic block */
    block = fun->start_blk;

    while (block)
    {
        _ljit_compile_block(block);
        block = block->next;
    }

    return 0;
}
