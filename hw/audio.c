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


err_code_t audioInit(uint32_t audio_freq)
{
  err_code_t err;

  err = drvAudioOutInit(audio_freq);

  return err;
}


err_code_t audioPlay(uint16_t* p_buf, uint32_t size)
{
  //drvAudioOutPlay();
}

err_code_t audioStop(void)
{
  drvAudioOutStop();
}

err_code_t audioPause(void);
err_code_t audioResume(void);

err_code_t audioSetVol(uint8_t volume);
err_code_t audioSetMute(uint32_t on_off);

void       audioSetFreq(uint32_t audio_freq);






#endif /* _USE_HW_AUDIO */



