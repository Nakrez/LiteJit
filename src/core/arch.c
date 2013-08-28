#include <ljit/core/arch.h>

#if LJIT_RUNNING_ARCH == LJIT_ARCH_X86
# include "x86-arch.c"
#elif LJIT_RUNNING_ARCH == LJIT_ARCH_X64
# include "x86-arch.c"
#endif
