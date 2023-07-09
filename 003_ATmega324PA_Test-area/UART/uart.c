/*
 * uart.c
 *
 *  Created on: 9 lip 2023
 *      Author: bmendyk
 */


#include <avr/io.h>
#include <stdio.h>
#include "uart.h"

// Definicje bufora cyklicznego
	volatile unsigned char uart_buffer[UART_BUFFER_SIZE];
	volatile unsigned int uart_buffer_head = 0;
	volatile unsigned int uart_buffer_tail = 0;


// Inicjalizacja UART
void uart_init(unsigned int baud_rate) {
    // Ustawienie prêdkoœci transmisji
    UBRR0H = (unsigned char)(baud_rate >> 8);
    UBRR0L = (unsigned char)baud_rate;

    // W³¹czenie nadajnika i odbiornika
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);

    // Ustawienie formatu ramki danych: 8 bitów danych, 1 bit stopu
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

    // W³¹czenie przerwañ dla odbiornika
    UCSR0B |= (1 << RXCIE0);
}

// Funkcja dodaj¹ca dane do bufora cyklicznego
void uart_buffer_put(unsigned char data) {
    unsigned int next = (uart_buffer_head + 1) % UART_BUFFER_SIZE;

    // Sprawdzenie czy bufor jest pe³ny
    if (next != uart_buffer_tail) {
        uart_buffer[uart_buffer_head] = data;
        uart_buffer_head = next;
    }
}

// Funkcja wysy³aj¹ca pojedynczy znak
void uart_transmit_char(unsigned char data) {
    // Oczekiwanie na zakoñczenie poprzedniej transmisji
    while (!(UCSR0A & (1 << UDRE0)));

    // Wys³anie znaku
    UDR0 = data;
}

// Funkcja wysy³aj¹ca napis
void uart_transmit_string(const char* string) {
    unsigned int i = 0;
    while (string[i] != '\0') {
        uart_transmit_char(string[i]);
        i++;
    }
}

// Funkcja wysy³aj¹ca liczbê jako tekst
void uart_transmit_number(int number) {
    char buffer[16];
    sprintf(buffer, "%d", number);
    uart_transmit_string(buffer);
}




