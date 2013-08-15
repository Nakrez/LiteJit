#include <assert.h>

#include <ljit/ljit.h>

int main(void)
{
    ljit_instance *test = NULL;

    test = ljit_new_instance();

    assert(test);

    ljit_set_arch(test, LJIT_ARCH_X86);

    assert(test->target_arch == LJIT_ARCH_X86);

    ljit_free_instance(test);

    return 0;
}
