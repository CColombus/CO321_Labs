// -------------------------------------------------------------
// University of Peradeniya - Faculty of Engineering
// Mid-Semester Examination - December 2023
// CO321 Embedded Systems
// -------------------------------------------------------------
// Registration Number: E/19/057
// -------------------------------------------------------------

// Include library files here
#include <avr/io.h>
#include <avr/interrupt.h>
// #include <util/delay.h>

void initTIMER0();
void closeTIMER0();
void knightRider();
void initINT0();

// Define your global variables here
uint8_t direction = 1, pattern = 0b00000010, t_count = 0;

// Main Function
int main(void)
{

    DDRB = 0XFF;
    PORTB = 0x00;

    initTIMER0();
    initINT0();

    // Enable global intterupts
    sei();

    for (;;)
        ;

    return 0;
}

// Initialize timer0
void initTIMER0()
{
    TCNT0 = 6;
    TCCR0A = 0x00;
    TCCR0B = _BV(CS01) | _BV(CS00);
    TIMSK0 = _BV(TOIE0);
}

// Disable timer0
void closeTIMER0()
{
    TCCR0A = 0x00;
    TCCR0B = 0x00;
    TIFR0 |= _BV(TOV0);
    TIMSK0 &= ~_BV(TOIE0);
}

// Timer0 Overflow Interrupt Service Routine
ISR(TIMER0_OVF_vect)
{
    if (t_count >= 200)
    {
        t_count = 0;
        knightRider();
    }
    else
    {
        t_count++;
    }
}

// Knight Rider LED Driver
void knightRider()
{
    if (direction)
        pattern = pattern << 1;
    else
        pattern = pattern >> 1;

    PORTB = pattern;

    if (PORTB == 0b00000010)
        direction = 1;
    if (PORTB == 0b00100000)
        direction = 0;
}

// Initialize External Innterrupt 0
void initINT0()
{
    DDRD &= ~_BV(PD2);
    EICRA |= _BV(ISC01);    //on falling edge
    EIMSK |= _BV(INT0);
}

// External Intererupt 0 Service Routine
ISR(INT0_vect)
{
    if (TCCR0B == (_BV(CS01) | _BV(CS00)))
        closeTIMER0();
    else
        initTIMER0();
}