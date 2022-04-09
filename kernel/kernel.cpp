#include "../include/uart.h"

extern "C" void __cxa_pure_virtual() {}

extern "C" void main()
{
    io::uart << "testing";
    char c[2];
    c[1] = 0;
    while (true)
    {
        io::uart >> c[0];
        if (c[0] == '\r')
            c[0] = '\n';
        io::uart << c;
    }
}
