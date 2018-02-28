/*
 * adc.h
 *
 *  Created on: 2017. 2. 13.
 *      Author: baram
 */

#ifndef ADC_H_
#define ADC_H_



#ifdef __cplusplus
 extern "C" {
#endif

#include "hw_def.h"

#ifdef _USE_HW_ADC




bool adcInit(void);

uint16_t adcRead(uint8_t ch);
uint16_t adcRead8(uint8_t ch);
uint16_t adcRead10(uint8_t ch);
uint16_t adcRead12(uint8_t ch);
uint16_t adcRead16(uint8_t ch);
uint16_t adcReadVoltage(uint8_t ch);
uint16_t adcConvVoltage(uint8_t ch, uint32_t adc_value);

uint8_t  adcGetRes(uint8_t ch);

#endif /* _USE_HW_ADC */

#ifdef __cplusplus
}
#endif


#endif /* ADC_H_ */
