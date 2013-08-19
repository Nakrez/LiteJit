#include <ljit/instance.h>
#include "internal.h"

ljit_instance *ljit_new_instance(void)
{
    ljit_instance *new_instance = NULL;

    if ((new_instance = malloc(sizeof(ljit_instance))) == NULL)
        return NULL;

    new_instance->target_arch = LJIT_ARCH_NONE;
    new_instance->usable_regs = 0;

    return new_instance;
}

void ljit_free_instance(ljit_instance *instance)
{
    free(instance);
}

void ljit_set_arch(ljit_instance *instance, ljit_arch_type arch)
{
    if (instance)
    {
        instance->target_arch = arch;

        /* Initialize platform parameters according to the new platform */

        switch (arch)
        {
            case LJIT_ARCH_NONE:
                break;
            case LJIT_ARCH_X86:
                break;
            case LJIT_ARCH_X64:
                break;
        }
    }
}
