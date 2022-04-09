#include "../include/io.h"

namespace io
{
    void mmio_write(long reg, unsigned int val)
    {
        *(volatile unsigned int*)reg = val;
    }

    unsigned int mmio_read(long reg)
    {
        return *(volatile unsigned int*)reg;
    }

    unsigned int gpio_call(unsigned int pin_number, unsigned int value, unsigned int base, unsigned int field_size, unsigned int field_max)
    {
        unsigned int field_mask = (1 << field_size) - 1;

        if (pin_number > field_max)
            return 0;
        if (value > field_mask)
            return 0;

        unsigned int num_fields = 32 / field_size;
        unsigned int reg = base + ((pin_number / num_fields) * 4);
        unsigned int shift = (pin_number % num_fields) * field_size;

        unsigned int curVal = mmio_read(reg);
        curVal &= ~(field_mask << shift);
        curVal |= value << shift;
        mmio_write(reg, curVal);

        return 1;
    }

    unsigned int gpio_set(unsigned int pin_number, unsigned int value) { return gpio_call(pin_number, value, GPSET0, 1, GPIO_MAX_PIN); }
    unsigned int gpio_clear(unsigned int pin_number, unsigned int value) { return gpio_call(pin_number, value, GPCLR0, 1, GPIO_MAX_PIN); }
    unsigned int gpio_pull(unsigned int pin_number, PULL_MODE value) { return gpio_call(pin_number, (unsigned int)value, GPPUPPDN0, 2, GPIO_MAX_PIN); }
    unsigned int gpio_function(unsigned int pin_number, unsigned int value) { return gpio_call(pin_number, value, GPFSEL0, 3, GPIO_MAX_PIN); }

    void gpio_useAsAlt5(unsigned int pin_number)
    {
        gpio_pull(pin_number, PULL_MODE::PULL_NONE);
        gpio_function(pin_number, GPIO_FUNCTION_ALT5);
    }
}
