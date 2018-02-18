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

  err = drvLcdInit();

  if(err == OK)
  {
    lcd_is_init = true;
  }

#ifdef _USE_HW_CMDIF_LCD
  lcdCmdifInit();
#endif

  return err;
}


void lcdReset(void)
{
  drvLcdReset();
}


uint32_t lcdReadPixel(uint16_t x_pos, uint16_t y_pos)
{
  return drvLcdReadPixel(x_pos, y_pos);
}

void lcdDrawPixel(uint16_t x_pos, uint16_t y_pos, uint32_t rgb_code)
{
  drvLcdDrawPixel(x_pos, y_pos, rgb_code);
}




void lcdClear(uint32_t rgb_code)
{
  drvLcdClear(rgb_code);
}

bool lcdDrawAvailable(void)
{
  return drvLcdDrawAvailable();
}

void lcdRequestDraw(void)
{
  drvLcdRequestDraw();
}

void lcdDisplayOff(void)
{
  drvLcdDisplayOff();
}

void lcdDisplayOn(void)
{
  drvLcdDisplayOn();
}


uint32_t lcdGetWidth(void)
{
  return drvLcdGetWidth();
}

uint32_t lcdGetHeight(void)
{
  return drvLcdGetHeight();
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
      uint16_t color = 0;

      x_mid = lcdGetWidth()/2;
      y_mid = lcdGetHeight()/2;


      while(cmdifRxAvailable() == 0)
      {
        if(lcdDrawAvailable())
        {
          cmdifPrintf("time : %d us\n", micros()-pre_time);

          pre_time = micros();
          lcdClear(LCD_COLOR_WHITE);

          //drvLcdFillRect(x_mid - 50, y_mid - 50, 100, 100, LCD_COLOR_BLUE);

          /* Draw rectangle */
          for(i = x_mid-50; i < x_mid+50; i++)
          {
            for(j = y_mid-50; j < y_mid+50; j++)
            {
              if (j < y_mid)
              {
                lcdDrawPixel(i, j, LCD_COLOR_RED);
              }
              else
              {
                lcdDrawPixel(i, j, LCD_COLOR_BLUE);
              }
            }
          }

          lcdRequestDraw();

          if(y_mid >= lcdGetHeight() - 55)
          {
            y_dir = 0;
          }

          if(y_mid - 50 <= 5)
          {
            y_dir = 1;
          }

          if(x_mid >= lcdGetWidth() - 55)
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
        }
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
