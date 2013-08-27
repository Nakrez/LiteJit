#include <ljit/elf.h>

static ljit_elf_header *_ljit_new_elf_header(void)
{
    ljit_elf_header *header = NULL;

    if ((header = malloc(sizeof(ljit_elf_header))) == NULL)
        return NULL;

    /* Magic number */
    header->e_ident[EI_MAG0] = ELFMAG0;
    header->e_ident[EI_MAG1] = ELFMAG1;
    header->e_ident[EI_MAG2] = ELFMAG2;
    header->e_ident[EI_MAG3] = ELFMAG3;

    /* Class */
    header->e_ident[EI_CLASS] = ELFCLASS32;

    /* Endianness */
    header->e_ident[EI_DATA] = ELFDATA2LSB;

    /* Version */
    header->e_ident[EI_VERSION] = EV_CURRENT;
    header->e_version = EV_CURRENT;

    /* ABI */
    header->e_ident[EI_OSABI] = ELFOSABI_SYSV;

    /* Set padding bytes */
    memset(header->e_ident + EI_OSABI + 1, 0, EI_NIDENT - (EI_OSABI + 1));

    /* Type, for now only dynamic */
    header->e_type = ET_DYN;

    /* Machine */
    header->e_machine = EM_860;

    /* Size of headers */
    header->e_ehsize = sizeof(ljit_elf_header);
    header->e_phentsize = sizeof(ljit_program_header);
    header->e_shentsize = sizeof(ljit_section_header);

    /* Number of headers */
    header->e_phnum = 0;
    header->e_shnum = 0;

    return header;
}

static void _ljit_free_elf_header(ljit_elf_header *header)
{
    if (!header)
        return;

    free(header);
}

static void _ljit_free_elf_section(ljit_elf_section *section)
{
    if (!section)
        return;

    _ljit_free_elf_section(section->next);
    free(section->header);
    free(section->data);
    free(section);
}

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

int ljit_elf_add_section(ljit_elf *elf, const char *name)
{
    return 0;
}

int ljit_write_elf(ljit_elf *elf, const char *file)
{
    int disk_elf;

    if ((disk_elf = open(file, O_WRONLY | O_CREAT | O_TRUNC,
                               S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
        return -1;

    /* Write the elf header */
    write(disk_elf, elf->header, sizeof(ljit_elf_header));

    close(disk_elf);

    return 0;
}

#ifdef LJIT_DEBUG
void ljit_write_elf_function(ljit_function *fun, const char *path)
{

}
#endif /* LJIT_DEBUG */
