#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include <uart.h>

int main(void)
{
    // initialize the UART
    initUART(103);
    // initialize the global interrupts
    initGlobalInterrupts();

    // set PB5 as output
    DDRB |= (1 << PB5);

    // enable the UART receive interrupt
    enableReceiveInterrupt();
    

    // loop forever
    while (1) {
        // check interrupt flag every 10ms
        _delay_ms(10);
        // if the interrupt flag is set
        if (UCSR0A & (1 << RXC0)) {
            // toggle PB5
            PORTB ^= (1 << PB5);
            // clear the interrupt flag
            UCSR0A &= ~(1 << RXC0);
        }

    }
}
