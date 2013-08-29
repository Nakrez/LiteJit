#include <assert.h>

#include <ljit/ljit.h>
#include <ljit/elf.h>

void *elf_text()
{
    // mov eax, 0
    // ret
    unsigned char code[] = {0xb8, 0x00, 0x00, 0x00, 0x00, 0xc3};

    void *buf = calloc(1, 16);

    memcpy(buf, code, sizeof(code));

    return buf;
}

int main(void)
{
    ljit_elf *elf = NULL;

    assert((elf = ljit_new_elf()) != NULL);

    ljit_elf_add_section(elf, ".text", SHT_PROGBITS, SHF_ALLOC | SHF_EXECINSTR,
                         16, elf_text(), 16);

    assert(ljit_write_elf(elf, "test_elf") == 0);

    ljit_free_elf(elf);

    return 0;
}
