/*****************************************************************************
 * File          : main.c
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

#include "irmp.h"
#include "pwm.h"
#include "colors.h"
#include "uart.h"
#include "helper.h"
#include "BTData.h"

#include <inttypes.h>
#include <string.h>

#define DEBUGLED 0,C

volatile uint32_t millis = 0;
volatile uint8_t comp = 0;
uint32_t last_millis = 0;

int16_t duration = 750;

rgb_t rgb_color;
hsv_t hsv_color;
uint8_t white_value = 0;

data_t bt_data;

typedef enum ACTION {
	NONE, HUE_FADE
} action_t;

action_t action = NONE;

void checkIR(IRMP_DATA *irmp_data);
void checkBT();
void sendDataBT();
void change_hue(float val);
void change_saturation(float val);
void change_value(float val);
void updateChannels();
void update_color();
void change_white(int16_t val);
void bt_init();
void timer1_init(void);


int main(void) {

	out(DEBUGLED);
    for(uint8_t i=0; i<5; i++) {
       toggle(DEBUGLED);
       _delay_ms(100);
    }
    off(DEBUGLED);

	bt_init();
	irmp_init();
	timer1_init();
	pwm_init();

	IRMP_DATA irmp_data;
	sei();

	// polling mode
	while(1) {
		checkIR(&irmp_data);
		checkBT();
	}
}//end main

void checkIR(IRMP_DATA *irmp_data) {

	if (irmp_get_data(irmp_data)) {

		if (pwm_status == POWER_OFF && irmp_data->command != 1)
			return;

		if (!(irmp_data->flags & IRMP_FLAG_REPETITION)) {

			switch (irmp_data->command) {

			case (1):
			if (pwm_status == POWER_ON) {
				pwm_disable_all();
				off(DEBUGLED);
			} else {
				pwm_enable_all();
				on(DEBUGLED);
			}
			action = NONE;
			break;

			case (30):
			change_white(1);
			break;

			case (36):
			change_white(-1);
			break;

			case (4):
			change_white(-255);
			break;

			case (14):
			rgb_color.r=0; rgb_color.g=0; rgb_color.b=0;
			hsv_color = RgbToHsv(&rgb_color);
			update_color();
			break;

			case (40):
			change_hue(5.);
			action = NONE;
			break;

			case (41):
			change_hue(-5.);
			action = NONE;
			break;

			case (44):
			change_saturation(0.1);
			action = NONE;
			break;

			case (45):
			change_saturation(-0.1);
			action = NONE;
			break;

			case (9):
			change_value(0.1);
			action = NONE;
			break;

			case (5):
			change_value(-0.1);
			action = NONE;
			break;

			case (7):
			duration += 10;
			break;

			case (8):
			duration -= 10;
			break;

			case (16):
			colors_gen(RED, &rgb_color, &hsv_color);
			update_color();
			action = NONE;
			break;
			case (17):
			colors_gen(GREEN, &rgb_color, &hsv_color);
			update_color();
			action = NONE;
			break;
			case (18):
			colors_gen(BLUE, &rgb_color, &hsv_color);
			update_color();
			action = NONE;
			break;
			case (19):
			colors_gen(CYAN, &rgb_color, &hsv_color);
			update_color();
			action = NONE;
			break;
			case (20):
			colors_gen(MAGENTA, &rgb_color, &hsv_color);
			update_color();
			action = NONE;
			break;
			case (21):
			colors_gen(YELLOW, &rgb_color, &hsv_color);
			update_color();
			action = NONE;
			break;
			case (22):
			colors_gen(WHITE, &rgb_color, &hsv_color);
			update_color();
			action = NONE;
			break;
			case (23):
			colors_gen(BROWN, &rgb_color, &hsv_color);
			update_color();
			action = NONE;
			break;
			case (24):
			colors_gen(RANDOM, &rgb_color, &hsv_color);
			update_color();
			action = NONE;
			break;

			case (15):
			action = (action == HUE_FADE) ? NONE : HUE_FADE;
			break;

			default:
				break;
			}
		} else {
			switch (irmp_data->command) { // if you press the button longer
			case (30):
			change_white(5);
			break;
			case (36):
			change_white(-5);
			break;
			case (40):
			change_hue(0.5);
			break;
			case (41):
			change_hue(-0.5);
			break;
			case (44):
			change_saturation(0.01);
			break;
			case (45):
			change_saturation(-0.01);
			break;
			case (9):
			change_value(0.01);
			break;
			case (5):
			change_value(-0.01);
			break;
			case (7):
			duration += 5;
			break;
			case (8):
			duration -= 5;
			break;
			default:
				break;
			}
		}
	} //end remote switch

	switch (action) {
		case (HUE_FADE):
   			if (duration <= 0)
    				duration = 0;
			if ((millis - last_millis) > duration) {
				change_hue(1.);
				last_millis = millis;
			}
		break;

		default:
		break;
	} // action switch
}

void checkBT() {

	if(readBTPackage()) {

		data_type = data_buffer[TYPE_POS];

		switch(data_type) {
		case(DATA):
    		pwm_status = data_buffer[STATUS_POS];
			memcpy(&bt_data, &data_buffer[DATA_POS], DATA_LENGTH);
			updateChannels();
		break;
		case(RA):
   			sendDataBT();
        break;

		default:
			break;
		}
	}

}

void sendDataBT() {

	data_buffer[TYPE_POS] = AW;
	data_buffer[STATUS_POS] = pwm_status;
	bt_data.red = rgb_color.r * 254.;
	bt_data.green = rgb_color.g * 254.;
	bt_data.blue = rgb_color.b * 254.;
	bt_data.white = white_value;

	memcpy(&data_buffer[DATA_POS], &bt_data, DATA_LENGTH);

	uart_putc(START_BYTE);
	for(uint8_t i=0; i<DATA_BUFFER_LENGTH; i++){
		uart_putc(data_buffer[i]);
	}
}

void updateChannels() {

	if(pwm_status==POWER_ON) {
		pwm_enable_all();
		on(DEBUGLED);
	} else if (pwm_status==POWER_OFF){
		pwm_disable_all();
		off(DEBUGLED);
		return;
	}

	rgb_color.r = (float) (bt_data.red) / 255.;
	rgb_color.g = (float) (bt_data.green) / 255.;
	rgb_color.b = (float)(bt_data.blue) / 255.;
	white_value = (uint8_t)(bt_data.white);

	update_color();
	pwm_setdutycycle(CHAN_WHITE, white_value);
}

void change_hue(float val) {

	float tmp = hsv_color.h + val;

	if (tmp > 360) {
		tmp -= 360.;
	} else if (tmp < 0) {
		tmp = 360. - fabs(tmp);
	}

	hsv_color.h = tmp;
	rgb_color = HsvToRgb(&hsv_color);
	update_color();
}

void change_saturation(float val) {

	float tmp = hsv_color.s + val;

	if (tmp > 1.0)
		tmp = 1.;
	if (tmp < 0.)
		tmp = 0.001;

	hsv_color.s = tmp;
	rgb_color = HsvToRgb(&hsv_color);

	update_color();
}

void change_value(float val) {

	float tmp = hsv_color.v + val;

	if (tmp > 1.0)
		tmp = 1.;
	if (tmp < 0.)
		tmp = 0.;

	hsv_color.v = tmp;
	rgb_color = HsvToRgb(&hsv_color);

	update_color();
}

void update_color() {
	pwm_setdutycycle(CHAN_RED, (uint8_t) (rgb_color.r * 254 + 0.5));
	pwm_setdutycycle(CHAN_GREEN, (uint8_t) (rgb_color.g * 254 + 0.5));
	pwm_setdutycycle(CHAN_BLUE, (uint8_t) (rgb_color.b * 254 + 0.5));
}

void change_white(int16_t inc) {

	int16_t tmp = white_value + inc;

	if(tmp > 255)
		tmp = 255;
	if(tmp < 0)
		tmp = 0;

	white_value = tmp;
	pwm_setdutycycle(CHAN_WHITE, white_value);
}

void bt_init() {
	uart_init(38400);
}

void timer1_init(void) {

	OCR1A = (F_CPU / F_INTERRUPTS) - 1;   // compare value: 1/15000 of CPU frequency
	TIMSK1 |= (1 << OCIE1A);              // OCIE1A: Interrupt by timer compare
	TCCR1B = (1 << WGM12) | (1 << CS10);  // switch CTC Mode on, set prescaler to 1
}

ISR(TIMER1_COMPA_vect) {
	comp++;
	if (!(comp % F_INTERRUPTS / 1000)) {
		millis++;
		comp = 0;
	}
	irmp_ISR();
}

