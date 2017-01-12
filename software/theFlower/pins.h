/*
 * pins.h
 *
 *  Created on: Apr 17, 2015
 *      Author: conut
 */

#ifndef PINS_H_
#define PINS_H_

#include <stdint.h>

typedef struct {
	volatile uint8_t bit;
	volatile uint8_t brightness;
	volatile uint8_t check_value;
	volatile uint8_t* out;
	volatile uint8_t* dir;

} pin;

#define PIN_COUNT 15
#define OFF_STATE 6

volatile pin pins[PIN_COUNT];

void pins_init();

#endif /* PINS_H_ */
