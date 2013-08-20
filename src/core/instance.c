#include "internal.h"

ljit_instance *ljit_new_instance(void)
{
    ljit_instance *new_instance = NULL;

    if ((new_instance = malloc(sizeof(ljit_instance))) == NULL)
        return NULL;

    new_instance->usable_regs = 0;
    ljit_setup_platform(new_instance);

    return new_instance;
}

void ljit_free_instance(ljit_instance *instance)
{
    free(instance);
}
