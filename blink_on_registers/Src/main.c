

#include <stdint.h>
#include "clk_config.h"
/*
 * clock enable RCC_APB2ENR 0x400021018 bit 4 -> 1 enable clock for
 * pc13 -> output GPIOC_CRH 0x40011004 bit 20 -> 0 bit 21-> 1
 * pc13-> 3.3v GPIOC_ODR 0x4001100C bit 13 -> 1
 * pc13->0v GPIOC_ODR 0x4001100C bit 13 -> 0
 */
#define RCC_APB1ENR *((uint32_t *)0x4002101C)
#define	RCC_APB2ENR *((uint32_t *)0x40021018)	//RCC_APB2ENR value of rcc_apb2enr
#define RCC_APB2ENR_IOPCEN 1<<4



#define GPIO_CRH_MONF_OUTPUT_10M_GP_PP 0x1U
#define GPIO_CRH_MONF_OUTPUT_10M_GP_OD 0x5U
#define GPIO_CRH_MONF_OUTPUT_10M_AF_PP 0x9U
#define GPIO_CRH_MONF_OUTPUT_10M_AF_OD 0xDU
#define GPIO_CRH_MONF_OUTPUT_2M_GP_PP 0x2U
#define GPIO_CRH_MONF_OUTPUT_2M_GP_OD 0x6U
#define GPIO_CRH_MONF_OUTPUT_2M_AF_PP 0xAU
#define GPIO_CRH_MONF_OUTPUT_2M_AF_OD 0xEU
#define GPIO_CRH_MONF_OUTPUT_50M_GP_PP 0x3U
#define GPIO_CRH_MONF_OUTPUT_50M_GP_OD 0x7U
#define GPIO_CRH_MONF_OUTPUT_50M_AF_PP 0xBU
#define GPIO_CRH_MONF_OUTPUT_50M_AF_OD 0xFU
#define GPIO_CRH_MONF_Float 0x4U
#define GPIO_CRH_MONF_PuPd 0x8U
#define GPIO_CRH_MONF_Analog 0x0U
#define GPIO_CRH_MONF_CNFMODE 0xFU




//GPIO register structure
typedef struct{
	uint32_t CRL;
	union{								//union for accesing CRH as a register or as struct CRH_T
		uint32_t reg;
		struct{							//struct for CRH register
			volatile uint32_t MONF8:4;
			volatile uint32_t MONF9:4;
			volatile uint32_t MONF10:4;
			volatile uint32_t MONF11:4;
			volatile uint32_t MONF12:4;
			volatile uint32_t MONF13:4;
			volatile uint32_t MONF14:4;
			volatile uint32_t MONF15:4;

		} bit;
	} CRH;

	uint32_t IDR;

	union{
		uint32_t reg;
		struct{
			volatile uint32_t PIN0:1;
			volatile uint32_t PIN1:1;
			volatile uint32_t PIN2:1;
			volatile uint32_t PIN3:1;
			volatile uint32_t PIN4:1;
			volatile uint32_t PIN5:1;
			volatile uint32_t PIN6:1;
			volatile uint32_t PIN7:1;
			volatile uint32_t PIN8:1;
			volatile uint32_t PIN9:1;
			volatile uint32_t PIN10:1;
			volatile uint32_t PIN11:1;
			volatile uint32_t PIN12:1;
			volatile uint32_t PIN13:1;
			volatile uint32_t PIN14:1;
			volatile uint32_t PIN15:1;

		}bit;
	}ODR;

	uint32_t BSRR;
	uint32_t BRR;
	uint32_t LCKR;
}GPIO_T;

#define GPIOC ((GPIO_T*)0x40011000)

typedef struct{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SMCR;
	volatile uint32_t DIER;
	volatile uint32_t SR;
	volatile uint32_t EGR;
	volatile uint32_t CCMR1;
	volatile uint32_t CCMR2;
	volatile uint32_t CCER;
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
	volatile uint32_t reserved1;
	volatile uint32_t CCR1;
	volatile uint32_t CCR2;
	volatile uint32_t CCR3;
	volatile uint32_t CCR4;
	volatile uint32_t reserved2;
	volatile uint32_t DCR;
	volatile uint32_t DMAR;
}TIM_T;

#define TIM_2 ((TIM_T*)0x40000000)


void delay_us(uint32_t time_us){
	TIM_2->CNT = 0;
	while(TIM_2->CNT < time_us);
}

void delay_ms(uint32_t time_ms){
	for(uint32_t i=0;i<time_ms;i++){
	delay_us(1000);	// delay of 1 ms
	}
}


int main(void)
{
	//clock config
	RCC_APB1ENR |= 1<<28; //enable power to clock
	clk_init();


	//timer config
	RCC_APB1ENR |= 1<<0; //set (bit 0) -> 1 to enable timer 2 clock
	TIM_2->CR1 |= (1<<0); // enable timer CEN (bit 0) -> 1
	TIM_2->PSC = 8-1; //SET to clk freq in MHz to get us ticks
	TIM_2->ARR = 0xFFFF;	//MAX ARR
	while(!(TIM_2->SR & (1<<0)));	//wait until timer setup is finished


	//GPIO config
	RCC_APB2ENR |= RCC_APB2ENR_IOPCEN;	// sets IOPCEN (bit 4) -> 1
	GPIOC->CRH.bit.MONF13 = GPIO_CRH_MONF_OUTPUT_2M_GP_PP; //crh

	//GPIOC->CRH |= (1<<21);	// CRH register sets bit 21 -> 1
	//GPIOC->CRH &= ~(1<<20); // CRH register sets bit 20 -> 0

    /* Loop forever */
	for(;;){
		delay_ms(10000);
		GPIOC->ODR.bit.PIN13 = 1;
		delay_ms(1000);
		GPIOC->ODR.bit.PIN13 = 0;
	}
}
