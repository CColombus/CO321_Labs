#include <avr/io.h>
#include <util/delay.h>

#define blink_delay 10

void initPWM();
uint8_t dutycycle = 0;

int main(void)
{
    initPWM();

    while (1)
    {   
        // increase duty cycle from 0% to 50%
        while (dutycycle < 128)
        {
            dutycycle++;
            OCR0A = dutycycle; // set duty cycle
            _delay_ms(blink_delay);
        }

        // decrease duty cycle from 50% to 0%
        while (dutycycle > 0)
        {
            dutycycle--;
            OCR0A = dutycycle;  // set duty cycle
            _delay_ms(blink_delay);
        }
    }

    return 0;
}

void initPWM()
{
    DDRD |= (1 << PD6); // Enable PWM output on OC0A

    OCR0A = 0; // Duty Cycle of 0%

    // Non-inverting FastPWM at OCRA with a pre-scale of /64
    TCCR0A |= (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);
    TCCR0B |= (0 << WGM02) | (1 << CS01) | (1 << CS00);
}