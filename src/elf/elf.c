#include <ljit/elf.h>

ljit_elf *ljit_new_elf(void)
{
    ljit_elf *elf = NULL;

    if ((elf = malloc(sizeof(ljit_elf))) == NULL)
        return NULL;

    return elf;
}

void ljit_free_elf(ljit_elf *elf)
{
    if (!elf)
        return;

    free(elf);
}

#ifdef LJIT_DEBUG
void ljit_write_elf_function(ljit_function *fun, const char *path)
{

}
#endif /* LJIT_DEBUG */
