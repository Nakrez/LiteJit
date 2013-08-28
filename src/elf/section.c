#include <ljit/elf/elf-section.h>

ljit_elf_section *_ljit_new_elf_section()
{
    ljit_elf_section *section;

    if ((section = malloc(sizeof(ljit_elf_section))) == NULL)
        return NULL;

    return section;
}

void _ljit_free_elf_section(ljit_elf_section *section)
{
    if (!section)
        return;

    _ljit_free_elf_section(section->next);
    free(section->header);
    free(section->data);
    free(section);
}

int ljit_elf_add_section(ljit_elf *elf, const char *name)
{
    ljit_elf_section *new_sec = NULL;

    if ((new_sec = malloc(sizeof(ljit_elf_section))) == NULL)
        return -1;

    if ((new_sec->header = malloc(sizeof(ljit_section_header))) == NULL)
    {
        free(new_sec);
        return -1;
    }

    new_sec->next = elf->section;
    elf->section = new_sec;

    return 0;
}
