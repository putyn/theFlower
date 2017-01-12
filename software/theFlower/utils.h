/*
 * utils.h
 *
 *  Created on: Apr 17, 2015
 *      Author: conut
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <stdint.h>

volatile uint8_t _state;
volatile uint8_t _pstate;

uint8_t check_state(uint8_t in_delay);
void _delay_ms(uint16_t delay);
void fade_all(uint8_t delay);
void all(uint8_t pwm);
void chase(uint8_t delay);
void heart_beat(uint8_t delay);
void random(uint16_t rand_seed);
void up_down(uint8_t delay);
void _off();

#endif /* UTILS_H_ */
