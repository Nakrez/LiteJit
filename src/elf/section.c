#include <ljit/elf/elf-section.h>

int _ljit_shstrtab_add_string(ljit_elf *elf, const char *str)
{
    /* Calculate the future size of the shstrtab buffer */
    unsigned int new_size = elf->shstrtab->header->sh_size + strlen(str) + 1;
    int offset = elf->shstrtab->header->sh_size;

    /* Reallocate shstrtab buffer if to small */
    while (elf->shstrtab_max_size < new_size)
    {
        elf->shstrtab_max_size *= 2;
        if ((elf->shstrtab->data = realloc(elf->shstrtab->data,
                                           elf->shstrtab_max_size)) == NULL)
            return -1;
    }

    /* Copy the new string into the shstrtab buffer */
    strcpy(((char *)elf->shstrtab->data) + offset, str);

    /* Update the header size field of the section */
    elf->shstrtab->header->sh_size = new_size;

    return offset;
}

int _ljit_shstrtab_section(ljit_elf *elf)
{
    char *buf = NULL;

    if ((elf->shstrtab = _ljit_new_elf_section()) == NULL)
        return -1;

    elf->shstrtab_max_size = 64;

    if ((elf->shstrtab->data = malloc(elf->shstrtab_max_size)) == NULL)
    {
        free(elf->shstrtab->header);
        free(elf->shstrtab);
        return -1;
    }

    /* Add the .shstrtab data */
    buf = elf->shstrtab->data;

    buf[0] = 0;
    strcpy(buf + 1, ".shstrtab");
    elf->shstrtab->header->sh_size = 2 + strlen(".shstrtab");

    /*
    ** Init header, some value like offset, next, ... are computed when
    ** writing ELF
    */
    elf->shstrtab->header->sh_name = 1;
    elf->shstrtab->header->sh_type = SHT_STRTAB;
    elf->shstrtab->header->sh_addralign = 1;

    /* Add shstrtab section at the end */
    elf->shstrtab->next = elf->section;
    elf->section = elf->shstrtab;

    return 0;
}

ljit_elf_section *_ljit_new_elf_section()
{
    ljit_elf_section *section;

    if ((section = malloc(sizeof(ljit_elf_section))) == NULL)
        return NULL;

    if ((section->header = malloc(sizeof(ljit_section_header))) == NULL)
    {
        free(section);
        return NULL;
    }

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

    if ((new_sec = _ljit_new_elf_section()) == NULL)
        return -1;

    if (!name)
        new_sec->header->sh_name = 0;
    else
    {
        
    }

    new_sec->next = elf->section;
    elf->section = new_sec;

    return 0;
}
