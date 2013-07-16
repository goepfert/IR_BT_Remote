/*****************************************************************************
* File          : pwm.c
* Created       : Apr 7, 2013
* 
* Title         : ---
* Author        : goepfert
* Contact       : info@SolderLab.de
* 
* Version       : 1.0
* Last Changed  : Apr 7, 2013 by goepfert
* Remarks       : ---
*
* Description   : ---
*
*****************************************************************************/

#include "pwm.h"
#include "uart.h"
#include "BTData.h"

void pwm_init() {

	// FastPWM
	//TCCR0A |= (1 << WGM00 | 1 << WGM01);
	//TCCR2A |= (1 << WGM20 | 1 << WGM21);

	// Phase corrected PWM
	// problems with fastPWM 0% duty cycle is _not_ off
	TCCR0A |= (1 << WGM00);
	TCCR2A |= (1 << WGM20);

	// Set clock source (prescaler)
	TCCR0B |= (1 << CS01);
	TCCR2B |= (1 << CS21);

	// 4 PWM channel outputs
	DDRB |= 1 << PB3; // OC2A
	DDRD |= 1 << PD3; // OC2B
	DDRD |= 1 << PD5; // OC0B
	DDRD |= 1 << PD6; // OC0A

	pwm_disable_all();

	pwm_setdutycycle(CHAN_RED, 0);
	pwm_setdutycycle(CHAN_GREEN, 0);
	pwm_setdutycycle(CHAN_BLUE, 0);
	pwm_setdutycycle(CHAN_WHITE, 0);

	pwm_status = POWER_OFF;
}


// Enable PWM channels
void pwm_enable(pwm_channel_t channel) {
	if (channel & CHAN_OC0A)
		TCCR0A |= 1 << COM0A1;
	if (channel & CHAN_OC0B)
		TCCR0A |= 1 << COM0B1;
	if (channel & CHAN_OC2A)
		TCCR2A |= 1 << COM2A1;
	if (channel & CHAN_OC2B)
		TCCR2A |= 1 << COM2B1;
}


// Enable PWM channels
void pwm_enable_all() {
	pwm_enable(CHAN_RED);
	pwm_enable(CHAN_GREEN);
	pwm_enable(CHAN_BLUE);
	pwm_enable(CHAN_WHITE);

	pwm_status = POWER_ON;
}

// Disable PWM channels
void pwm_disable(pwm_channel_t channel) {
	if (channel & CHAN_OC0A)
		TCCR0A &= ~(1 << COM0A1);
	if (channel & CHAN_OC0B)
		TCCR0A &= ~(1 << COM0B1);
	if (channel & CHAN_OC2A)
		TCCR2A &= ~(1 << COM2A1);
	if (channel & CHAN_OC2B)
		TCCR2A &= ~(1 << COM2B1);
}


// Disable PWM channels
void pwm_disable_all() {
	pwm_disable(CHAN_RED);
	pwm_disable(CHAN_GREEN);
	pwm_disable(CHAN_BLUE);
	pwm_disable(CHAN_WHITE);

	pwm_status = POWER_OFF;
}


// Sets the channel brightness
void pwm_setdutycycle(pwm_channel_t channel, uint8_t dutycycle) {
	if (channel & CHAN_OC0A)
		OCR0A = dutycycle;
	if (channel & CHAN_OC0B)
		OCR0B = dutycycle;
	if (channel & CHAN_OC2A)
		OCR2A = dutycycle;
	if (channel & CHAN_OC2B)
		OCR2B = dutycycle;
}


uint8_t pwm_getdutycycle(pwm_channel_t channel) {
	uint8_t ret = 0;

	if (channel & CHAN_OC0A)
		ret = OCR0A;
	if (channel & CHAN_OC0B)
		ret = OCR0B;
	if (channel & CHAN_OC2A)
		ret = OCR2A;
	if (channel & CHAN_OC2B)
		ret = OCR2B;

	return ret;
}


void pwm_toggle(pwm_channel_t channel) {
	if (channel & CHAN_OC0A)
		TCCR0A ^= (1 << COM0A1);
	if (channel & CHAN_OC0B)
		TCCR0A ^= (1 << COM0B1);
	if (channel & CHAN_OC2A)
		TCCR2A ^= (1 << COM2A1);
	if (channel & CHAN_OC2B)
		TCCR2A ^= (1 << COM2B1);
}


