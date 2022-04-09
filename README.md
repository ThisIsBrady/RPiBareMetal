# RPiBareMetal
This project's purpose is for me to learn how bare metal level programming works and to get experience working with the GCC. 

 Compiling and running
----------------
Download the [(Arm GCC)](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-a/downloads) for the aarch64-none-elf target and add it to your path. Run `make` to compile. Get a MicroSD card with Raspbian already on it, and replace the kernel8.img file on it with the newly built image.

 Acknowledgements
----------------

Some of the code in this repo is based on or adapted from [(isometimes' rpi4-osdev tutorials)](https://github.com/isometimes/rpi4-osdev) and [(the OSdev Wiki)](https://wiki.osdev.org/Main_Page)
