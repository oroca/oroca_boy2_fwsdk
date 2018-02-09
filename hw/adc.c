/*
 * adc.c
 *
 *  Created on: 2017. 2. 13.
 *      Author: baram
 */

#include "adc.h"

#ifdef _USE_HW_ADC

#include "driver/drv_adc.h"
#include "hw.h"

//-- Internal Variables
//

//-- External Variables
//

//-- Internal Functions
//
static void adcCmdifInit(void);
static int adcCmdif(int argc, char **argv);

//-- External Functions
//

bool adcInit(void)
{
  drvAdcInit();

#ifdef _USE_HW_CMDIF_ADC
  adcCmdifInit();
#endif

  return true;
}

uint16_t adcRead(uint8_t ch)
{
  return drvAdcRead(ch);
}

uint16_t adcRead8(uint8_t ch)
{
  return drvAdcRead8(ch);
}

uint16_t adcRead10(uint8_t ch)
{
  return drvAdcRead10(ch);
}

uint16_t adcRead12(uint8_t ch)
{
  return drvAdcRead12(ch);
}

uint16_t adcRead16(uint8_t ch)
{
  return drvAdcRead16(ch);
}

uint8_t adcGetRes(uint8_t ch)
{
  return drvAdcGetRes(ch);
}

uint16_t adcReadVoltage(uint8_t ch)
{
  return drvAdcReadVoltage(ch);
}

uint16_t adcConvVoltage(uint8_t ch, uint32_t adc_value)
{
  return drvAdcConvVoltage(ch, adc_value);
}

#ifdef _USE_HW_CMDIF_ADC
void adcCmdifInit(void)
{
  if (cmdifIsInit() == false)
  {
    cmdifInit();
  }
  cmdifAdd("adc", adcCmdif);
}

int adcCmdif(int argc, char **argv)
{
  bool ret = true;
  uint8_t print_ch;
  uint8_t ch;

  if (argc < 3)
  {
    ret = false;
  }
  else
  {
    print_ch = (uint8_t) strtoul((const char *) argv[2], (char **) NULL,
        (int) 0);
    ch = print_ch - 1;

    if (strcmp("get", argv[1]) == 0)
    {
      while (cmdifRxAvailable() == 0)
      {
        uint16_t adc_value;

        adc_value = adcRead(ch);
        cmdifPrintf("%d ADC : %d %d.%d V\n", print_ch, adc_value,
            adcConvVoltage(ch, adc_value) / 100,
            adcConvVoltage(ch, adc_value) % 100);
        delay(50);
      }
    }
    else
    {
      ret = false;
    }
  }

  if (ret == false)
  {
    cmdifPrintf("adc get channel(1~%d) \n", ADC_MAX_CH);
  }

  return 0;
}

#endif /* _USE_HW_CMDIF_ADC */

#endif /* _USE_HW_ADC */

