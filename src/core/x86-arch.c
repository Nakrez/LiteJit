#include <ljit/ljit.h>
#include "internal.h"

void setup_x86_platform(ljit_instance *instance)
{
    if (instance)
    {
        instance->usable_regs = LJIT_X86_USABLE_REGS;
    }
}
