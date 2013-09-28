#include <assert.h>

#include <ljit/ljit.h>
#include <ljit/elf.h>

int main(void)
{
    ljit_instance *instance = NULL;
    ljit_function *mul = NULL;
    ljit_types params[2] = {LJIT_INT, LJIT_INT};
    ljit_value x, y, z, a;
    int param1 = 5, param2 = 8;
    int mul_ret = 0;
    void *mul_params[2] = {&param1, &param2};

    instance = ljit_new_instance();

    mul = ljit_new_function(instance);
    assert(mul);

    ljit_new_signature(mul, LJIT_INT, 2, params);

    x = ljit_inst_get_param(mul, 0);
    y = ljit_inst_get_param(mul, 1);

    z = ljit_inst_mul(mul, x, y);
    a = ljit_inst_mul(mul, z, y);
    ljit_inst_return(mul, a);

    ljit_bytecode_dumper(stdout, mul);

    ljit_function_compile(mul);

    ljit_bytecode_dumper(stdout, mul);

    /* ljit_elf_debug_function(mul, "./elf_basic_fun"); */

    printf("Code address = %p\n", mul->code);

    ljit_call_function(mul, mul_params, &mul_ret);

    printf("Result %i\n", mul_ret);
    assert(mul_ret == 320);


    ljit_free_function(mul);
    ljit_free_instance(instance);

    return 0;
}
