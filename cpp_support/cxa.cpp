#include "../include/types.h"

namespace __cxxabiv1
{
    // TODO: Multithread compatability
    typedef volatile uint64_t __guard;

    extern "C" int __cxa_guard_acquire(__guard* g)
    {
        return !*(char*)(g);
    }

    extern "C" void __cxa_guard_release(__guard* g)
    {
        *(char*)g = 1;
    }

    extern "C" void __cxa_guard_abort(__guard*)
    {
    }
}
