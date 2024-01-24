#include <avr/io.h>

#include "eeprom.h"

void EEPROM_write(uint16_t uiAddress, uint8_t ucData)
{
    /* Wait for completion of previous write */
    while (EECR & (1 << EEPE))
        ;
    /* Set up address and Data Registers */
    EEAR = uiAddress;
    EEDR = ucData;
    /* Write logical one to EEMPE */
    EECR |= (1 << EEMPE);
    /* Start eeprom write by setting EEPE */
    EECR |= (1 << EEPE);
}

unsigned char EEPROM_read(uint16_t uiAddress)
{
    /* Wait for completion of previous write */
    while (EECR & (1 << EEPE))
        ;
    /* Set up address register */
    EEAR = uiAddress;
    /* Start eeprom read by writing EERE */
    EECR |= (1 << EERE);
    /* Return data from Data Register */
    return EEDR;
}

void EEPROM_update(uint16_t uiAddress, uint8_t ucData)
{
    uint8_t value = 0;

    // avoid rewriting the same value to eeprom to reduce the number of write cycles
    value = EEPROM_read(uiAddress);
    if (value == ucData)
    {
        return;
    }
    else
    {
        EEPROM_write(uiAddress, ucData);
        return;
    }
}

void EEPROM_update_batch(uint16_t uiAddress, char *data, uint8_t len)
{
    // write multiple bytes to eeprom
    uint16_t i = 0;

    for (i = 0; i < len; i++)
    {
        EEPROM_update(uiAddress + i, data[i]);
    }

    return;
}

void EEPROM_read_batch(uint16_t uiAddress, char *data, uint8_t len)
{
    // read multiple bytes from eeprom
    uint16_t i = 0;

    for (i = 0; i < len; i++)
    {
        data[i] = EEPROM_read(uiAddress + i);
    }

    return;
}