#define _GNU_SOURCE
#include <sys/mman.h>
#include <ljit/ljit.h>

ljit_codegen *ljit_new_codegen(ljit_function *fun)
{
    ljit_codegen *cg = NULL;

    if ((cg = malloc(sizeof(ljit_codegen))) == NULL)
        return NULL;

    /* FIXME : Review allocation process */
    if ((cg->start = mmap(NULL, 4096, PROT_EXEC | PROT_READ | PROT_WRITE,
                          MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == (void *)-1)
    {
        free(cg);
        return NULL;
    }

    cg->fun = fun;

    fun->code = cg->start;
    cg->current = cg->start;

    return cg;
}

void ljit_free_codegen(ljit_codegen *cg)
{
    if (cg)
        return;

    free(cg);
}
