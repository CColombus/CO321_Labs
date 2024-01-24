#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void usart_init(void);
void usart_send(unsigned char ch);
unsigned char usart_receive(void);
void usart_send_string(char *str);
void usart_receive_string(char *str);
char ceaser_cipher(char ch, int key);

void usart_init(void)
{
    UBRR0H = 0;
    UBRR0L = 103;
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
    // Write a string
    usart_init();

    usart_send_string("START....");
    char input[100], output[100];

    while (1)
    {
        usart_send_string("Enter plain text:");
        usart_receive_string(input);
        usart_send_string("Cipher text:");

        int idx = 0;
        while (input[idx] != '\0')
        {
            output[idx] = ceaser_cipher(input[idx], 3);
            idx++;
        }
        output[idx] = '\0';
        
        usart_send_string(output);
    }

    return 0;
}

// ceaser cipher function to cipher alphabetic ascii characters
char ceaser_cipher(char ch, int key)
{
    if (ch >= 'a' && ch <= 'z')
    {
        ch = ch + key;
        if (ch > 'z')
        {
            ch = ch - 'z' + 'a' - 1;
        }
        return ch;
    }
    else if (ch >= 'A' && ch <= 'Z')
    {
        ch = ch + key;
        if (ch > 'Z')
        {
            ch = ch - 'Z' + 'A' - 1;
        }
        return ch;
    }
    else
    {
        return ch;
    }
}