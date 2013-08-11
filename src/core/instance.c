#include "instance.h"

ljit_instance *ljit_new_instance(void)
{
    ljit_instance *new_instance = NULL;

    new_instance = malloc(sizeof(ljit_instance));

    return new_instance;
}

void ljit_free_instance(ljit_instance *instance)
{
    free(instance);
}
