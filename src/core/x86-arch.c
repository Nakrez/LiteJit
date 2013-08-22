#include <ljit/ljit.h>
#include "internal.h"

void ljit_setup_platform(ljit_instance *instance)
{
    if (instance)
    {
        instance->target_arch = LJIT_ARCH_X86;
        instance->usable_regs = LJIT_X86_USABLE_REGS;
    }
}

int ljit_compile_instr(ljit_codegen *cg, ljit_bytecode *instr)
{
    switch (instr->type)
    {
        #include "x86-code.inc"
    }

    return 0;
}

void ljit_gen_prolog(ljit_codegen *cg)
{
    unsigned char *code = cg->current;

    // push ebp
    ++code = 0x55;

    // mov ebp, esp
    ++code = 0x89;
    ++code = 0xE5;

    cg->current = code;
}
