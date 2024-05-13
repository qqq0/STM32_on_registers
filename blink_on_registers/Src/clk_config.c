/*
 * clk_config.c
 *
 *  Created on: May 3, 2024
 *      Author: Mateusz
 */
#include "clk_config.h"

void clk_init(){
	RCC->CR.HSE_ON=HSE_ENABLED; // RCC_CR |= 1<<16;			//set HSE ON
	while(RCC->CR.HSE_RDY == HSE_NOT_READY); //while(!(RCC_CR & (1<<17)));	//wait for change
	FLASH->ACR.LATENCY = ACR_LATENCY_0;		//latency - zero wait (0 < sysclk <= 24MHz)
	RCC->CFGR.HPRE = HPRE_Div1;//RCC_CFGR &= ~(1<<7);		// set HPRE to no division
	RCC->CFGR.PPRE1 = PPRE_Div2; //RCC_CFGR |= 1<<10;			// set PPRE1 to div by 2 (PCLK1 8MHz)
	RCC->CFGR.PPRE2 = PPRE_Div1; //RCC_CFGR &= ~(1<<13);		// set PPRE2 to no div (PCLK2 8MHz)
	RCC->CFGR.SW = SW_HSE; //RCC_CFGR |= 1<<0; 			// set SW to HSE clk
	while(RCC->CR.HSE_RDY == HSE_NOT_READY);//while(!(RCC_CR & (1<<17)));	// wait until HSE is redy
}
