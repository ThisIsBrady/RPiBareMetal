#ifndef UART_H
#define UART_H

#include "io.h"
#include "types.h"

namespace io
{
    class UART
    {
        enum
        {
            AUX_BASE = io::Peripherals::PERIPHERAL_BASE + 0x215000,
            AUX_ENABLES = AUX_BASE + 4,
            AUX_MU_IO_REG = AUX_BASE + 64,
            AUX_MU_IER_REG = AUX_BASE + 68,
            AUX_MU_IIR_REG = AUX_BASE + 72,
            AUX_MU_LCR_REG = AUX_BASE + 76,
            AUX_MU_MCR_REG = AUX_BASE + 80,
            AUX_MU_LSR_REG = AUX_BASE + 84,
            AUX_MU_CNTL_REG = AUX_BASE + 96,
            AUX_MU_BAUD_REG = AUX_BASE + 104,
            AUX_UART_CLOCK = 500000000,
            UART_MAX_QUEUE = 16 * 1024,
        };

    private:
        unsigned char uart_output_queue[UART_MAX_QUEUE];
        unsigned int uart_output_queue_write = 0;
        unsigned int uart_output_queue_read = 0;

        bool isOutputQueueEmpty();
        bool isReadByteReady();
        bool isWriteByteReady();
        void loadOutputFifo();
        void writeByteBlockingActual(char ch);
        void writeByteBlocking(char ch);
        void drainOutputQueue();
        void update();

    public:
        UART();
        uint8_t readByte();
        void writeText(const char* buff);

        friend UART& operator<<(UART& out, const char* c);
        friend UART& operator>>(UART& in, char& c);
    };
    extern UART uart;

    UART& operator<<(UART& out, const char* c);
    UART& operator>>(UART& in, char& c);
}

#endif
