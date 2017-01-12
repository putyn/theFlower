/*
 * soft_pwm.c
 *
 *  Created on: Apr 17, 2015
 *      Author: conut
 */

#include <msp430.h>
#include <stdint.h>
#include "pins.h"
#include "soft_pwm.h"


volatile uint8_t _soft_pwm = 0;

void soft_pwm_init(void) {

	TA0CCR0 = 250;						//~60Hz
	TA0CCTL0 = CCIE;                    //enable CCR0 interrupt
	TA0CTL = TASSEL_2 | ID_1 | MC_1;    //timer_A config: SCLK, /2, count up to CCR0
}

#pragma vector = TIMER0_A0_VECTOR       // timer_a CCR0 interrupt, used for soft pwm
__interrupt void soft_pwm_isr(void) {

	uint8_t soft_pwm_ch = 0;

	if (_soft_pwm == 0) {
		for (soft_pwm_ch = 0; soft_pwm_ch < PIN_COUNT; soft_pwm_ch++) {

			pins[soft_pwm_ch].check_value = cie1931[pins[soft_pwm_ch].brightness];
			if (pins[soft_pwm_ch].check_value > 0) {
				*pins[soft_pwm_ch].out |= pins[soft_pwm_ch].bit;
			}
		}
	}
	for (soft_pwm_ch = 0; soft_pwm_ch < PIN_COUNT; soft_pwm_ch++) {

		if (pins[soft_pwm_ch].check_value == _soft_pwm) {
			*pins[soft_pwm_ch].out &= ~pins[soft_pwm_ch].bit;
		}
	}
	_soft_pwm++;
}
