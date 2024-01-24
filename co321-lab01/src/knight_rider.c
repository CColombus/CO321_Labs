#include <avr/io.h>
#include <util/delay.h>

int main(void){

    DDRB = DDRB | 0x3F;

    while (1)
    {
        for (int i = 0; i < 8; i++)
        {
            if (i<4)
            {
                PORTB = (0x01<<i);
                _delay_ms(200);
            }else
            {
                PORTB = (0x80>>i);
                _delay_ms(200);               
            }
            
        }
    }
    

    return 0;
}