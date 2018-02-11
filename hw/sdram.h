/*
 * sdram.h
 *
 *  Created on: Feb 10, 2018
 *      Author: opus
 */

#ifndef SDRAM_H_
#define SDRAM_H_


#include "hw_def.h"


#ifdef _USE_HW_SDRAM



err_code_t sdramInit(void);

err_code_t sdramWrite(uint32_t addr, uint32_t *p_data, uint32_t length);
err_code_t sdramRead(uint32_t addr, uint32_t *p_data, uint32_t length);



#endif /* _USE_HW_SDRAM */



#endif /* SDRAM_H_ */
