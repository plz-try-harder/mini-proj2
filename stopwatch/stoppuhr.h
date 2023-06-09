#ifndef THEREALHELLOWORLD_SYSCFG_H
#define THEREALHELLOWORLD_SYSCFG_H
#include <stdint.h>

//*******************************************************//

typedef struct
{

	uint32_t memrmp;
	uint32_t cfgr1;
	uint32_t exticr1;
	uint32_t exticr2;
	uint32_t exticr3;
	uint32_t exticr4;
	uint32_t scsr;
	uint32_t cfgr2;
	uint32_t swpr;
} SYSCFG_TypeDef;



#define SYSCFG_BASE 0x40010000

#define SYSCFG (SYSCFG_TypeDef *) SYSCFG_BASE
#endif

//********************************************************//

#ifndef THEREALHELLOWORLD_GPIO_H
#define THEREALHELLOWORLD_GPIO_H
#include <stdint.h>

typedef struct {
	uint32_t moder;
	uint32_t otyper;
	uint32_t ospeedr;
	uint32_t pupdr;
	uint32_t idr;
	uint32_t odr;
	uint32_t bsrr;
	uint32_t lckr;
	uint32_t afrl;
	uint32_t afrh;
	uint32_t brr;
} GPIO_TypeDef;



#define GPIOA_BASE 0x48000000
#define GPIOB_BASE 0x48000400
#define GPIOC_BASE 0x48000800
#define GPIOH_BASE 0x48001C00

#define GPIOA (GPIO_TypeDef *) GPIOA_BASE
#define GPIOB (GPIO_TypeDef *) GPIOB_BASE

#endif





#ifndef THEREALHELLOWORLD_STK_H
#define THEREALHELLOWORLD_STK_H

#include <stdint.h>

typedef struct {
	uint32_t ctrl;	// RW	
	uint32_t load;	// RW
	uint32_t val;	// RW
	uint32_t calib;	// RO
} STK_TypeDef;

#define STK_BASE 0xE000E010	//from PM S.246: STK
#define STK (STK_TypeDef *) STK_BASE

#endif

//****************************************************************//

#ifndef THEREALHELLOWORLD_RCC_H
#define THEREALHELLOWORLD_RCC_H

#include <stdint.h>
// from RM page.244 table nr. 32
typedef struct {	
	
	uint32_t cr;	
	uint32_t icsrc;
	uint32_t cfgr;
	uint32_t pllcfgr;
	uint32_t pllsai1cfgr;
	uint32_t unused1;
	uint32_t cier;
	uint32_t cifr;
	uint32_t cicr;
	uint32_t unused2;
	uint32_t ahb1rstr;
	uint32_t ahb2rstr;
	uint32_t ahb3rstr;
	uint32_t unused3;
	uint32_t apb1rstr1;
	uint32_t apb1rstr2;
	uint32_t apb2rstr;
	uint32_t unused4;
	uint32_t ahb1enr;
	uint32_t ahb2enr;
	uint32_t ahb3enr;
	uint32_t unused5;
	uint32_t apb1enr1;
	uint32_t apb1enr2;
	uint32_t apb2enr;
	uint32_t unused6;
	uint32_t ahb1smenr;
	uint32_t ahb2smenr;
	uint32_t ahb3smenr;
	uint32_t unused7;
	uint32_t apb1smenr1;
	uint32_t apb1smenr2;
	uint32_t apb2smenr;
	uint32_t unused8;
	uint32_t ccipr;
	uint32_t unused9;
	uint32_t bdcr;
	uint32_t csr;
	uint32_t crrcr;
	uint32_t ccipr2;
	
}RCC_TypeDef;

#define RCC_BASE 0x40021000 // found from RM page 68 

#define RCC ( RCC_TypeDef *) RCC_BASE

#endif

//************************************************************//

#ifndef THEREALHELLOWORLD_EXTI_H
#define THEREALHELLOWORLD_EXTI_H
#include <stdint.h>



typedef struct
{
	
	uint32_t imr1;
	uint32_t emr1;
	uint32_t rtsr1;
	uint32_t ftsr1;
	uint32_t swier1;
	uint32_t pr1;
	uint32_t unused[2];
	uint32_t imr2;
	uint32_t emr2;
	uint32_t rtsr2;
	uint32_t ftsr2;
	uint32_t swier2;
	uint32_t pr2;
} EXTI_TypeDef;



#define EXTI_BASE 0x40010400 

#define EXTI (EXTI_TypeDef *) EXTI_BASE
#endif



#ifndef THEREALHELLOWORLD_NVIC_H
#define THEREALHELLOWORLD_NVIC_H
#include <stdint.h>



#define NVIC_BASE 0xE000E000
#define NVIC_ISER_BASE NVIC_BASE+0x100
#define NVIC_ICER_BASE NVIC_BASE+0x180
#define NVIC_ISPR_BASE NVIC_BASE+0x200
#define NVIC_ICPR_BASE NVIC_BASE+0x280
#define NVIC_IABR_BASE NVIC_BASE+0x300
#define NVIC_IPR_BASE NVIC_BASE+0x400
#define NVIC_STIR_BASE NVIC_BASE+0xF00



#endif

//**********************************************//
