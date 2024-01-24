#include <avr/io.h>
#include <util/delay.h>

void initPWM();

int main(void)
{
    initPWM();  // Initialize PWM

    while (1)
    {
    }

    return 0;
}

void initPWM()
{
    DDRD |= (1 << PD6); // Enable PWM output on OC0A

    // 50% duty cycle is not enough to make a noticeable difference in brightness
    // 7.8% duty cycle is more noticeable
    OCR0A = 20; // Duty Cycle of 7.8%

    // 976.56 Hz = 16MHz/(64 * 256)
    // thus we need a prescale of 64
    // Non-inverting FastPWM at OCRA with a pre-scale of /64
    TCCR0A |= (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);
    TCCR0B |= (0 << WGM02) | (1 << CS01) | (1 << CS00);
}