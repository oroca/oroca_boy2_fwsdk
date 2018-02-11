/*
 * lcd.c
 *
 *  Created on: Feb 11, 2018
 *      Author: opus
 */


#include "lcd.h"


#ifdef _USE_HW_LCD

#include "hw.h"
#include "driver/drv_lcd.h"

#ifdef _USE_HW_CMDIF_LCD
void lcdCmdifInit(void);
int  lcdCmdif(int argc, char **argv);
#endif



err_code_t  lcdInit(void)
{
  err_code_t err;

  err = lcdInitEx(_DEF_LADSCAPE);

#ifdef _USE_HW_CMDIF_LCD
  lcdCmdifInit();
#endif

  return err;
}

err_code_t  lcdInitEx(uint8_t orientation)
{
  err_code_t err;

  err = drvLcdInit(orientation);

  return err;
}

void lcdReset(void)
{
  drvLcdReset();
}

uint32_t lcdGetXSize(void)
{
  return drvLcdGetXSize();
}

uint32_t lcdGetYSize(void)
{
  return drvLcdGetYSize();
}

void lcdSetXSize(uint32_t image_width_pixels)
{
  drvLcdSetXSize(image_width_pixels);
}

void lcdSetYSize(uint32_t image_height_pixels)
{
  drvLcdSetYSize(image_height_pixels);
}

void lcdInitLayerDefault(uint16_t layer, uint32_t fb_addr)
{
  drvLcdInitLayerDefault(layer, fb_addr);
}

void lcdSetTransparency(uint32_t layer_idx, uint8_t transparency)
{
  drvLcdSetTransparency(layer_idx, transparency);
}

void lcdSetLayerAddr(uint32_t layer_idx, uint32_t addr)
{
  drvLcdSetLayerAddr(layer_idx, addr);
}

void lcdSetColorKeying(uint32_t layer_idx, uint32_t rgb_value)
{
  drvLcdSetColorKeying(layer_idx, rgb_value);
}

void lcdResetColorKeying(uint32_t layer_idx)
{
  drvLcdResetColorKeying(layer_idx);
}

void lcdSetLayerWindow(uint16_t layer_idx, uint16_t x_pos, uint16_t y_pos, uint16_t width, uint16_t height)
{
  drvLcdSetLayerWindow(layer_idx, x_pos, y_pos, width, height);
}

void lcdSelectLayer(uint32_t layer_idx)
{
  drvLcdSelectLayer(layer_idx);
}

void lcdSetLayerVisible(uint32_t layer_idx, uint8_t state)
{
  drvLcdSetLayerVisible(layer_idx, state);
}

void lcdSetTextColor(uint32_t color)
{
  drvLcdSetTextColor(color);
}

uint32_t lcdGetTextColor(void)
{
  return drvLcdGetTextColor();
}

void lcdSetBackColor(uint32_t color)
{
  drvLcdSetBackColor(color);
}

uint32_t lcdGetBackColor(void)
{
  return drvLcdGetBackColor();
}

void lcdSetFont(uint8_t font_type)
{
  drvLcdSetFont(font_type);
}

uint32_t lcdReadPixel(uint16_t x_pos, uint16_t y_pos)
{
  return drvLcdReadPixel(x_pos, y_pos);
}

void lcdDrawPixel(uint16_t x_pos, uint16_t y_pos, uint32_t rgb_code)
{
  drvLcdDrawPixel(x_pos, y_pos, rgb_code);
}

void lcdClear(uint32_t color)
{
  drvLcdClear(color);
}

void lcdClearStringLine(uint32_t line)
{
  drvLcdClearStringLine(line);
}

void lcdDisplayStringAtLine(uint16_t line, uint8_t *ptr)
{
  drvLcdDisplayStringAtLine(line, ptr);
}

void lcdDisplayStringAt(uint16_t x_pos, uint16_t y_pos, uint8_t *p_text, uint8_t align)
{
  drvLcdDisplayStringAt(x_pos, y_pos, p_text, align);
}

void lcdDisplayChar(uint16_t x_pos, uint16_t y_pos, uint8_t ascii)
{
  drvLcdDisplayChar(x_pos, y_pos, ascii);
}

void lcdDrawHLine(uint16_t x_pos, uint16_t y_pos, uint16_t length)
{
  drvLcdDrawHLine(x_pos, y_pos, length);
}

void lcdDrawVLine(uint16_t x_pos, uint16_t y_pos, uint16_t length)
{
  drvLcdDrawVLine(x_pos, y_pos, length);
}

void lcdDrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
  drvLcdDrawLine(x1, y1, x2, y2);
}

void lcdDrawRect(uint16_t x_pos, uint16_t y_pos, uint16_t width, uint16_t height)
{
  drvLcdDrawRect(x_pos, y_pos, width, height);
}

void lcdDrawCircle(uint16_t x_pos, uint16_t y_pos, uint16_t radius)
{
  drvLcdDrawCircle(x_pos, y_pos, radius);
}

void lcdDrawPolygon(p_pixel points, uint16_t point_cnt)
{
  drvLcdDrawPolygon(points, point_cnt);
}

void lcdDrawEllipse(int32_t x_pos, int32_t y_pos, int32_t x_rad, int32_t y_rad)
{
  drvLcdDrawEllipse(x_pos, y_pos, x_rad, y_rad);
}
void lcdDrawBitmap(uint32_t x_pos, uint32_t y_pos, uint8_t *pbmp)
{
  drvLcdDrawBitmap(x_pos, y_pos, pbmp);
}

void lcdFillRect(uint16_t x_pos, uint16_t y_pos, uint16_t width, uint16_t height)
{
  drvLcdFillRect(x_pos, y_pos, width, height);
}

void lcdFillCircle(uint16_t x_pos, uint16_t y_pos, uint16_t radius)
{
  drvLcdFillCircle(x_pos, y_pos, radius);
}

void lcdFillPolygon(p_pixel points, uint16_t point_cnt)
{
  drvLcdFillPolygon(points, point_cnt);
}

void lcdFillEllipse(int32_t x_pos, int32_t y_pos, int32_t x_rad, int32_t y_rad)
{
  drvLcdFillEllipse(x_pos, y_pos, x_rad, y_rad);
}

void lcdDisplayOff(void)
{
  drvLcdDisplayOff();
}

void lcdDisplayOn(void)
{
  drvLcdDisplayOn();
}


#ifdef _USE_HW_CMDIF_LCD




void lcdCmdifInit(void)
{
  if (cmdifIsInit() == false)
  {
    cmdifInit();
  }
  cmdifAdd("lcd", lcdCmdif);
}

int lcdCmdif(int argc, char **argv)
{
  bool ret = true;
  uint32_t addr;
  uint32_t length;
  err_code_t err_code;
  uint32_t time_pre;
  uint32_t time_process;
  uint32_t data[256];
  uint32_t i;


  if ((argc == 2)&&(strcmp("demo", argv[1]) == 0))
  {

  }
  else
  {
    ret = false;
  }

  if (ret == false)
  {
    cmdifPrintf( "lcd demo \n");
  }

  return 0;
}




#endif /* _USE_HW_CMDIF_LCD */



#endif /* _USE_HW_LCD */
