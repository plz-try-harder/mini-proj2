
#ifndef THEREALHELLOWORLD_STK_H
#define THEREALHELLOWORLD_STK_H
#include <stdint.h>

typedef struct
{
	uint32_t ctrl;
	uint32_t load;
	uint32_t val;
	uint32_t calib;
} STK_TypeDef;

#define STK_BASE 0xE000E010

#define STK (STK_TypeDef *) STK_BASE
#endif

