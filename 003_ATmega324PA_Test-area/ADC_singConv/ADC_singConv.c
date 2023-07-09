/*
 * ADC_singConv.c
 *
 *  Created on: 9 lip 2023
 *      Author: bmendyk
 */
#include <avr/io.h>


// Funkcja inicjalizuj¹ca ADC
void ADC_Init()
	{
		// Wybór wewnêtrznego Ÿród³a napiêcia odniesienia
		// Ustawienie ADMUX[REFS1:0] na 0b00 wybierze Vcc jako Ÿród³o odniesienia
		ADMUX &= ~(1 << REFS1);
		ADMUX |= (1 << REFS0);

		// W³¹czenie ADC
		ADCSRA |= (1 << ADEN);

		// Ustawienie ADC preskalera na 128
		// To spowoduje czêstotliwoœæ próbkowania ADC na poziomie 125 kHz przy zegarze 16 MHz
		ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

		// Ustawienie ADC na tryb pojedynczego pomiaru (Single Conversion Mode)
		ADCSRA |= (1 << ADSC);

		// Konfiguracja kana³ów pomiarowych
			// Ustawienie DDRx na 0 na odpowiednich pinach oznacza wejœcia
			// Ustawienie MUXn na odpowiedniej wartoœci w ADMUX pozwala na wybór kana³ów
			DDRD &= ~(1 << PD0); // Ustawienie PD0 jako wejœcie (ADC0)
			ADMUX &= 0xF0; // Wyczyszczenie bitów MUXn
			ADMUX |= 0x00; // Wybór kana³u 0 (ADC0)

	}




    uint16_t GetADC_value(void)
    {
        // Pocz¹tek konwersji ADC
        ADCSRA |= (1 << ADSC);

        // Odczekanie na koniec konwersji
        while (ADCSRA & (1 << ADSC)) {}

        // Odczytanie wyniku pomiaru
        return ADC;
    }





