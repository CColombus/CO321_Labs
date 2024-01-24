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

void initTIMER0();
void closeTIMER0();
void knightRider();
void initINT0();
void initPWM();
void closePWM();
void initTIMER1();

// Define your global variables here
uint8_t direction = 1, pattern = 0b00000010, t_count = 0;
uint16_t fade_count = 0, fade = 0;

// Main Function
int main(void)
{
    // Set PORTB as output
    DDRB = 0XFF;
    PORTB = 0b00000010;

    // initialize TIMER0
    initTIMER0();
    // initialie External Intterupt
    initINT0();

    // Enable global intterupts
    sei();

    //infinite loop
    for (;;)
        ;

    return 0;
}

// Initialize timer0 for 1ms overflow
void initTIMER0()
{
    TCNT0 = 6;
    TCCR0A = 0x00;
    TCCR0B = _BV(CS01) | _BV(CS00);
    TIMSK0 = _BV(TOIE0);
}

// Function to Disable timer0
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
    // Calculate 200ms as 1ms * 200 using TIMER0
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

    // If we are at the either end of the paattern change directions
    if (PORTB == 0b00000010)
        direction = 1;
    if (PORTB == 0b00100000)
        direction = 0;
}

// Initialize External Innterrupt 0
void initINT0()
{
    DDRD &= ~_BV(PD2);
    EICRA |= _BV(ISC01); // on falling edge
    EIMSK |= _BV(INT0);
}

// External Intererupt 0 Service Routine
ISR(INT0_vect)
{
    // Check if TIMER0 is running
    if (TCCR0B == (_BV(CS01) | _BV(CS00)))
    {
        // if yes pause TIMER0 to pause the pattern
        closeTIMER0();
        
        //if we pause at PB3 initialize PWM on it
        if (PORTB & _BV(PB3)){
            initPWM();
        }

    }
    else
    {
        // disable PWM on PB3 (even if we didn't pause at PB3 for good measure)
        closePWM();
        // restart TIMER0 to resume pattern
        initTIMER0();
    }
}

// initialize PWM on PB3
void initPWM()
{
    DDRB |= _BV(PB3);
    TCCR2A = _BV(WGM21) | _BV(WGM20) | _BV(COM2A1);
    TCCR2B = _BV(CS22);
    OCR2A = 0;

    // TIMER1 will control the fade amount
    initTIMER1();
}

// disable PWM on PB3
void closePWM()
{
    //disable timer1 as well
    TCCR1B = 0x00;
    TIFR1 |= _BV(TOV1);
    TIMSK1 &= ~_BV(TOIE1);

    TCCR2A = 0x00;
    TCCR2B = 0x00;
    OCR2A = 0;
}

// initialize TIMER1 for 10ms
void initTIMER1()
{
    // use timer1 to get 10ms delay to update fade amount
    TCNT1 = 64911;
    TCCR1A = 0x00;
    TCCR1B = _BV(CS11) | _BV(CS10);
    TIMSK1 |= _BV(TOIE1);
}

// Control fade amount of PB3
ISR(TIMER1_OVF_vect)
{
    if (fade_count >= 400)
    {
        fade_count = 0;
    }
    else
    {
        fade_count++;
    }

    if (fade_count < 200)
    {
        fade = fade_count;
    }
    else
    {
        fade = 200 - (fade_count - 200);
    }

    OCR2A = fade;

    TCNT1 = 64911;
}