#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void initTIMER0();

int main(void)
{

    DDRB = 0XFF;
    PORTB = 0x00;


    for (;;)
        ;

    return 0;
}

uint8_t pattern = 0b00000010;

void initTIMER0(){
    TCNT0 = 0;
    TCCR0A = 0x00;
    TCCR0B = _BV()
}



