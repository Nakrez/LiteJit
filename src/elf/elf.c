#include <ljit/elf.h>

ljit_elf *ljit_new_elf(void)
{
    ljit_elf *elf = NULL;

    if ((elf = malloc(sizeof(ljit_elf))) == NULL)
        return NULL;

    if ((elf->header = _ljit_new_elf_header()) == NULL)
    {
        free(elf);
        return NULL;
    }

    elf->section = NULL;

    /* Add shstrtab section */
    if (_ljit_shstrtab_section(elf))
    {
        free(elf);
        return NULL;
    }

    return elf;
}

void ljit_free_elf(ljit_elf *elf)
{
    if (!elf)
        return;

    _ljit_free_elf_section(elf->section);
    _ljit_free_elf_header(elf->header);
    free(elf);
}
