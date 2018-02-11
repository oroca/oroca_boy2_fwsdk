/*
 * sdram.c
 *
 *  Created on: Feb 10, 2018
 *      Author: opus
 */


#include "sdram.h"


#ifdef _USE_HW_SDRAM

#include "hw.h"
#include "driver/drv_sdram.h"

#ifdef _USE_HW_CMDIF_SDRAM
void sdramCmdifInit(void);
int  sdramCmdif(int argc, char **argv);
#endif



err_code_t sdramInit(void)
{
  err_code_t err;

  err = drvSdramInit();

#ifdef _USE_HW_CMDIF_SDRAM
  sdramCmdifInit();
#endif

  return err;
}

err_code_t sdramWrite(uint32_t addr, uint32_t *p_data, uint32_t length)
{
  err_code_t err;

  err = drvSdramWriteData(addr, p_data, length);

  return err;
}

err_code_t sdramRead(uint32_t addr, uint32_t *p_data, uint32_t length)
{
  err_code_t err;

  err = drvSdramReadData(addr, p_data, length);

  return err;
}


#ifdef _USE_HW_CMDIF_SDRAM
void sdramCmdifInit(void)
{
  if (cmdifIsInit() == false)
  {
    cmdifInit();
  }
  cmdifAdd("sdram", sdramCmdif);
}

int sdramCmdif(int argc, char **argv)
{
  bool ret = true;
  uint32_t addr;
  uint32_t length;
  err_code_t err_code;
  uint32_t time_pre;
  uint32_t time_process;
  uint32_t data[256];
  uint32_t i;


  if (argc == 4)
  {
    addr   = (uint32_t) strtoul((const char * ) argv[2], (char **)NULL, (int) 0);
    length = (uint32_t) strtoul((const char * ) argv[3], (char **)NULL, (int) 0);

    if(strcmp("write", argv[1]) == 0)
    {
      if (addr%4 != 0)
      {
        cmdifPrintf("addr not aligned 4bytes \n");
      }
      else
      {
        data[0] = length;
        time_pre = micros();
        err_code = sdramWrite(addr, data, 1);
        time_process = micros()-time_pre;
        cmdifPrintf("flashWrite : %d, %dus\n", err_code, time_process);
      }
    }
    else if(strcmp("read", argv[1]) == 0)
    {
      if (addr%4 != 0)
      {
        cmdifPrintf("addr not aligned 4bytes \n");
      }
      else
      {
        if(length > 256)
        {
          length = 256;
        }
        time_pre = micros();
        err_code = sdramRead(addr, data, length);
        time_process = micros()-time_pre;
        cmdifPrintf("flashRead : %d, %dus\n", err_code, time_process);
        for(i = 0; i < length; i++)
        {
          if((i > 0)&&(i%10 == 0))
          {
            cmdifPrintf("\r\n");
          }
          cmdifPrintf("%04X ", data[i]);
        }
        cmdifPrintf("\r\n");
      }
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
    cmdifPrintf( "flash erase addr length \n");
    cmdifPrintf( "flash write addr data   \n");
  }

  return 0;
}
#endif /* _USE_HW_CMDIF_SDRAM */


#endif /* _USE_HW_SDRAM */
