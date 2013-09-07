#include <assert.h>

#include <ljit/ljit.h>
#include <ljit/elf.h>

int main(void)
{
    ljit_instance *instance = ljit_new_instance();
    ljit_function *fun = NULL;
    ljit_types params[2] = {LJIT_INT, LJIT_INT};
    ljit_value x, y;
    ljit_label *l1, *l2, *l3;
    int param1 = 1, param2 = 1;
    int fun_ret = 0;
    void *fun_params[2] = {&param1, &param2};

    assert(fun = ljit_new_function(instance));

    ljit_new_signature(fun, LJIT_INT, 2, params);

    l1 = ljit_new_label(fun);
    l2 = ljit_new_label(fun);
    l3 = ljit_new_label(fun);

    x = ljit_inst_get_param(fun, 0);
    y = ljit_inst_get_param(fun, 1);

    x = ljit_inst_mul(fun, x, y);
    x = ljit_inst_mul(fun, x, y);
    ljit_inst_jump(fun, l1);
    ljit_bind_label(fun, l1);
    x = ljit_inst_mul(fun, x, y);
    ljit_inst_jump(fun, l2);
    ljit_bind_label(fun, l2);
    x = ljit_inst_mul(fun, x, y);
    ljit_inst_jump(fun, l3);
    ljit_bind_label(fun, l3);
    x = ljit_inst_mul(fun, x, y);

    ljit_inst_return(fun, x);

    ljit_bytecode_dumper(stdout, fun);

    ljit_function_compile(fun);

    ljit_elf_debug_function(fun, "./elf_basic_regalloc");

    ljit_call_function(fun, fun_params, &fun_ret);

    printf("Result %i\n", fun_ret);

    ljit_free_function(fun);
    ljit_free_instance(instance);

    return 0;
}
