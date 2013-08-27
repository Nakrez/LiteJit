#include <assert.h>

#include <ljit/ljit.h>
#include <ljit/elf.h>

int main(void)
{
    ljit_elf *elf = NULL;

    assert((elf = ljit_new_elf()) != NULL);

    assert(ljit_write_elf(elf, "test_elf") == 0);

    ljit_free_elf(elf);

    return 0;
}
