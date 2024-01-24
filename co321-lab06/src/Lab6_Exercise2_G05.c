#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void usart_init(void);
void usart_send(unsigned char ch);
unsigned char usart_receive(void);
void usart_send_string(char *str);
void usart_receive_string(char *str);

void usart_init(void)
{
    UBRR0H = 0;
    UBRR0L = 103;                           // 9600 baud rate
    UCSR0A = 0;                             // Normal speed
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);   // Enable receiver and transmitter
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // Asynchronous //Parity Disable //1 stop bit //8 bit character size
}

void usart_send(unsigned char ch)
{
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = ch;
}

unsigned char usart_receive(void)
{
    while (!(UCSR0A & (1 << RXC0)))
        ;
    return UDR0;
}

void usart_send_string(char *str)
{
    int i = 0;
    while (str[i] != 0)
    {
        usart_send(str[i]);
        i++;
    }
    usart_send('\n');
}

void usart_receive_string(char *input)
{
    char rec_char = '\0';
    int idx = 0;

    while (rec_char != '\n')
    {
        rec_char = usart_receive();
        input[idx] = rec_char;
        idx++;
    }

    rec_char = '\0';
    input[idx] = rec_char;
    idx = 0;
}

int main(void)
{
    usart_init();

    usart_send_string("START....\n");

    while (1)
    {
        usart_send_string("E/19/057 C.O. Colombage");
        usart_send_string("E/19/060 S. Danujan");
        usart_send_string("E/19/063 S. Dissanayake");

        usart_send('\n');

        _delay_ms(1000);
    }

    return 0;
}