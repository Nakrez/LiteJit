#include <ljit/ljit.h>

void ljit_call_function(ljit_function *fun, void **params, void *ret_val)
{
    ffi_call(&fun->signature->cif, FFI_FN(fun->code), ret_val, params);
}
