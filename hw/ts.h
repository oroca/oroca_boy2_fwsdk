/*
 * ts.h
 *
 *  Created on: Feb 13, 2018
 *      Author: opus
 */

#ifndef TS_H_
#define TS_H_

#include "hw_def.h"

#ifdef _USE_HW_TS


err_code_t tsInit(void);

err_code_t tsResetTouchData(void);
err_code_t tsUpdateTouchData(void);

uint8_t tsIsDetected(void);

uint16_t tsGetXAxis(uint8_t detect_num);
uint16_t tsGetYAxis(uint8_t detect_num);

uint8_t tsGetWeight(uint8_t detect_num);
touch_event_t tsGetEventId(uint8_t detect_num);
uint8_t tsGetArea(uint8_t detect_num);
touch_gesture_t tsGetGestureId(void);

err_code_t tsExtiConfig(void);



#endif /* _USE_HW_TS */


#endif /* TS_H_ */
