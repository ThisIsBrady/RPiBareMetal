#include "../include/uart.h"
#include "../include/io.h"

#define AUX_MU_BAUD(baud) ((AUX_UART_CLOCK / (baud * 8)) - 1)

namespace io
{
    UART uart{};

    UART::UART()
    {
        mmio_write(AUX_ENABLES, 1); // enable UART1
        mmio_write(AUX_MU_IER_REG, 0);
        mmio_write(AUX_MU_CNTL_REG, 0);
        mmio_write(AUX_MU_LCR_REG, 3);
        mmio_write(AUX_MU_MCR_REG, 0);
        mmio_write(AUX_MU_IER_REG, 0);
        mmio_write(AUX_MU_IIR_REG, 0xC6);
        mmio_write(AUX_MU_BAUD_REG, AUX_MU_BAUD(115200));
        gpio_useAsAlt5(14);
        gpio_useAsAlt5(15);
        mmio_write(AUX_MU_CNTL_REG, 3);
    }

    bool UART::isOutputQueueEmpty()
    {
        return uart_output_queue_read == uart_output_queue_write;
    }

    void UART::writeByteBlockingActual(char ch)
    {
        while (!isWriteByteReady())
        {
        }
        mmio_write(AUX_MU_IO_REG, (unsigned int)ch);
    }

    void UART::loadOutputFifo()
    {
        while (!isOutputQueueEmpty() && isWriteByteReady())
        {
            writeByteBlockingActual(uart_output_queue[uart_output_queue_read]);
            uart_output_queue_read = (uart_output_queue_read + 1) & (UART_MAX_QUEUE - 1);
        }
    }

    void UART::writeByteBlocking(char ch)
    {
        unsigned int next = (uart_output_queue_write + 1) & (UART_MAX_QUEUE - 1);

        while (next == uart_output_queue_read)
            loadOutputFifo();

        uart_output_queue[uart_output_queue_write] = ch;
        uart_output_queue_write = next;
    }

    void UART::writeText(const char* buff)
    {
        while (*buff)
        {
            if (*buff == '\n')
                writeByteBlockingActual('\r');
            writeByteBlockingActual(*buff++);
        }
    }

    bool UART::isReadByteReady() { return mmio_read(AUX_MU_LSR_REG) & 0x01; }
    bool UART::isWriteByteReady() { return mmio_read(AUX_MU_LSR_REG) & 0x20; }

    uint8_t UART::readByte()
    {
        while (!isReadByteReady())
            ;
        return (uint8_t)mmio_read(AUX_MU_IO_REG);
    }

    void UART::drainOutputQueue()
    {
        while (!isOutputQueueEmpty())
            loadOutputFifo();
    }

    UART& operator<<(UART& out, const char* c)
    {
        out.writeText(c);
        return out;
    }

    UART& operator>>(UART& in, char& c)
    {
        c = in.readByte();
        return in;
    }
}
