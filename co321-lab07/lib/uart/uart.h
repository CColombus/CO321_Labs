#ifndef UART_H
#define UART_H

void usart_init(void);
void usart_send(unsigned char ch);
unsigned char usart_receive(void);
void usart_send_string(char *str);
void usart_receive_string(char *str);

#endif