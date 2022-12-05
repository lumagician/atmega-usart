// include guard 
#ifndef UART_H
#define UART_H


// include the necessary libraries
#include <avr/io.h>
#include <avr/interrupt.h>



// function used to initialize the UART on atmega328p
void initUART(uint16_t ubrr);

// function used to transmit a single byte over UART
void transmitByte(uint8_t data);

// function used to receive a single byte over UART
uint8_t receiveByte(void);

// function used to create a callback for the UART receive interrupt
ISR(USART_RX_vect);

// function used to enable the UART receive interrupt
void enableReceiveInterrupt(void);

// function used to disable the UART receive interrupt
void disableReceiveInterrupt(void);

// function used to initialize global interrupts
void initGlobalInterrupts(void);


// end of include guard
#endif