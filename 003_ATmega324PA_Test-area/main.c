/*
 * main.c
 *
 *  Created on: 9 lip 2023
 *      Author: bmendyk
 */

#include <avr/io.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "UART/uart.h"


int main(void)
{

    // Inicjalizacja UART z prêdkoœci¹ 9600 bps
    uart_init(51);  // dla F_CPU = 8 MHz



	//Dierect Pin Ports
	DDRB =(1<<PB5);
	DDRC = (1<<PC0)|(1<<PC1)|(1<<PC2)|(1<<PC3);

	sei();

	while(1)
	{
		uart_transmit_char('A');
		uart_transmit_string("Hello, World!");
		uart_transmit_number(12345);

		_delay_ms(500);
		PORTB ^= (PB5);
		PORTC ^=(0X0F); //ustawienie portu w stan wysoki


	}
}
// Funkcja obs³uguj¹ca przerwanie odbiornika UART
ISR(USART0_RX_vect) {
    unsigned char data = UDR0;
    uart_buffer_put(data);
}
ISR(TIMER0_OVF_vect)
{

}
