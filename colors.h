/*****************************************************************************
 * File          : colors.h
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

#ifndef COLORS_H_
#define COLORS_H_

#include <inttypes.h>

typedef enum COLORS {
	RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW, WHITE, BROWN, RANDOM
} colors_t;

typedef struct RGB_COLOR {
	float r;
	float g;
	float b;
} rgb_t;

typedef struct HSV_COLOR {
	float h; // angle in degrees
	float s;
	float v;
} hsv_t;


void colors_gen(colors_t mode, rgb_t* rgb_color, hsv_t* hsv_color);
void colors_set(colors_t mode, rgb_t* rgb_color, hsv_t* hsv_color);

rgb_t HsvToRgb(hsv_t* hsv);
hsv_t RgbToHsv(rgb_t* rgb);

#endif /* COLORS_H_ */
