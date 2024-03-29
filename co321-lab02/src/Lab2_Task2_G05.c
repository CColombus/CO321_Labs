#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define DEBOUNCE_DELAY_MS 300

int main()
{
    DDRD &= ~(1 << 2); // Set PD2 as input (INT0)
    DDRB |= 0x3F;      // Set PB as an output

    PORTB = 0x00;

    EICRA |= (1 << ISC01); // Set INT0 to trigger on falling edge
    EICRA &= ~(1 << ISC00);

    sei(); // Enable global interrupts

    EIMSK |= (1 << INT0); // Enable external interrupt for INT0

    while (1)
    {
        // Your code here
    }

    return 0;
}

ISR(INT0_vect)
{
    _delay_ms(DEBOUNCE_DELAY_MS); // wait for debounce
    if (!(PIND & (1 << PD2)))
    {                        // check if the button is still released
        PORTB ^= (1 << PB0); // Toggle PB0
    _delay_ms(DEBOUNCE_DELAY_MS); // wait for debounce
    _delay_ms(DEBOUNCE_DELAY_MS); // wait for debounce
    }
}
