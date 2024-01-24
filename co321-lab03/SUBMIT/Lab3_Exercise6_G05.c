#include <avr/io.h>
#include <avr/interrupt.h>

int main()
{
    DDRB |= 0x3F; // Set PORTB as an output
    PORTB = 0x00; // Reset all outputs of PORTB to off

    // For 50ms blink we will use TIMER0 as following,
    // TIMER0 will overflow every 1ms,
    // 1ms * 50 = 50ms

    // To achieve a 1ms you need 250 increments under a /64 pre-scaler
    TCNT0 = 6; // Set desired counter increments (256-250=6)

    // Timer 0
    // Mode: Overflow, Interrupt
    // Prescaler: /64
    TCCR0A = 0x00; // No need autoset at startup
    TCCR0B = (0 << CS02) | (1 << CS01) | (1 << CS00);
    TIMSK0 = (1 << TOIE0);

    // For 500ms blink we wil use TIMER1 directly,

    // To achieve 500ms you need 31250 increments under a /256 pre-scaler
    TCNT1 = 34287; // Set desired counter increments (65537-31250=34287)

    // Timer 1
    // Mode: Overflow, Interrupt
    // Prescaler: /64
    TCCR1A = 0x00; // No need autoset at startup
    TCCR1B = (0 << CS12) | (1 << CS11) | (1 << CS10);
    TIMSK1 = (1 << TOIE1);

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

    // 1ms * 50 is 50ms of delay
    if (timer >= 50)
    {
        PORTB ^= (1 << PB0);
        timer = 0;
    }

    TCNT0 = 6; // Set desired counter increments (256-250=6) to achieve 1ms
}

ISR(TIMER1_OVF_vect)
{
    PORTB ^= (1 << PB1);
    TCNT1 = 34287; // Set desired counter increments (65537-31250=34287)
}