/*
 * ADC_singConv.c
 *
 *  Created on: 9 lip 2023
 *      Author: bmendyk
 */
#include <avr/io.h>


// Funkcja inicjalizuj�ca ADC
void ADC_Init()
	{
		// Wyb�r wewn�trznego �r�d�a napi�cia odniesienia
		// Ustawienie ADMUX[REFS1:0] na 0b00 wybierze Vcc jako �r�d�o odniesienia
		ADMUX &= ~(1 << REFS1);
		ADMUX |= (1 << REFS0);

		// W��czenie ADC
		ADCSRA |= (1 << ADEN);

		// Ustawienie ADC preskalera na 128
		// To spowoduje cz�stotliwo�� pr�bkowania ADC na poziomie 125 kHz przy zegarze 16 MHz
		ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

		// Ustawienie ADC na tryb pojedynczego pomiaru (Single Conversion Mode)
		ADCSRA |= (1 << ADSC);

		// Konfiguracja kana��w pomiarowych
			// Ustawienie DDRx na 0 na odpowiednich pinach oznacza wej�cia
			// Ustawienie MUXn na odpowiedniej warto�ci w ADMUX pozwala na wyb�r kana��w
			DDRD &= ~(1 << PD0); // Ustawienie PD0 jako wej�cie (ADC0)
			ADMUX &= 0xF0; // Wyczyszczenie bit�w MUXn
			ADMUX |= 0x00; // Wyb�r kana�u 0 (ADC0)

	}




    uint16_t GetADC_value(void)
    {
        // Pocz�tek konwersji ADC
        ADCSRA |= (1 << ADSC);

        // Odczekanie na koniec konwersji
        while (ADCSRA & (1 << ADSC)) {}

        // Odczytanie wyniku pomiaru
        return ADC;
    }





