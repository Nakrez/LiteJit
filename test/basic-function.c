#include <assert.h>

#include <ljit/ljit.h>

int main(void)
{
    ljit_instance *instance = NULL;
    ljit_function *mul = NULL;
    ljit_types params[2] = {LJIT_INT, LJIT_INT};
    ljit_value x, y;

    instance = ljit_new_instance();
    ljit_set_arch(instance, LJIT_ARCH_X86);

    mul = ljit_new_function(instance);
    ljit_new_signature(mul, LJIT_INT, 2, params);

    x = ljit_inst_get_param(mul, 0);
    y = ljit_inst_get_param(mul, 1);

    ljit_bytecode_dumper(stdout, mul);

    ljit_free_function(mul);
    ljit_free_instance(instance);

    return 0;
}
