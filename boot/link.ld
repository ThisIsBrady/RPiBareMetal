SECTIONS
{
    . = 0x80000;
    
    .text : { KEEP(*(.text.boot)) *(.text .text.* .gnu.linkonce.t*) }
    .rodata : { *(.rodata .rodata.* .gnu.linkonce.r*) }
    
    .init_array :
    {
        cpp_support/crti.o(.init_array)
        KEEP (*(SORT(EXCLUDE_FILE(cpp_support/crti.o cpp_support/crtn.o) .init_array.*)))
        KEEP (*(EXCLUDE_FILE(cpp_support/crti.o cpp_support/crtn.o) .init_array))
        cpp_support/crtn.o(.init_array)
    }

    /* Include the list of termination functions sorted. */
    .fini_array :
    {
        cpp_support/crti.o(.fini_array)
        KEEP (*(SORT(EXCLUDE_FILE(cpp_support/crti.o crtn.o) .fini_array.*)))
        KEEP (*(EXCLUDE_FILE(cpp_support/crti.o cpp_support/crtn.o) .fini_array))
        cpp_support/crtn.o(.fini_array)
    }
    PROVIDE(_data = .);
    .data : { *(.data .data.* .gnu.linkonce.d*) }
    .bss (NOLOAD) : {
        . = ALIGN(16);
        __bss_start = .;
        *(.bss .bss.*)
        *(COMMON)
        __bss_end = .;
    }
    
    .eh_frame : {
		*(.eh_frame*)
	}

    _end = .;

    /DISCARD/ : { *(.comment) *(.gnu*) *(.note*) *(.eh_frame*) }
}
__bss_size = (__bss_end - __bss_start) >> 3;
