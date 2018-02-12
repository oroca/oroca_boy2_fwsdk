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

static bool lcd_is_init = false;

bool lcdIsInit(void)
{
  return lcd_is_init;
}

err_code_t  lcdInit(void)
{
  err_code_t err;

  err = lcdInitEx(_DEF_LADSCAPE);

  if(err == OK)
  {
    lcd_is_init = true;
  }

#ifdef _USE_HW_CMDIF_LCD
  lcdCmdifInit();
#endif

  return err;
}

err_code_t  lcdInitEx(uint8_t orientation)
{
  err_code_t err;

  err = drvLcdInit(orientation);

  if(err == OK)
  {
    drvLcdInitLayer(LTDC_ACTIVE_LAYER_FOREGROUND, LCD_FB_START_ADDRESS);
    drvLcdInitLayer(LTDC_ACTIVE_LAYER_BACKGROUND, LCD_FB_START_ADDRESS + LCD_ADDRESS_LENGTH/2);
  }

  return err;
}

void lcdReset(void)
{
  drvLcdReset();
}


void lcdInitLayer(uint16_t layer, uint32_t fb_addr)
{
  drvLcdInitLayer(layer, fb_addr);
}

void lcdSelectLayer(uint32_t layer_idx)
{
  drvLcdSelectLayer(layer_idx);
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



void lcdSetTransparency(uint32_t layer_idx, uint8_t transparency)
{
  drvLcdSetTransparency(layer_idx, transparency);
}

void lcdSetLayerAddr(uint32_t layer_idx, uint32_t addr)
{
  drvLcdSetLayerAddr(layer_idx, addr);
}

void lcdSetLayerWindow(uint16_t layer_idx, uint16_t x_pos, uint16_t y_pos, uint16_t width, uint16_t height)
{
  drvLcdSetLayerWindow(layer_idx, x_pos, y_pos, width, height);
}

void lcdSetLayerVisible(uint32_t layer_idx, uint8_t state)
{
  drvLcdSetLayerVisible(layer_idx, state);
}



void lcdDisplayOff(void)
{
  drvLcdDisplayOff();
}

void lcdDisplayOn(void)
{
  drvLcdDisplayOn();
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


#ifdef _USE_HW_CMDIF_LCD




void lcdCmdifInit(void)
{
  if (cmdifIsInit() == false)
  {
    cmdifInit();
  }
  cmdifAdd("lcd", lcdCmdif);
}

extern void drvLcdCopyLayer(uint32_t src_index, uint32_t dst_index);

int lcdCmdif(int argc, char **argv)
{
  bool ret = true;
  err_code_t err_code;
  uint32_t time_pre;
  uint32_t time_process;
  uint32_t i, j;

  if ((argc == 2)&&(strcmp("demo", argv[1]) == 0))
  {
    if(lcdIsInit() == true)
    {
      uint32_t x_mid, y_mid;
      bool dir = 1;
      uint32_t pre_time;

      x_mid = lcdGetXSize()/2;
      y_mid = lcdGetYSize()/2;

      lcdSelectLayer(_DEF_LCD_LAYER1);
      lcdClear(LCD_COLOR_WHITE);
      lcdSetLayerVisible(_DEF_LCD_LAYER2, _DEF_DISABLE);
      lcdSetLayerVisible(_DEF_LCD_LAYER1, _DEF_ENABLE);

      lcdSelectLayer(_DEF_LCD_LAYER2);
      while(cmdifRxAvailable() == 0)
      {

        pre_time = micros();
        lcdClear(LCD_COLOR_WHITE);

        /* Draw rectangle */
        for(i = x_mid-50; i < x_mid+50; i++)
        {
          for(j = y_mid-50; j < y_mid+150; j++)
          {
            lcdDrawPixel(i, j, LCD_COLOR_BLUE);
            //lcdDrawPixel(i, j, LCD_COLOR_RED);
            //lcdDrawPixel(i, j, LCD_COLOR_BROWN);
          }
        }

        drvLcdCopyLayer(_DEF_LCD_LAYER2, _DEF_LCD_LAYER1);

        if(y_mid >= lcdGetYSize() - 70)
        {
          dir = 0;
        }

        if(y_mid - 50 <= 20)
        {
          dir = 1;
        }

        if(dir)
        {
          x_mid += 5;
          y_mid += 5;
        }
        else
        {
          x_mid -= 5;
          y_mid -= 5;
        }
        cmdifPrintf("time : %d us\n", micros()-pre_time);
        delay(10);
      }

      lcdClear(LCD_COLOR_WHITE);
    }
    else
    {
      cmdifPrintf("lcd init failed \n");
    }
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
