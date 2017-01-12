/*
 * pins.c
 *
 *  Created on: Apr 17, 2015
 *      Author: conut
 */

#include <msp430.h>
#include <stdint.h>
#include "pins.h"
#include "soft_pwm.h"
#include "utils.h"

void pins_init() {

	//P1 --> BIT0: input w/ pulldown, rest output low, enable interrupt on BIT0 on rising edge
	P1DIR = 0xFE;
	P1OUT = 0x00;
	P1REN = 0x01;
	P1IE |= BIT0;
	P1IES &= ~BIT0;
	P1IFG &= ~BIT0;

	//P2 --> all outputs, all low
	P2DIR = 0xFF;
	P2OUT = 0x00;

	//P3 --> all outputs, all low
	P3DIR = 0xFF;
	P3OUT = 0x00;

	//LED1 on pin P1.BIT2
	pins[0].bit = BIT2;
	pins[0].out = &P1OUT;
	pins[0].brightness = 0;

	//LED2 on pin P1.BIT3
	pins[1].bit = BIT3;
	pins[1].out = &P1OUT;
	pins[1].brightness = 0;

	//LED3 on pin P1.BIT4
	pins[2].bit = BIT4;
	pins[2].out = &P1OUT;
	pins[2].brightness = 0;

	//LED4 on pin P1.BIT5
	pins[3].bit = BIT5;
	pins[3].out = &P1OUT;
	pins[3].brightness = 0;

	//LED5 on pin P3.BIT1
	pins[4].bit = BIT1;
	pins[4].out = &P3OUT;
	pins[4].brightness = 0;

	//LED6 on pin P3.BIT0
	pins[5].bit = BIT0;
	pins[5].out = &P3OUT;
	pins[5].brightness = 0;

	//LED7 on pin P2.BIT0
	pins[6].bit = BIT0;
	pins[6].out = &P2OUT;
	pins[6].brightness = 0;

	//LED8 on pin P2.BIT1
	pins[7].bit = BIT1;
	pins[7].out = &P2OUT;
	pins[7].brightness = 0;

	//LED9 on pin P2.BIT2
	pins[8].bit = BIT2;
	pins[8].out = &P2OUT;
	pins[8].brightness = 0;

	//LED10 on pin P3.BIT2
	pins[9].bit = BIT2;
	pins[9].out = &P3OUT;
	pins[9].brightness = 0;

	//LED11 on pin P3.BIT3
	pins[10].bit = BIT3;
	pins[10].out = &P3OUT;
	pins[10].brightness = 0;

	//LED12 on pin P3.BIT7
	pins[11].bit = BIT7;
	pins[11].out = &P3OUT;
	pins[11].brightness = 0;

	//LED13 on pin P1.BIT6
	pins[12].bit = BIT6;
	pins[12].out = &P1OUT;
	pins[12].brightness = 0;

	//LED14 on pin P1.BIT7
	pins[13].bit = BIT7;
	pins[13].out = &P1OUT;
	pins[13].brightness = 0;

	//LED15 on pin P1.BIT1
	pins[14].bit = BIT1;
	pins[14].out = &P1OUT;
	pins[14].brightness = 0;
}

#pragma vector=PORT1_VECTOR
__interrupt void port1_isr(void) {

	_state++;
	if (_state == (OFF_STATE + 1))
		_state = 0;
	//wake up
	if(_state == 0 && _pstate == OFF_STATE) {
		__bic_SR_register_on_exit(LPM4_bits);
		soft_pwm_init();
	}
	//since we were lazy (ab)use WDT for button debounce
	P1IE &= ~BIT0;
	WDTCTL = WDT_MDLY_32; //if using the DCO at 1MHz this will overflow once every ~32mS
	IE1 |= WDTIE;
	IFG1 &= ~WDTIFG;
}

volatile uint8_t wdt_isr_cnt = 0;
#pragma vector=WDT_VECTOR
__interrupt void wdt_isr(void) {

	wdt_isr_cnt++;
	if (wdt_isr_cnt == 60) {
		wdt_isr_cnt = 0;
		WDTCTL = WDTPW | WDTHOLD;
		P1IE |= BIT0;
		//go to sleep
		if (_state == OFF_STATE && _pstate == OFF_STATE)
			_off();
	}
	P1IFG &= ~BIT0;
	IFG1 &= ~WDTIFG;
}
