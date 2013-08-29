#include <ljit/elf/elf-debug.h>

int ljit_elf_debug_function(ljit_function *fun, const char *file)
{
    ljit_elf *elf = ljit_new_elf();
    void *code = NULL;

    if (!elf)
        return -1;

    /* TODO memory clean */
    if ((code = malloc(fun->size_code)) == NULL)
        return -1;


    ljit_elf_add_section(elf, ".text", SHT_PROGBITS, SHF_ALLOC | SHF_EXECINSTR,
                         16, code, fun->size_code);

    ljit_write_elf(elf, file);

    ljit_free_elf(elf);

    return 0;
}
