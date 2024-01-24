#include <avr/io.h>

void delay()
{
    // We need 125 increments to get 2ms under 16us increment segements
    TCNT0 = 131; // Reset TIMER0 Counter to 131

    TCCR0A = 0x00; // Set normal mode
    TCCR0B = 0x04; // Set clock source no pre-scale

    while ((TIFR0 & 0x01) == 0)
    {
        // stuck in while loop until timer ovrflow flag
    }

    TCCR0A = 0x00; // Set normal mode
    TCCR0B = 0x00; // Set no source to disable counter

    TIFR0 = 0x01; // Manually clear the TOV0 flag
}

int main()
{
    DDRB |= 0x3F; // Set PORTB as an output

    PORTB = 0x00; // Reset all outputs of PORTB to off

    while (1)
    {
        PORTB = PORTB | (1 << PB0); // ON PB0
        delay();
        PORTB = PORTB & ~(1 << PB0); // OFF PB0
        delay();
    }

    return 0;
}