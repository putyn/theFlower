/*
 * utils.c
 *
 *  Created on: Apr 17, 2015
 *      Author: conut
 */

#include <msp430.h>
#include "rand.h"
#include "soft_pwm.h"
#include "utils.h"
#include "pins.h"

/*
 * turn the flower off
 */
void _off() {

	//stop timer_A
	TA0CCR0 = 0;
	TA0CCTL0 &= ~CCIE;
	//all outputs low
	P1OUT = 0x00;
	P2OUT = 0x00;
	P3OUT = 0x00;

	//enter deep sleep w/ interrupt
	__bis_SR_register(LPM4_bits + GIE);
}
/*
 * delay function
 */
void _delay_ms(uint16_t delay) {
	while (delay--) {
		if(check_state(1))
			break;
		__delay_cycles(8000);
	}
}
/*
 * state chage
 */
uint8_t check_state(uint8_t in_delay) {

	if(_pstate != _state) {
		if(!in_delay)
			_pstate = _state;
		return 1;
	}
	return 0;
}
/*
 * all fade in, fade out
 */
void fade_all(uint8_t delay) {
	uint8_t brightness;
	uint8_t pin;

	for (brightness = BRIGHTNESS_MIN; brightness <= BRIGHTNESS_MAX; brightness++) {
		for (pin = 0; pin < PIN_COUNT; pin++) {
			pins[pin].brightness = brightness;
		}
		_delay_ms(delay);
		if(check_state(0))
			goto end;
	}
	for (brightness = BRIGHTNESS_MAX; brightness >= BRIGHTNESS_MIN; brightness--) {
		for (pin = 0; pin < PIN_COUNT; pin++) {
			pins[pin].brightness = brightness;
		}
		_delay_ms(delay);
		if(check_state(0))
			goto end;
	}
end:
	return;
}
/*
 *  chaser back and forth
 */
void chase(uint8_t delay) {

	uint8_t pin;

	for (pin = 0; pin < PIN_COUNT-1; pin++) {
		pins[pin].brightness = BRIGHTNESS_MAX;
		_delay_ms(delay);
		if(check_state(0))
			goto end;
		pins[pin].brightness = BRIGHTNESS_MIN;
	}
	for (pin = PIN_COUNT - 1; pin > 0; pin--) {
		pins[pin].brightness = BRIGHTNESS_MAX;
		_delay_ms(delay);
		if(check_state(0))
			goto end;
		pins[pin].brightness = BRIGHTNESS_MIN;
	}
end:
	return;
}
/*
 * heart beat (delay 30mS)
 */
void heart_beat(uint8_t delay) {
	static const uint8_t heart_beat[] = { 1, 2, 2, 3, 3, 4, 5, 6, 7, 9, 10, 12, 13, 15, 17, 19, 21, 23, 25, 27, 28, 30, 31, 31, 30, 28, 27, 25, 23, 21, 19, 17, 15, 13, 12, 10, 9, 7, 6, 5, 4, 3, 3, 2, 2, 1 };
	uint8_t hb_idx = 0;
	uint8_t pin = 0;
	for (hb_idx = 0; hb_idx < sizeof(heart_beat) / sizeof(heart_beat[0]); hb_idx++) {
		for (pin = 0; pin < PIN_COUNT; pin++) {
			pins[pin].brightness = heart_beat[hb_idx];
		}
		_delay_ms(delay);
		if(check_state(0))
			goto end;
	}
end:
	return;
}

/*
 * random
 */
void random(uint16_t rand_seed) {

	uint8_t prand_seed = 0;
	uint8_t pin = 0;

	while(1) {
		prand_seed = prand(rand_seed + prand_seed);
		pin = prand_seed % PIN_COUNT;
		pins[pin].brightness = BRIGHTNESS_MAX;
		_delay_ms(300);
		if(check_state(0))
			goto end;
		pins[pin].brightness = BRIGHTNESS_MIN;
	}
end:
	return;
}

/*
 * up and down (delay 100mS)
 */
void up_down(uint8_t delay) {

	uint8_t pin;
	pins[0].brightness = BRIGHTNESS_MAX;
	_delay_ms(delay);
	pins[0].brightness = 0;
	for(pin = 1; pin < PIN_COUNT; pin++) {
		if(pin == 7)
			continue;
		pins[pin].brightness = BRIGHTNESS_MAX;
		pins[PIN_COUNT - pin].brightness = BRIGHTNESS_MAX;
		_delay_ms(delay);
		if(check_state(0))
			goto end;
		pins[pin].brightness = 0;
		pins[PIN_COUNT - pin].brightness = 0;
	}
end:
	return;
}

/*
 * all to brightness
 */
void all(uint8_t brightness) {
	uint8_t pin;
	for(pin =0; pin < PIN_COUNT; pin++)
		pins[pin].brightness = brightness;
	while(1) {
		if(check_state(0))
			goto end;
	}
end:
	return;
}
