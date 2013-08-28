#include <ljit/elf/elf-header.h>

ljit_elf_header *_ljit_new_elf_header(void)
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

void _ljit_free_elf_header(ljit_elf_header *header)
{
    if (!header)
        return;

    free(header);
}
