#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

uint16_t fade_count = 0, fade = 0;

void delay_200ms();

int main(void)
{
    DDRB = 0xFF;
    PORTB = 0x00;

    while (1)
    {
        for (uint8_t i = 0; i < 4; i++)
        {
            PORTB = 1 << i;
            delay_200ms();
        }

        for (uint8_t i = 4; i > 0; i--)
        {
            PORTB = 1 << i;
            delay_200ms();
        }
    }
    
    return 0;
}

void delay_200ms(){
    TCNT1 = 62411;
    TCCR1A = 0x00;
    TCCR1B = _BV(CS12) | _BV(CS10);
    TIMSK1 = _BV(TOIE1);

    while ((TIFR1 & _BV(TOV1)) == 0);

    TIFR1 |= _BV(TOV1);

    TCCR1B = 0x00;
    TIMSK1 = 0x00;
}