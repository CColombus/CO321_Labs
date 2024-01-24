#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main()
{
    DDRB |= 0x3F; // Set PORTB as an output
    PORTB = 0x00; // Reset all outputs of PORTB to off

    // To achieve 1s you need 15625 increments under a 1/1024 pre-scaler
    TCNT1 = 49912; // Set desired counter increments (65537-15625=49912)

    // Timer 1
    // Mode: Overflow, Interrupt
    // Prescaler: /1024
    TCCR1A = 0x00; // No need autoset at startup
    TCCR1B = (1 << CS12) | (0 << CS11) | (1 << CS10);
    TIMSK1 = (1 << TOIE1);

    sei(); // set global interrupts

    while (1)   // knight-rider code
    {
        for (int i = 0; i < 8; i++)
        {
            if (i<4)
            {
                // here (PORTB & 0xF0) clears lower 4bits of PORTB to accept the new knight-rider pattern
                // while keeping the upper 4bits the same, allowing to blink PB5 separately
                PORTB = (PORTB & 0xF0) | (0x01<<i);
                _delay_ms(100);
            }else
            {
                PORTB = (PORTB & 0xF0) | (0x80>>i);
                _delay_ms(100);               
            }
            
        }
    }

    return 0;
}

ISR(TIMER1_OVF_vect)
{
    PORTB ^= (1 << PB5);
    TCNT1 = 49912; // Set desired counter increments (65537-15625=49912) to achieve 1s
}