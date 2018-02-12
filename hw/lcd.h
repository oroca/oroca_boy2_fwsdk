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

typedef enum {
  FONT8 = 0,
  FONT12,
  FONT16,
  FONT20,
  FONT24
} font_type_t;


bool lcdIsInit(void);

err_code_t lcdInit(void);
err_code_t lcdInitEx(uint8_t orientation);
void       lcdReset(void);

void       lcdInitLayer(uint16_t layer, uint32_t fb_addr);
void       lcdSelectLayer(uint32_t layer_idx);

uint32_t   lcdReadPixel(uint16_t x_pos, uint16_t y_pos);
void       lcdDrawPixel(uint16_t x_pos, uint16_t y_pos, uint32_t rgb_code);
void       lcdClear(uint32_t color);

void       lcdSetTransparency(uint32_t layer_idx, uint8_t transparency);
void       lcdSetLayerAddr(uint32_t layer_idx, uint32_t addr);
void       lcdSetLayerWindow(uint16_t layer_idx, uint16_t x_pos, uint16_t y_pos, uint16_t width, uint16_t height);
void       lcdSetLayerVisible(uint32_t layer_idx, uint8_t state);

void       lcdDisplayOff(void);
void       lcdDisplayOn(void);

uint32_t   lcdGetXSize(void);
uint32_t   lcdGetYSize(void);
void       lcdSetXSize(uint32_t image_width_pixels);
void       lcdSetYSize(uint32_t image_height_pixels);


#endif /* _USE_HW_LCD */


#endif /* LCD_H_ */
