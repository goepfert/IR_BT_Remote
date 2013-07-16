/*****************************************************************************
 * File          : colors.c
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

#include "colors.h"

#include <math.h>
#include <stdlib.h>

void colors_gen(colors_t mode, rgb_t* rgb_color, hsv_t* hsv_color) {

	switch (mode) {
	case (RED):
		rgb_color->r = 1;
		rgb_color->g = 0;
		rgb_color->b = 0;
		break;
	case (GREEN):
		rgb_color->r = 0;
		rgb_color->g = 1;
		rgb_color->b = 0;
		break;
	case (BLUE):
		rgb_color->r = 0;
		rgb_color->g = 0;
		rgb_color->b = 1;
		break;
	case (CYAN):
		rgb_color->r = 0;
		rgb_color->g = 1;
		rgb_color->b = 1;
		break;
	case (MAGENTA):
		rgb_color->r = 1;
		rgb_color->g = 0;
		rgb_color->b = 1;
		break;
	case (YELLOW):
		rgb_color->r = 1;
		rgb_color->g = 1;
		rgb_color->b = 0;
		break;
	case (WHITE):
		rgb_color->r = 1;
		rgb_color->g = 1;
		rgb_color->b = 1;
		break;
	case (BROWN):
		rgb_color->r = 0.36;
		rgb_color->g = 0.20;
		rgb_color->b = 0.09;
		break;
	case (RANDOM):
		rgb_color->r = (rand() % 101)/100.;
		rgb_color->g = (rand() % 101)/100.;
		rgb_color->b = (rand() % 101)/100.;
		break;
	default:
		break;
	} //end switch

	*hsv_color = RgbToHsv(rgb_color);
}

void colors_toggle(colors_t mode, rgb_t* rgb_color, hsv_t* hsv_color) {

	switch (mode) {
	case (RED):
		rgb_color->r = (rgb_color->r > 0) ? 0 : 1;
		break;
	case (GREEN):
		rgb_color->g = (rgb_color->g > 0) ? 0 : 1;
		break;
	case (BLUE):
		rgb_color->b = (rgb_color->b > 0) ? 0 : 1;
		break;
	default:
		break;
	} //end switch

	*hsv_color = RgbToHsv(rgb_color);
}

hsv_t RgbToHsv(rgb_t* in) {

	hsv_t out;

	double min, max, delta;

	min = in->r < in->g ? in->r : in->g;
	min = min < in->b ? min : in->b;

	max = in->r > in->g ? in->r : in->g;
	max = max > in->b ? max : in->b;

	out.v = max;
	delta = max - min;
	if (max > 0.0) {
		out.s = (delta / max);
	} else {
		// r = g = b = 0
		out.s = 0.0;
		out.h = NAN;
		return out;
	}
	if (in->r >= max)
		out.h = (in->g - in->b) / delta;
	else if (in->g >= max)
		out.h = 2.0 + (in->b - in->r) / delta;
	else
		out.h = 4.0 + (in->r - in->g) / delta;

	out.h *= 60.0;

	if (out.h < 0.0)
		out.h += 360.0;

	return out;
}

rgb_t HsvToRgb(hsv_t* in) {
	double hh, p, q, t, ff;
	long i;
	rgb_t out;

	if (in->s <= 0.0) {
		if (isnan(in->h)) {
			out.r = in->v;
			out.g = in->v;
			out.b = in->v;
			return out;
		}
		out.r = 0.0;
		out.g = 0.0;
		out.b = 0.0;
		return out;
	}
	hh = in->h;
	if (hh >= 360.0)
		hh = 0.0;
	hh /= 60.0;
	i = (long) hh;
	ff = hh - i;
	p = in->v * (1.0 - in->s);
	q = in->v * (1.0 - (in->s * ff));
	t = in->v * (1.0 - (in->s * (1.0 - ff)));

	switch (i) {
	case 0:
		out.r = in->v;
		out.g = t;
		out.b = p;
		break;
	case 1:
		out.r = q;
		out.g = in->v;
		out.b = p;
		break;
	case 2:
		out.r = p;
		out.g = in->v;
		out.b = t;
		break;

	case 3:
		out.r = p;
		out.g = q;
		out.b = in->v;
		break;
	case 4:
		out.r = t;
		out.g = p;
		out.b = in->v;
		break;
	case 5:
	default:
		out.r = in->v;
		out.g = p;
		out.b = q;
		break;
	}
	return out;
}
