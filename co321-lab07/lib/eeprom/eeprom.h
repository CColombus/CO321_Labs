#include <stdint.h>
#ifndef EEPROM_H
#define EEPROM_H

void EEPROM_write(uint16_t uiAddress, uint8_t ucData);
unsigned char EEPROM_read(uint16_t uiAddress);
void EEPROM_update(uint16_t uiAddress, uint8_t ucData);
void EEPROM_update_batch(uint16_t uiAddress, char *data, uint8_t len);
void EEPROM_read_batch(uint16_t uiAddress, char *data, uint8_t len);

#endif