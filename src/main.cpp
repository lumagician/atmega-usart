#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include <uart.h>

// global interrupt flag
volatile uint8_t interruptFlag = 0;

int main(void)
{
    // initialize the UART using the baud to UBRR conversion macro
    initUART(UBRR_VALUE(9600));
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
            interruptFlag = 0;
        }

    }
}

// interrupt handler for the UART receive interrupt
ISR(USART_RX_vect)
{
    // read the received byte
    uint8_t data = UDR0;
    // check if the received byte is 'a'
    if (data == 'a') {
        // set interrupt flag
        interruptFlag = 1;
    }
}