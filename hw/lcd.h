/*
 * lcd.h
 *
 *  Created on: Feb 11, 2018
 *      Author: opus
 */

#ifndef LCD_H_
#define LCD_H_

#include "hw_def.h"

#ifdef _USE_HW_LCD


bool       lcdIsInit(void);

err_code_t lcdInit(void);
void       lcdReset(void);


uint32_t   lcdReadPixel(uint16_t x_pos, uint16_t y_pos);
void       lcdDrawPixel(uint16_t x_pos, uint16_t y_pos, uint32_t rgb_code);
void       lcdClear(uint32_t rgb_code);

bool       lcdDrawAvailable(void);
void       lcdRequestDraw(void);

void       lcdDisplayOff(void);
void       lcdDisplayOn(void);

uint32_t   lcdGetWidth(void);
uint32_t   lcdGetHeight(void);


#endif /* _USE_HW_LCD */


#endif /* LCD_H_ */
