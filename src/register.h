/**
 * @file register.h
 */

#ifndef REGISTER_H_
#define REGISTER_H_

/**
 * Writes data to 16-bit register
 * @param adress - adress of register where data has to be saved
 * @param value  - value of data
 */
void register_16_write(volatile uint16_t* adress, uint16_t value);

#endif
