/**
 * Library for seting up clock
 * prepared for STM32F103xx
 */
#include <stdint.h>

#define RCC_ADDR 0x40021000
#define FLASH_ADDR 0x40022000

#define HSE_ENABLED 1
#define HSE_DISABLED 0
#define HSE_REDY 1
#define HSE_NOT_READY 0

#define HPRE_Div1 0b000
#define HPRE_Div2 0b1000
#define HPRE_Div4 0b1001
#define HPRE_Div8 0b1010
#define HPRE_Div16 0b1011
#define HPRE_Div64 0b1100
#define HPRE_Div128 0b1101
#define HPRE_Div256 0b1110
#define HPRE_Div512 0b1111

#define PPRE_Div1 0b000
#define PPRE_Div2 0b100
#define PPRE_Div4 0b101
#define PPRE_Div8 0b110
#define PPRE_Div16 0b111

#define SW_HSI 0b00
#define SW_HSE 0b01
#define SW_PLL 0b10

#define ACR_LATENCY_0 0b000	//sys  0 < clk <= 24 MHz
#define ACR_LATENCY_1 0b001 //sys  24 < clk <= 48 MHz
#define ACR_LATENCY_2 0b010 //sys  48 < clk <= 72 MHz
/* struct for RCC registers */
typedef struct{

	/* union for accesing CR register and its bits*/
	union{
		uint32_t reg;
		struct{
			volatile uint32_t HSION:1;
			volatile uint32_t HSI_RDY:1;
			volatile uint32_t reserved1:1;
			volatile uint32_t HYSITRIM:5;
			volatile uint32_t HSICAL:8;
			volatile uint32_t HSE_ON:1;
			volatile uint32_t HSE_RDY:1;
			volatile uint32_t HSE_BYP:1;
			volatile uint32_t CSS_ON:1;
			volatile uint32_t reserved21:4;
			volatile uint32_t PLL_ON:1;
			volatile uint32_t PLLRDY:1;
			volatile uint32_t reserved3:6;
		};
	}CR;

	/* union for accesing CFGR register and its bits*/
	union{
		uint32_t reg;
		struct{
			volatile uint32_t SW:2;
			volatile uint32_t SWS:2;
			volatile uint32_t HPRE:4;
			volatile uint32_t PPRE1:3;
			volatile uint32_t PPRE2:3;
			volatile uint32_t ADCPRE:2;
			volatile uint32_t PLL_SCR:1;
			volatile uint32_t PLL_XTRPRE:1;
			volatile uint32_t PLLMUL:4;
			volatile uint32_t USBPRE:1;
			volatile uint32_t reserved1;
			volatile uint32_t MCO:3;
			volatile uint32_t reserved2:5;
		};
	}CFGR;

}RCC_T;

typedef struct{
	/* union for accesing ACR register and its bits*/
	union{
		uint32_t reg;
		struct{
			volatile uint32_t LATENCY:3;
			volatile uint32_t HLFCYA:1;
			volatile uint32_t PRFTBE:1;
			volatile uint32_t PRFTBS:1;
			volatile uint32_t reserved:26;
		};
	}ACR;
}FLASH_T;

#define RCC ((RCC_T *)RCC_ADDR)
#define FLASH ((FLASH_T *)FLASH_ADDR)


void clk_init();
