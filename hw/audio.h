/*
 * audio.h
 *
 *  Created on: Feb 22, 2018
 *      Author: opus
 */

#ifndef AUDIO_H_
#define AUDIO_H_


#include "hw_def.h"


#ifdef _USE_HW_AUDIO


err_code_t audioInit(uint32_t audio_freq);
err_code_t audioStop(void);

err_code_t audioPlay(uint16_t* p_buf, uint32_t size);
err_code_t audioPause(void);
err_code_t audioResume(void);


err_code_t audioSetVol(uint8_t volume);
err_code_t audioSetMute(uint32_t on_off);

void       audioSetFreq(uint32_t audio_freq);


#endif /* _USE_HW_AUDIO */

#endif /* AUDIO_H_ */
