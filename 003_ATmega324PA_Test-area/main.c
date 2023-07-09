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


int main(void)
{

	/specjalny komentarz
	//Dierect Pin Ports
	DDRB =(1<<PB5);
	DDRC = (1<<PC0)|(1<<PC1)|(1<<PC2)|(1<<PC3);

	//sei();

	while(1)
	{

		PORTB ^= (PB5);
		_delay_ms(1000);

	}
}

ISR(TIMER0_OVF_vect)
{

}
