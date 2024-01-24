#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

uint16_t fade_count = 0, fade = 0;
uint8_t i = 0;

uint8_t play = 1;

void delay_200ms();

int main(void)
{
    DDRB = 0xFF;
    PORTB = 0x00;

    DDRD &= ~_BV(PD2);

    EICRA |= _BV(ISC01);
    EIMSK |= _BV(INT0);

    sei();

    while (1)
    {
        while (i < 4)
        {
            PORTB = 1 << i;
            delay_200ms();

            if (play)
                i++;
        }

        i = 4;

        while (i > 0)
        {
            PORTB = 1 << i;
            delay_200ms();

            if (play)
                i--;
        }
    }

    return 0;
}

void delay_200ms()
{
    TCNT1 = 62411;
    TCCR1A = 0x00;
    TCCR1B = _BV(CS12) | _BV(CS10);

    while ((TIFR1 & _BV(TOV1)) == 0)
        ;

    TIFR1 |= _BV(TOV1);

    TCCR1B = 0x00;
    TIMSK1 = 0x00;
}

ISR(INT0_vect)
{
    if (!(PIND & _BV(PD2)))
    {
        _delay_ms(100);
        if (!(PIND & _BV(PD2)))
        {
            play ^= 1;
        }
    }
}