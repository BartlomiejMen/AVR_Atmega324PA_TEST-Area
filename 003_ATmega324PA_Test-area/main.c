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

void initComparExtSource(uint8_t sourceSel);
void ComparFallingEdg(void);
void ComparRisingEdg(void);

int main(void)
{

    // Inicjalizacja UART z prêdkoœci¹ 9600 bps
    uart_init(51);  // dla F_CPU = 8 MHz
    initComparExtSource(0);


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

//Cia³a funkcji prototypowych
void initComparExtSource(uint8_t sourceSel)
{
	ADCSRB |= (1<<ACME) & ~(1<<ADEN);
	ADMUX = (1<<sourceSel);
	ACSR = (1<<ACIE);
	void ComparFallingEdg(void);
}// funkcja inicjuj¹ca pracê komparatora (we: AIN0 i AIN1) z wykorzystaiem ¿ród³a zewnêtrzego z wyborem ¿ród³a sygna³u

void ComparFallingEdg(void)
{
	ACSR |= (1<<ACIS1);
	ACSR &=	~(1<<ACIS0); // ACIS1 =1 ACIS0 =0 -Falling
}// ustawia przerwanie na zbocze opadaj¹ce
void ComparRisingEdg(void)
{
	ACSR = (1<<ACIS1) | (1<<ACIS0); // ACIS1 =1 ACIS0 =1 -Rising
}// ustawia przerwanie na zbocze narastaj¹ce

// Funkcja obs³uguj¹ca przerwanie odbiornika UART
ISR(USART0_RX_vect) {
    unsigned char data = UDR0;
    uart_buffer_put(data);
}
ISR(TIMER0_OVF_vect)
{

}
ISR(ANALOG_COMP_vect)
{
	static uint8_t state=0;
	if (!state)
	{	PORTC |=(1<<PC0);
		if(PINC &(1<<PC0)) ComparRisingEdg();
		state =1;
	}
	if (state>0) {
		PORTC &=~(1<<PC0);
		ComparFallingEdg();
		state =0;
	}

}
