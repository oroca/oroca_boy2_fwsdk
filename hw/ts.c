/*
 * ts.c
 *
 *  Created on: Feb 13, 2018
 *      Author: opus
 */


#include "ts.h"


#ifdef _USE_HW_TS

#include "hw.h"
#include "driver/drv_ts.h"

#ifdef _USE_HW_CMDIF_TS
void tsCmdifInit(void);
int  tsCmdif(int argc, char **argv);
#endif

#ifdef _USE_HW_RTOS
static void tsUpdateTask( void const * argument );
#endif

static bool ts_is_init = false;

bool tsIsInit(void)
{
  return ts_is_init;
}

err_code_t tsInit(void)
{
  err_code_t err;

  err = drvTsInit(800, 480);

  if(err == OK)
  {
    ts_is_init = true;

#ifdef _USE_HW_RTOS
    osThreadDef(touchScreen, tsUpdateTask, osPriorityAboveNormal, 0, 1024/4);
    osThreadCreate(osThread(touchScreen), NULL);
#endif
#ifdef _USE_HW_CMDIF_TS
    tsCmdifInit();
#endif
  }

  return err;
}

err_code_t tsUpdateTouchData(void)
{
  err_code_t err;

  err = drvTsUpdateTouchData();

  return err;
}

err_code_t tsResetTouchData(void)
{
  err_code_t err;

  err = drvTsResetTouchData();

  return err;
}

uint8_t tsIsDetected(void)
{
  return drvTsIsDetected();
}

uint16_t tsGetXAxis(uint8_t detect_num)
{
  return drvTsGetXAxis(detect_num);
}

uint16_t tsGetYAxis(uint8_t detect_num)
{
  return drvTsGetYAxis(detect_num);
}

uint8_t tsGetWeight(uint8_t detect_num)
{
  return drvTsGetWeight(detect_num);
}

touch_event_t tsGetEventId(uint8_t detect_num)
{
  return drvTsGetEventId(detect_num);
}

uint8_t tsGetArea(uint8_t detect_num)
{
  return drvTsGetArea(detect_num);
}

touch_gesture_t tsGetGestureId(void)
{
  return drvTsGetGestureId();
}

err_code_t tsExtiConfig(void)
{
  err_code_t err;

  err = drvTsExtiConfig();

  return err;
}


static void tsUpdateTask( void const * argument )
{
  UNUSED(argument);

  if(tsIsInit() == false)
  {
    for( ;; )
    {
      delay(1);
    }
  }

  for( ;; )
  {
    tsUpdateTouchData();
    delay(20);
  }
}


#ifdef _USE_HW_CMDIF_TS
void tsCmdifInit(void)
{
  if (cmdifIsInit() == false)
  {
    cmdifInit();
  }
  cmdifAdd("ts", tsCmdif);
}

int tsCmdif(int argc, char **argv)
{
  bool ret = true;
  uint32_t detect_cnt;
  err_code_t err_code;
  uint32_t i;

  if ((argc == 3)&&(strcmp("demo", argv[1]) == 0))
  {
    if (strcmp("info", argv[2]) == 0)
    {
      while(cmdifRxAvailable() == 0)
      {
        detect_cnt = tsIsDetected();

        if(detect_cnt > 0)
        {
          cmdifPrintf("Detect count : %d, GestureId : %d\r\n", detect_cnt, tsGetGestureId());

          for(i = 0; i < detect_cnt; i++)
          {
            cmdifPrintf("X : %d, Y : %d, Wg : %d, EvId : %d, Area : %d \r\n",
                tsGetXAxis(i), tsGetYAxis(i), tsGetWeight(i), tsGetEventId(i), tsGetArea(i));
          }
        }
      }
    }
    else if(strcmp("lcd", argv[2]) == 0)
    {
      uint16_t x_axis, y_axis;
      uint32_t j;

      lcdSelectLayer(_DEF_LCD_LAYER1);
      lcdClear(0xFFFF);
      lcdSetLayerVisible(_DEF_LCD_LAYER2, _DEF_DISABLE);
      lcdSetLayerVisible(_DEF_LCD_LAYER1, _DEF_ENABLE);

      while(cmdifRxAvailable() == 0)
      {
        detect_cnt = tsIsDetected();

        if(detect_cnt > 0)
        {
          for(i = 0; i < detect_cnt; i++)
          {
            cmdifPrintf("X : %d, Y : %d \r\n", tsGetXAxis(i), tsGetYAxis(i));
          }
        }

        if(detect_cnt == 1)
        {
          x_axis = tsGetXAxis(0);
          y_axis = tsGetYAxis(0);

          for(i = 0; i < 10; i++)
          {
            for(j = 0; j < 10; j++)
            {
              lcdDrawPixel(x_axis + i, y_axis + j, 0x4439);
            }
          }
        }

        if(detect_cnt == 2)
        {
          lcdClear(0xFFFF);
        }
      }
      lcdClear(0xFFFF);
    }
    else
    {
      ret = false;
    }
  }
  else
  {
    ret = false;
  }

  if (ret == false)
  {
    cmdifPrintf( "ts demo [lcd|info]\n");
  }

  return 0;
}
#endif /* _USE_HW_CMDIF_TS */






#endif /* _USE_HW_TS */
