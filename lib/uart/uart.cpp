#include "uart.h"


// function used to initialize the UART on atmega328p
void initUART(uint16_t ubrr)
{
    UBRR0H = (uint8_t)(ubrr >> 8);
    UBRR0L = (uint8_t)ubrr;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

// function used to transmit a single byte over UART
void transmitByte(uint8_t data)
{
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

// function used to receive a single byte over UART
uint8_t receiveByte(void)
{
    while (!(UCSR0A & (1 << RXC0)));
    return UDR0;
}

// function used to create a callback for the UART receive interrupt
ISR(USART_RX_vect)
{
    uint8_t data = UDR0;
    transmitByte(data);
}

// function used to enable the UART receive interrupt
void enableReceiveInterrupt(void)
{
    UCSR0B |= (1 << RXCIE0);
}

// function used to disable the UART receive interrupt
void disableReceiveInterrupt(void)
{
    UCSR0B &= ~(1 << RXCIE0);
}

// function used to initialize global interrupts
void initGlobalInterrupts(void)
{
    sei();
}