#include <ljit/elf/elf-write.h>

static void _ljit_write_elf_sections(ljit_elf *elf, int fd)
{
    ljit_elf_section *tmp = elf->section;

    if (!tmp)
        return;

    while (tmp)
    {
        write(fd, tmp->header, sizeof(ljit_section_header));
        tmp = tmp->next;
    }
}

static void _ljit_update_elf(ljit_elf *elf)
{
    /* TODO calculate this */
    elf->header->e_shoff = sizeof(ljit_elf_header);

    /* Calculate number of section header */
    ljit_elf_section *sec_tmp = elf->section;

    while (sec_tmp)
    {
        ++elf->header->e_shnum;
        sec_tmp = sec_tmp->next;
    }
}


int ljit_write_elf(ljit_elf *elf, const char *file)
{
    int disk_elf;

    if ((disk_elf = open(file, O_WRONLY | O_CREAT | O_TRUNC,
                               S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
        return -1;

    _ljit_update_elf(elf);

    /* Write the elf header */
    write(disk_elf, elf->header, sizeof(ljit_elf_header));

    _ljit_write_elf_sections(elf, disk_elf);
    close(disk_elf);

    return 0;
}
