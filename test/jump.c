#include <ljit/ljit.h>

int main()
{
    ljit_function *fun = NULL;
    ljit_label *lbl1 = NULL;
    ljit_instance *instance = ljit_new_instance();
    ljit_value zero = ljit_new_uchar_cst(0);

    ljit_set_arch(instance, LJIT_ARCH_X86);

    fun = ljit_new_function(instance);
    ljit_new_signature(fun, LJIT_INT, 0, NULL);

    lbl1 = ljit_new_label(fun);

    ljit_inst_jump(fun, lbl1);
    ljit_bind_label(fun, lbl1);
    ljit_inst_return(fun, zero);

    ljit_bytecode_dumper(stdout, fun);

    ljit_free_function(fun);
    ljit_free_instance(instance);

    return 0;
}
