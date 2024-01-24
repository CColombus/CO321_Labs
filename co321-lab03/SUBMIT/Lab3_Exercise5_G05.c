#include <avr/io.h>
#include <avr/interrupt.h>

int main()
{
    DDRB |= 0x3F; // Set PORTB as an output
    PORTB = 0x00; // Reset all outputs of PORTB to off

    // To achieve a 1ms you need 250 increments under a 1/64 pre-scaler
    TCNT0 = 6; // Set desired counter increments (256-250=6)

    // Timer 0
    // Mode: Overflow, Interrupt
    // Prescaler: /64
    TCCR0A = 0x00; // No need autoset at startup
    TCCR0B = (0 << CS02) | (1 << CS01) | (1 << CS00);
    TIMSK0 = (1 << TOIE0);

    sei(); // set global interrupts

    while (1)
    {
        // nothing here
    }

    return 0;
}

char timer = 0;

ISR(TIMER0_OVF_vect)
{
    timer++;

    // 1ms * 100 is 100ms of delay
    if (timer >= 100)
    {
        PORTB ^= (1 << PB0);    //Toggle the LED
        timer = 0;
    }

    TCNT0 = 6; // Set desired counter increments (256-250=6) to achieve 1ms
}