/*
 * soft_pwm.h
 *
 *  Created on: Apr 17, 2015
 *      Author: conut
 */

#ifndef SOFT_PWM_H_
#define SOFT_PWM_H_

#include <msp430.h>
#include <stdint.h>

#define BRIGHTNESS_MIN 1
#define BRIGHTNESS_MAX 31

void soft_pwm_init(void);
/*
 * brightness correction https://ledshield.wordpress.com/2012/11/13/led-brightness-to-your-eye-gamma-correction-no/
 */
static const uint8_t cie1931[] = {0, 1, 2, 3, 4, 5, 7, 9, 12, 15, 18, 22, 27, 32, 38, 44, 51, 58, 67, 76, 86, 96, 108, 120, 134, 148, 163, 180, 197, 216, 235, 255};
#endif /* SOFT_PWM_H_ */
