#include <assert.h>

#include <ljit/ljit.h>

int mul_fun(int x, int y)
{
    return x * y;
}

int main(void)
{
    ljit_instance *instance = NULL;
    ljit_function *mul = NULL;
    ljit_types params[2] = {LJIT_INT, LJIT_INT};
    int param1 = 5, param2 = 8;
    void *mul_params[2] = {&param1, &param2};
    int res = 0;

    mul = ljit_new_function(instance);
    assert(mul);

    assert(ljit_new_signature(mul, LJIT_INT, 2, params) == 0);

    /* This is a little hack to test this function */
    mul->code = mul_fun;

    ljit_call_function(mul, mul_params, &res);

    printf("5 * 8 = %i\n", res);
    assert(res == 40);
    mul->code = NULL;

    ljit_free_function(mul);
    ljit_free_instance(instance);
    return 0;
}
