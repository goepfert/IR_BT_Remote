/*****************************************************************************
* File          : pwm.h
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

#ifndef PWM_H_
#define PWM_H_

#include <inttypes.h>


typedef enum PWM_CHANNEL {
	// Name by color
	CHAN_RED   = 1,
	CHAN_GREEN = 1 << 1,
	CHAN_BLUE  = 1 << 2,
	CHAN_WHITE = 1 << 3,
	// Name by index
	CHAN_0 = 1,
	CHAN_1 = 1 << 1,
	CHAN_2 = 1 << 2,
	CHAN_3 = 1 << 3,
	// Name by port
	CHAN_PB3 = 1,
	CHAN_PD3 = 1 << 1,
	CHAN_PD6 = 1 << 2,
	CHAN_PD5 = 1 << 3,
	// Name by register
	CHAN_OC2A = 1,
	CHAN_OC2B = 1 << 1,
	CHAN_OC0A = 1 << 2,
	CHAN_OC0B = 1 << 3,
} pwm_channel_t;

extern void pwm_init();
extern void pwm_enable(pwm_channel_t channel);
extern void pwm_enable_all();
extern void pwm_disable(pwm_channel_t channel);
extern void pwm_disable_all();
extern void pwm_toggle(pwm_channel_t channel);
extern void pwm_setdutycycle(pwm_channel_t channel, uint8_t dutycycle);
extern uint8_t pwm_getdutycycle(pwm_channel_t channel);


#endif /* PWM_H_ */
