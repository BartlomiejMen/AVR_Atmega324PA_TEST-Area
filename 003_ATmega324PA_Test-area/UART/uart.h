/*
 * uart.h
 *
 *  Created on: 9 lip 2023
 *      Author: bmendyk
 */

#ifndef UART_UART_H_
#define UART_UART_H_

// DEFINICJE
	#define UART_BUFFER_SIZE 32

//DEKLARACJE



//FUNKCJE
	void uart_buffer_put(unsigned char data);
	// Inicjalizacja UART
	void uart_init(unsigned int baud_rate);
	// Funkcja wysyłająca pojedynczy znak
	void uart_transmit_char(unsigned char data);
	// Funkcja wysyłająca napis
	void uart_transmit_string(const char* string);
	// Funkcja wysyłająca liczbę jako tekst
	void uart_transmit_number(int number);


	// Funkcja obsługująca przerwanie odbiornika UART
	//ISR(USART_RX_vect);

#endif /* UART_UART_H_ */
