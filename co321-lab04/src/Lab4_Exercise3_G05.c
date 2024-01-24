#include <avr/io.h>
#include <util/delay.h>

void initPWM()
{
    // set OC1A pin as output
    DDRB |= _BV(PB1);

    // set phase and frequency correct PWM mode with ICR1 as TOP
    TCCR1B |= _BV(WGM13);

    // set non-inverting mode
    TCCR1A |= _BV(COM1A1);

    // set prescaler to /8
    TCCR1B |= _BV(CS11);
}

// custom_delay_ms() function to generate delay in milliseconds
// beacause _delay_ms() function can't take variable arguments
void custom_delay_ms(int dly)
{
    while (dly--)
    {
        _delay_ms(1);
    }
}

void tone(float freq, int dly)
{
    // set frequency
    // TOP = F_CPU / (2 * prescaler * freq)
    ICR1 = F_CPU / (2 * 8 * freq);

    // set duty cycle of 12.5%
    OCR1A = ICR1 / 8;

    custom_delay_ms(dly);
}

int main(void)
{

    initPWM();

    // play "Fur Elise"
    while (1)
    {
        // play e4
        tone(329.63, 200);
        _delay_ms(150);
        // play d4#
        tone(311.13, 200);
        _delay_ms(150);
        // play e4
        tone(329.63, 200);
        _delay_ms(150);
        // play d4#
        tone(311.13, 200);
        _delay_ms(150);
        // play e4
        tone(329.63, 200);
        _delay_ms(150);
        // play b3
        tone(246.94, 200);
        _delay_ms(200);
        // play d4
        tone(293.66, 200);
        _delay_ms(200);
        // play c4
        tone(261.63, 200);
        _delay_ms(200);
        // play a3
        tone(220, 800);
        _delay_ms(800);
        // play d3
        tone(146.83, 200);
        _delay_ms(150);
        // play f3
        tone(174.61, 200);
        _delay_ms(200);
        // play a3
        tone(220, 200);
        _delay_ms(200);
        // play b3
        tone(246.94, 800);
        _delay_ms(800);
        // play f3
        tone(174.61, 200);
        _delay_ms(200);
        // play a3#
        tone(233.08, 200);
        _delay_ms(200);
        // play b3
        tone(246.94, 200);
        _delay_ms(200);
        // play c4
        tone(261.63, 800);
        _delay_ms(800);
        _delay_ms(100);
        // play e4
        tone(329.63, 200);
        _delay_ms(200);
        // play d4#
        tone(311.13, 200);
        _delay_ms(200);
        // play e4
        tone(329.63, 200);
        _delay_ms(200);
        // play d4#
        tone(311.13, 200);
        _delay_ms(200);
        // play e4
        tone(329.63, 200);
        _delay_ms(200);
        // play b3
        tone(246.94, 200);
        _delay_ms(200);
        // play d4
        tone(293.66, 200);
        _delay_ms(200);
        // play c4
        tone(261.63, 200);
        _delay_ms(200);
        // play a3
        tone(220, 800);
        _delay_ms(800);
        // play d3
        tone(146.83, 200);
        _delay_ms(200);
        // play f3
        tone(174.61, 200);
        _delay_ms(200);
        // play a3
        tone(220, 200);
        _delay_ms(200);
        // play b3
        tone(246.94, 800);
        _delay_ms(800);
        // play f3
        tone(174.61, 200);
        _delay_ms(200);
        // play c4
        tone(261.63, 200);
        _delay_ms(200);
        // play b3
        tone(246.94, 200);
        _delay_ms(200);
        // play a3
        tone(220, 800);
        _delay_ms(800);
        // play b3
        tone(246.94, 200);
        _delay_ms(200);
        // play c4
        tone(261.63, 200);
        _delay_ms(200);
        // play d4
        tone(293.66, 200);
        _delay_ms(200);
        // play e4
        tone(329.63, 800);
        _delay_ms(800);
        // play g3
        tone(196, 200);
        _delay_ms(200);
        // play f4
        tone(349.23, 200);
        _delay_ms(200);
        // play e4
        tone(329.23, 200);
        _delay_ms(200);
        // play d4
        tone(293.63, 800);
        _delay_ms(800);
        // play e3
        tone(164.81, 200);
        _delay_ms(200);
        // play e4
        tone(329.63, 200);
        _delay_ms(200);
        // play d4
        tone(293.63, 200);
        _delay_ms(200);
        // play c4
        tone(261.63, 800);
        _delay_ms(800);
        // play d3
        tone(146.83, 200);
        _delay_ms(200);
        // play d4
        tone(293.63, 200);
        _delay_ms(200);
        // play c4
        tone(261.63, 200);
        _delay_ms(200);
        // play b3
        tone(246.94, 800);
        _delay_ms(800);
        _delay_ms(200);
        // play e4
        tone(329.63, 200);
        _delay_ms(200);
        // play d4#
        tone(311.13, 200);
        _delay_ms(150);
        // play e4
        tone(329.63, 200);
        _delay_ms(150);
        // play d4#
        tone(311.13, 200);
        _delay_ms(150);
        // play e4
        tone(329.63, 200);
        _delay_ms(150);
        // play b3
        tone(246.94, 200);
        _delay_ms(200);
        // play d4
        tone(293.66, 200);
        _delay_ms(200);
        // play c4
        tone(261.63, 200);
        _delay_ms(200);
        // play a3
        tone(220, 800);
        _delay_ms(800);
        // play d3
        tone(146.83, 200);
        _delay_ms(150);
        // play f3
        tone(174.61, 200);
        _delay_ms(200);
        // play a3
        tone(220, 200);
        _delay_ms(200);
        // play b3
        tone(246.94, 800);
        _delay_ms(800);
        // play f3
        tone(174.61, 200);
        _delay_ms(200);
        // play a3
        tone(233.08, 200);
        _delay_ms(200);
        // play b3
        tone(246.94, 200);
        _delay_ms(200);
        // play c4
        tone(261.63, 800);
        _delay_ms(800);
        _delay_ms(100);
        // play e4
        tone(329.63, 200);
        _delay_ms(200);
        // play d4#
        tone(311.13, 200);
        _delay_ms(200);
        // play e4
        tone(329.63, 200);
        _delay_ms(200);
        // play d4#
        tone(311.13, 200);
        _delay_ms(200);
        // play e4
        tone(329.63, 200);
        _delay_ms(200);
        // play b3
        tone(246.94, 200);
        _delay_ms(200);
        // play d4
        tone(293.66, 200);
        _delay_ms(200);
        // play c4
        tone(261.63, 200);
        _delay_ms(200);
        // play a3
        tone(220, 800);
        _delay_ms(800);
        // play d3
        tone(146.83, 200);
        _delay_ms(200);
        // play f3
        tone(174.61, 200);
        _delay_ms(200);
        // play a3
        tone(220, 200);
        _delay_ms(200);
        // play b3
        tone(246.94, 800);
        _delay_ms(800);
        // play f3
        tone(174.61, 200);
        _delay_ms(200);
        // play c4
        tone(261.63, 200);
        _delay_ms(200);
        // play b3
        tone(246.94, 200);
        _delay_ms(200);
        // play a3
        tone(220, 800);
        _delay_ms(800);
    }

    return 0;
}