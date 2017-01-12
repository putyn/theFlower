#include <msp430.h>
#include <stdint.h>

#include "rand.h"
#include "pins.h"
#include "utils.h"
#include "soft_pwm.h"

/*
 * main.c
 */
int main(void) {

	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

	const uint16_t rand_seed = rand();

	DCOCTL = 0;
	BCSCTL1 = CALBC1_8MHZ;
	DCOCTL = CALDCO_8MHZ;

	//initialize pins
	pins_init();
	//provides 32 levels of pwm for each led
	soft_pwm_init();

	//enable interupts
	__bis_SR_register(GIE);

	_state = _pstate = 0;

	while (1) {
		switch (_state) {
		case 0:
			heart_beat(30);
			break;
		case 1:
			chase(75);
			break;
		case 2:
			fade_all(50);
			break;
		case 3:
			random(rand_seed);
		case 4:
			up_down(100);
			break;
		case 5:
			all(16);
			break;
		}
	}
}
