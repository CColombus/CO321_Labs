#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define DEBOUNCE_DELAY_MS 200

int main()
{
    DDRD &= ~(1 << 2); // Set PD2 as input (INT0)
    DDRD &= ~(1 << 3); // Set PD3 as input (INT1)

    DDRB |= 0x3F; // Set PORTB as an output

    PORTB = 0x00; // Reset all outputs of PORTB to off

    EICRA |= ((1 << ISC01) | (1 << ISC00)); // Set INT0 to trigger on rising edge

    EICRA |= ((1 << ISC11) | (1 << ISC10)); // Set INT1 to trigger on rising edge

    sei(); // Enable global interrupts

    EIMSK |= (1 << INT0); // Enable external interrupt for INT0
    EIMSK |= (1 << INT1); // Enable external interrupt for INT1

    while (1)
    {
        // Your code here
    }

    return 0;
}

ISR(INT0_vect)
{
    _delay_ms(DEBOUNCE_DELAY_MS);   // Handle debounce issues
    if (PIND & (1 << PD2))          // Check after a delay if the button is still pressed
    {
        PORTB = (PORTB << 1); // Shifting the current value on PORTB
        PORTB |= (1 << 0);    // Setting PB0 to 1
    }
}

ISR(INT1_vect)
{
    _delay_ms(DEBOUNCE_DELAY_MS);
    if (PIND & (1 << PD3))
    {
        PORTB = (PORTB << 1); // Shifting the current value on PORTB
        PORTB &= ~(1 << 0);   // Setting PB0 to 0
    }
}
