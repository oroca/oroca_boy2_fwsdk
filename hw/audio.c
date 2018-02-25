/*
 * audio.c
 *
 *  Created on: Feb 22, 2018
 *      Author: opus
 */



#include "audio.h"

#ifdef _USE_HW_AUDIO

#include "hw.h"
#include "driver/drv_audio.h"


#ifdef _USE_HW_CMDIF_SDRAM
void audioCmdifInit(void);
int  audioCmdif(int argc, char **argv);
#endif

static bool is_audio_init = false;

err_code_t audioInit(uint32_t audio_freq)
{
  err_code_t err;

  err = drvAudioOutInit(audio_freq);

  if(err == OK)
  {
    is_audio_init = true;
#ifdef _USE_HW_CMDIF_SDRAM
    audioCmdifInit();
#endif
  }

  return err;
}


err_code_t audioPlay(uint16_t* p_buf, uint32_t size)
{
  err_code_t err;

  err = drvAudioOutPlay(p_buf, size);

  return err;
}

err_code_t audioStop(void)
{
  err_code_t err;

  err = drvAudioOutStop();

  return err;
}

err_code_t audioPause(void)
{
  err_code_t err;

  err = drvAudioOutPause();

  return err;
}

err_code_t audioResume(void)
{
  err_code_t err;

  err = drvAudioOutResume();

  return err;
}

err_code_t audioSetVol(uint8_t volume)
{
  err_code_t err;

  err = drvAudioOutSetVolume(volume);

  return err;
}

err_code_t audioSetMute(uint32_t on_off)
{
  err_code_t err;

  err = drvAudioOutSetMute(on_off);

  return err;
}

// TODO : Add function to check mute state
bool audioIsMute(void)
{

}




#ifdef _USE_HW_CMDIF_AUDIO

uint16_t ok_pattern[] =     {0x0005, 0x0138, 0x0168, 0x0000};
uint16_t cancel_pattern[] = {0x0005, 0x0168, 0x0138, 0x0000};
uint16_t tick_pattern[] =   {0x0045, 0x0168, 0x0000};

void audioCmdifInit(void)
{
  if (cmdifIsInit() == false)
  {
    cmdifInit();
  }
  cmdifAdd("audio", audioCmdif);
}

int audioCmdif(int argc, char **argv)
{
  bool ret = true;
  err_code_t err;

  if ((argc == 2)&&(strcmp("demo", argv[1]) == 0))
  {
    while(cmdifRxAvailable() == 0)
    {
      err = audioPlay(ok_pattern, 4);
      cmdifPrintf("Play : OK (errcode : %d)\r\n", err);
      delay(500);
      err = audioPlay(cancel_pattern, 4);
      cmdifPrintf("Play : Cancel (errcode : %d)\r\n", err);
      delay(500);
      err = audioPlay(tick_pattern, 3);
      cmdifPrintf("Play : Tick (errcode : %d)\r\n", err);
      delay(500);
    }
  }
  else
  {
    ret = false;
  }

  if (ret == false)
  {
    cmdifPrintf( "audio demo \n");
  }

  return 0;
}
#endif /* _USE_HW_CMDIF_SDRAM */



#endif /* _USE_HW_AUDIO */



