#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

uint8_t direction = 1;

void initTIMER0();
void knightRider();

int main(void)
{
    DDRB = 0xFF;
    PORTB = 0b00000010;

    sei();

    initTIMER0();

    for (;;)
        ;

    return 0;
}

void initTIMER0()
{
    TCNT0 = 6;
    TCCR0A = 0x00;
    TCCR0B = _BV(CS01) | _BV(CS00);
    TIMSK0 |= _BV(TOIE0);
}

uint8_t t_cnt = 0;

ISR(TIMER0_OVF_vect)
{
    if (t_cnt >= 200)
    {
        knightRider();
        t_cnt = 0;
    }else{
        t_cnt++;
    }

    TCNT0 = 6;
}

uint8_t pattern = 0b00000010;

void knightRider(){
    if (direction){
        pattern = pattern << 1;
    }else{
        pattern = pattern >> 1;
    }

    if (pattern == 0b00000010) direction = 1;
    if (pattern == 0b00100000) direction = 0;    

    PORTB = pattern;
}