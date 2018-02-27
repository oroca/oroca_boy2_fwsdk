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

#include "cs43l22/cs43l22.h"

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

void audioSelectDev(uint8_t dev)
{
  drvAudioSelectOutDev(dev);
}

void audioBeep(uint8_t note, uint32_t duration_ms)
{
  drvAudioOutBeep(note, duration_ms);
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
  bool state = false;

  return state;
}




#ifdef _USE_HW_CMDIF_AUDIO

/* wav format */
uint8_t sound_demo[] = {
  0x52, 0x49, 0x46, 0x46, 0xa0, 0x04, 0x00, 0x00, 0x57, 0x41, 0x56, 0x45,
  0x66, 0x6d, 0x74, 0x20, 0x32, 0x00, 0x00, 0x00, 0x02, 0x00, 0x02, 0x00,
  0x22, 0x56, 0x00, 0x00, 0x27, 0x57, 0x00, 0x00, 0x00, 0x04, 0x04, 0x00,
  0x20, 0x00, 0xf4, 0x03, 0x07, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02,
  0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x40, 0x00, 0xf0, 0x00,
  0x00, 0x00, 0xcc, 0x01, 0x30, 0xff, 0x88, 0x01, 0x18, 0xff, 0x66, 0x61,
  0x63, 0x74, 0x04, 0x00, 0x00, 0x00, 0xa7, 0x02, 0x00, 0x00, 0x64, 0x61,
  0x74, 0x61, 0x00, 0x04, 0x00, 0x00, 0x02, 0x02, 0x28, 0x00, 0x37, 0x00,
  0x89, 0xff, 0x6f, 0x01, 0x3d, 0x01, 0x76, 0x00, 0x4e, 0x64, 0x05, 0xbf,
  0x1c, 0xc2, 0x0b, 0x70, 0x37, 0x80, 0x78, 0xe7, 0xfd, 0x50, 0xd4, 0xeb,
  0x2f, 0x22, 0x71, 0xf4, 0xed, 0xfd, 0x4e, 0x16, 0xf0, 0x0f, 0xd0, 0x4d,
  0x34, 0xc1, 0xfc, 0x20, 0x22, 0xf1, 0xcf, 0x0d, 0x20, 0x42, 0xe4, 0xed,
  0x2e, 0x02, 0x00, 0x21, 0x02, 0x2f, 0x92, 0x08, 0x00, 0xf0, 0x00, 0x00,
  0x34, 0x2e, 0x30, 0x00
};
unsigned int sound_demo_len = 1192;


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
  uint32_t pre_time;
  uint8_t out_dev = _DEF_AUDIO_HEADPHONE;

  if (argc == 2)
  {
    if(strcmp("demo", argv[1]) == 0)
    {
      pre_time = millis();

      err = audioPlay((uint16_t *)sound_demo, sound_demo_len/2);
      while(cmdifRxAvailable() == 0)
      {
        if(millis() - pre_time > 500)
        {
          pre_time = millis();
          audioStop();
          audioSelectDev(out_dev);
          err = audioPlay((uint16_t *)sound_demo, sound_demo_len/2);
          cmdifPrintf("Play : OK (errcode : %d)\r\n", err);

          if(out_dev == _DEF_AUDIO_HEADPHONE)
          {
            out_dev = _DEF_AUDIO_SPEAKER;
          }
          else
          {
            out_dev = _DEF_AUDIO_HEADPHONE;
          }
        }
      }
      audioStop();
    }
    else if(strcmp("beep", argv[1]) == 0)
    {
      uint8_t note = CS43L22_BEEP_NOTE_C4;
      pre_time = millis();

      while(cmdifRxAvailable() == 0)
      {
        if(millis() - pre_time > 1000)
        {
          pre_time = millis();
          audioSelectDev(out_dev);
          audioBeep(note++, 800);

          if(note > CS43L22_BEEP_NOTE_C7)
          {
            note = CS43L22_BEEP_NOTE_C4;
          }

          if(out_dev == _DEF_AUDIO_HEADPHONE)
          {
            out_dev = _DEF_AUDIO_SPEAKER;
          }
          else
          {
            out_dev = _DEF_AUDIO_HEADPHONE;
          }
        }
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
    cmdifPrintf( "audio demo \n");
    cmdifPrintf( "audio beep \n");
  }

  return 0;
}
#endif /* _USE_HW_CMDIF_SDRAM */



#endif /* _USE_HW_AUDIO */



