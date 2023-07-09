/*
 * ADC_singConv_IT.c
 *
 *  Created on: 9 lip 2023
 *      Author: bmendyk
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include "ADC_singConv_IT.h"

//volatile uint16_t resultADC;
// Funkcja inicjalizuj¹ca ADC
void ADC_Init_IT() {
    // Wybór wewnêtrznego Ÿród³a napiêcia odniesienia
    ADMUX &= ~(1 << REFS1);
    ADMUX |= (1 << REFS0);

    // W³¹czenie ADC
    ADCSRA |= (1 << ADEN);

    // Ustawienie ADC preskalera na 128
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

    // Ustawienie ADC na tryb pojedynczego pomiaru (Single Conversion Mode)
    ADCSRA |= (1 << ADSC);


    // Konfiguracja kana³ów pomiarowych

    // W³¹czenie przerwañ ADC
    ADCSRA |= (1 << ADIE);
}


// Obs³uga przerwania ADC
ISR(ADC_vect) {
    // Obs³uga przerwania ADC

    // Odczytanie wyniku pomiaru
    resultADC = ADC;

    // Przetworzenie wyniku pomiaru

    // Wykonanie innych operacji

    // Rozpoczêcie kolejnej konwersji ADC
    ADCSRA |= (1 << ADSC);
}

