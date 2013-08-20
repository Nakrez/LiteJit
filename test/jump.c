#include <assert.h>

#include <ljit/ljit.h>

int main()
{
    ljit_function *fun = NULL;
    ljit_label *lbl1 = NULL;
    ljit_label *lbl2 = NULL;
    ljit_instance *instance = ljit_new_instance();
    ljit_value zero = ljit_new_uchar_cst(0);
    ljit_value one = ljit_new_uchar_cst(1);

    fun = ljit_new_function(instance);
    assert(fun);

    ljit_new_signature(fun, LJIT_INT, 0, NULL);

    lbl1 = ljit_new_label(fun);
    lbl2 = ljit_new_label(fun);

    ljit_inst_jump_if(fun, zero, lbl1);
    ljit_inst_jump(fun, lbl2);
    ljit_bind_label(fun, lbl1);
    ljit_inst_return(fun, zero);
    ljit_bind_label(fun, lbl2);
    ljit_inst_return(fun, one);

    ljit_bytecode_dumper(stdout, fun);

    ljit_free_function(fun);
    ljit_free_instance(instance);

    return 0;
}
