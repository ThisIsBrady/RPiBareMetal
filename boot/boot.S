.section ".text.boot"

.global _start

_start:
    //Check on main core
    mrs x1, mpidr_el1
    and x1, x1, 0x3
    cbz x1, 2f

1:
    wfe
    b   1b
2:
    ldr x1, =_start
    mov sp, x1

    //Clean BSS
    ldr x1, =__bss_start    //Start addr
    ldr w2, =__bss_size     //Size of section
3:
    cbz w2, 4f              //Quit loop if zero
    str xzr, [x1], 0x8
    sub w2, w2, 0x1
    cbnz w2, 3b             //Loop if non-zero

4:
    bl  _init               //Construct global objects
    bl  main                //Jump to main() C routine, don't return
    bl _fini                //Destruct global objects
    b   1b                  //Halt master core if it does return
