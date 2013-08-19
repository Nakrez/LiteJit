#include "regalloc.h"

int _ljit_regalloc(ljit_function *fun)
{
    /*
    If the number of temporary values in the function is inferior to the
    number of registers available then nothing to do
    */

    if (fun->uniq_index <= fun->instance->usable_regs)
        return 0;

    return 0;
}
