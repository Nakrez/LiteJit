#include <ljit/elf/elf-write.h>

static void _ljit_write_elf_sections(ljit_elf *elf, int fd)
{
    ljit_elf_section *tmp = elf->section;

    if (!tmp)
        return;

    while (tmp)
    {
        write(fd, tmp->header, sizeof(ljit_section_header));
        write(fd, tmp->data, tmp->header->sh_size);
        tmp = tmp->next;
    }
}

static void _ljit_update_elf(ljit_elf *elf)
{
    /* Current offset */
    unsigned int offset = sizeof(ljit_elf_header);

    /* TODO calculate this */
    elf->header->e_shoff = sizeof(ljit_elf_header);

    /* Calculate number of section header */
    ljit_elf_section *sec_tmp = elf->section;

    while (sec_tmp)
    {
        offset += sizeof(ljit_section_header);

        /* If the section is shstrtab put index in ELF header */
        if (sec_tmp->header->sh_name == 1)
            elf->header->e_shstrndx = elf->header->e_shnum;

        ++elf->header->e_shnum;

        /* Update section header infos */
        sec_tmp->header->sh_offset = offset;

        offset += sec_tmp->header->sh_size;

        sec_tmp = sec_tmp->next;
    }
}


int ljit_write_elf(ljit_elf *elf, const char *file)
{
    int disk_elf;

    if ((disk_elf = open(file, O_WRONLY | O_CREAT | O_TRUNC,
                               S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
        return -1;

    ljit_elf_add_section(elf, NULL);
    _ljit_update_elf(elf);

    /* Write the elf header */
    write(disk_elf, elf->header, sizeof(ljit_elf_header));

    _ljit_write_elf_sections(elf, disk_elf);
    close(disk_elf);

    return 0;
}
