#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <uart.h>
#include <customKey.h>

// Timer0 setup
void Timer0_Setup(void)
{
    OCR0A = 124;
    TCNT0 = 0;
    TCCR0A = _BV(WGM01);
    TCCR0B = _BV(CS01) | _BV(CS00);
    TIMSK0 = _BV(OCIE0A);
}

int main(void)
{

    keypad_init();
    Timer0_Setup();
    sei();

    // Setup
    usart_init();

    // Loop
    while (1)
    {
        char key = getKey();
        waitKeyRelease();
        usart_send(key);
    }
}

// Timer0 interrupt service routine
ISR(TIMER0_COMPA_vect)
{
    check_key();
}