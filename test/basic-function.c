#include <assert.h>

#include "../src/core/instance.h"
#include "../src/core/function.h"

int main(void)
{
    ljit_instance *test = NULL;
    ljit_function *mul = NULL;

    test = ljit_new_instance();

    ljit_set_arch(test, LJIT_ARCH_X86);

    mul = ljit_new_function();

    ljit_new_signature(mul, LJIT_INT, 0, NULL);

    ljit_free_function(mul);

    ljit_free_instance(test);

    return 0;
}
