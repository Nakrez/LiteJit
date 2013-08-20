#include "internal.h"
#include "regalloc.h"

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

    return 0;
}
