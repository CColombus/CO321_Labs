#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

uint16_t fade_count = 0, fade = 0;
uint8_t i = 0;

uint8_t play = 1;

void delay_200ms();

void init_PWM();

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
        if (play)
        {
            while (i < 4)
            {
                PORTB = 0b00000010 << i;
                delay_200ms();

                i++;
            }

            i = 4;

            while (i > 0)
            {
                PORTB = 0b00000010 << i;
                delay_200ms();

                i--;
            }
        }
        else
        {
            if (PORTB == 0b00010000)
            {
                init_PWM();

                while (!play)
                {
                    fade_count++;

                    if (fade_count >= 400)
                        fade_count = 0;

                    if (fade_count < 200)
                    {
                        OCR2A = fade_count;
                    }
                    else
                    {
                        OCR2A = 200 - (fade_count - 200);
                    }

                    _delay_ms(10);
                }

                TCCR2A = 0x00;
                TCCR2B = 0x00;
                OCR2A = 0xFF;
            }
        }
    }

    return 0;
}

void init_PWM()
{
    TCCR2A = 0b10000011;
    TCCR2B = _BV(CS22);
    OCR2A = 0;
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