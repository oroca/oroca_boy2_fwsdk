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
    drvLcdInitLayer(_DEF_LCD_LAYER1, _HW_DEF_LCD_ADDR_LAYER1_START);
    drvLcdInitLayer(_DEF_LCD_LAYER2, _HW_DEF_LCD_ADDR_LAYER2_START);


    lcdSelectLayer(_DEF_LCD_LAYER2);
    lcdClear(LCD_COLOR_BLACK);
    lcdSelectLayer(_DEF_LCD_LAYER1);
    lcdClear(LCD_COLOR_BLACK);

    lcdSetLayerVisible(_DEF_LCD_LAYER2, _DEF_DISABLE);
    lcdSetLayerVisible(_DEF_LCD_LAYER1, _DEF_ENABLE);

    lcdSelectLayer(_DEF_LCD_LAYER2);

    lcd_is_init = true;
  }

  return err;
}

void lcdReset(void)
{
  drvLcdReset();
}


err_code_t lcdInitLayer(uint16_t layer_idx, uint32_t fb_addr)
{
  return drvLcdInitLayer(layer_idx, fb_addr);
}

err_code_t lcdSelectLayer(uint32_t layer_idx)
{
  return drvLcdSelectLayer(layer_idx);
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

void lcdCopyLayer(uint32_t src_index, uint32_t dst_index)
{
  drvLcdCopyLayer(src_index, dst_index);
}


err_code_t lcdSetTransparency(uint32_t layer_idx, uint8_t transparency)
{
  return drvLcdSetTransparency(layer_idx, transparency);
}

err_code_t lcdSetLayerAddr(uint32_t layer_idx, uint32_t addr)
{
  return drvLcdSetLayerAddr(layer_idx, addr);
}

err_code_t lcdSetLayerWindow(uint16_t layer_idx, uint16_t x_pos, uint16_t y_pos, uint16_t width, uint16_t height)
{
  return drvLcdSetLayerWindow(layer_idx, x_pos, y_pos, width, height);
}

err_code_t lcdSetLayerVisible(uint32_t layer_idx, uint8_t state)
{
  return drvLcdSetLayerVisible(layer_idx, state);
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
      bool x_dir = 1, y_dir = 1;
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
          for(j = y_mid-50; j < y_mid+50; j++)
          {
            lcdDrawPixel(i, j, LCD_COLOR_BLUE);
            //lcdDrawPixel(i, j, LCD_COLOR_RED);
            //lcdDrawPixel(i, j, LCD_COLOR_BROWN);
          }
        }

        lcdCopyLayer(_DEF_LCD_LAYER2, _DEF_LCD_LAYER1);

        if(y_mid >= lcdGetYSize() - 55)
        {
          y_dir = 0;
        }

        if(y_mid - 50 <= 5)
        {
          y_dir = 1;
        }

        if(x_mid >= lcdGetXSize() - 55)
        {
          x_dir = 0;
        }

        if(x_mid - 50 <= 5)
        {
          x_dir = 1;
        }

        if(y_dir)
        {
          y_mid += 5;
        }
        else
        {
          y_mid -= 5;
        }

        if(x_dir)
        {
          x_mid += 5;
        }
        else
        {
          x_mid -= 5;
        }

        cmdifPrintf("time : %d us\n", micros()-pre_time);
        delay(10);
      }

      lcdClear(LCD_COLOR_WHITE);
      lcdCopyLayer(_DEF_LCD_LAYER2, _DEF_LCD_LAYER1);
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
