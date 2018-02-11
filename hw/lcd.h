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


err_code_t  lcdInit(void);
err_code_t  lcdInitEx(uint8_t orientation);

void     lcdReset(void);

uint32_t lcdGetXSize(void);
uint32_t lcdGetYSize(void);
void     lcdSetXSize(uint32_t image_width_pixels);
void     lcdSetYSize(uint32_t image_height_pixels);

void     lcdInitLayerDefault(uint16_t layer, uint32_t fb_addr);
void     lcdSetTransparency(uint32_t layer_idx, uint8_t transparency);
void     lcdSetLayerAddr(uint32_t layer_idx, uint32_t addr);
void     lcdSetColorKeying(uint32_t layer_idx, uint32_t rgb_value);
void     lcdResetColorKeying(uint32_t layer_idx);
void     lcdSetLayerWindow(uint16_t layer_idx, uint16_t x_pos, uint16_t y_pos, uint16_t width, uint16_t height);

void     lcdSelectLayer(uint32_t layer_idx);
void     lcdSetLayerVisible(uint32_t layer_idx, uint8_t state);

void     lcdSetTextColor(uint32_t color);
uint32_t lcdGetTextColor(void);
void     lcdSetBackColor(uint32_t color);
uint32_t lcdGetBackColor(void);
void     lcdSetFont(uint8_t font_type);

uint32_t lcdReadPixel(uint16_t x_pos, uint16_t y_pos);
void     lcdDrawPixel(uint16_t x_pos, uint16_t y_pos, uint32_t rgb_code);
void     lcdClear(uint32_t color);
void     lcdClearStringLine(uint32_t line);
void     lcdDisplayStringAtLine(uint16_t line, uint8_t *ptr);
void     lcdDisplayStringAt(uint16_t x_pos, uint16_t y_pos, uint8_t *p_text, uint8_t align);
void     lcdDisplayChar(uint16_t x_pos, uint16_t y_pos, uint8_t ascii);

void     lcdDrawHLine(uint16_t x_pos, uint16_t y_pos, uint16_t length);
void     lcdDrawVLine(uint16_t x_pos, uint16_t y_pos, uint16_t length);
void     lcdDrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void     lcdDrawRect(uint16_t x_pos, uint16_t y_pos, uint16_t width, uint16_t height);
void     lcdDrawCircle(uint16_t x_pos, uint16_t y_pos, uint16_t radius);
void     lcdDrawPolygon(p_pixel points, uint16_t point_cnt);
void     lcdDrawEllipse(int32_t x_pos, int32_t y_pos, int32_t x_rad, int32_t y_rad);
void     lcdDrawBitmap(uint32_t x_pos, uint32_t y_pos, uint8_t *pbmp);

void     lcdFillRect(uint16_t x_pos, uint16_t y_pos, uint16_t width, uint16_t height);
void     lcdFillCircle(uint16_t x_pos, uint16_t y_pos, uint16_t radius);
void     lcdFillPolygon(p_pixel points, uint16_t point_cnt);
void     lcdFillEllipse(int32_t x_pos, int32_t y_pos, int32_t x_rad, int32_t y_rad);

void     lcdDisplayOff(void);
void     lcdDisplayOn(void);



#endif /* _USE_HW_LCD */


#endif /* LCD_H_ */
