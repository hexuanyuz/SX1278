#include "stm32f0xx.h"
#include "gpio.h"


void GPIO_int()
{
  GPIO_InitTypeDef  GPIO_InitStruct;
  /****************************************
   RF_NSS
  ****************************************/
  GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
  GPIO_InitStruct.GPIO_Speed=GPIO_Speed_Level_2;
  GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_Pin=RF_NSS_IO;
  GPIO_Init(RF_NSS_PORT, &GPIO_InitStruct);
  
  
  /****************************************
   M_CLK
  ****************************************/
  GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
  GPIO_InitStruct.GPIO_Speed=GPIO_Speed_Level_2;
  GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_Pin=RF_CLK_IO;
  GPIO_Init(RF_CLK_PORT, &GPIO_InitStruct);
  GPIO_PinAFConfig(RF_CLK_PORT,RF_CLK_AF,GPIO_AF_0);
    
  /****************************************
   M_MOSI
  ****************************************/
  GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
  GPIO_InitStruct.GPIO_Speed=GPIO_Speed_Level_2;
  GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_Pin=RF_MOSI_IO;
  GPIO_Init(RF_MOSI_PORT, &GPIO_InitStruct);
  GPIO_PinAFConfig(RF_MOSI_PORT,RF_MOSI_AF,GPIO_AF_0);

  /****************************************
   M_MISO
  ****************************************/
  GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
  GPIO_InitStruct.GPIO_Speed=GPIO_Speed_Level_2;
  GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_Pin=RF_MISO_IO;
  GPIO_Init(RF_MISO_PORT, &GPIO_InitStruct);
  GPIO_PinAFConfig(RF_MISO_PORT,RF_MISO_AF,GPIO_AF_0);
  
  
  /****************************************
   RF_RST
  ****************************************/
  GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
  GPIO_InitStruct.GPIO_Speed=GPIO_Speed_Level_2;
  GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_Pin=RF_RST_IO;
  GPIO_Init(RF_RST_PORT, &GPIO_InitStruct);
  
    /****************************************
   LED1
  ****************************************/
  GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
  GPIO_InitStruct.GPIO_Speed=GPIO_Speed_Level_2;
  GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_Pin=LED1_PIN;
  GPIO_Init(LED1_PORT, &GPIO_InitStruct);
  
  
  /****************************************
   RF_DIO0
  ****************************************/
  GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
  GPIO_InitStruct.GPIO_Speed=GPIO_Speed_Level_2;
  GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_Pin=RF_DIO0_IO;
  GPIO_Init(RF_DIO0_PORT, &GPIO_InitStruct);
  
  
   /****************************************
   RF_DIO1
  ****************************************/
  GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
  GPIO_InitStruct.GPIO_Speed=GPIO_Speed_Level_2;
  GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_Pin=RF_DIO1_IO;
  GPIO_Init(RF_DIO1_PORT, &GPIO_InitStruct);
  
  
	GPIO_SetBits(LED1_PORT,LED1_PIN);
						 /*  RF_MODE_PIN  */
	GPIO_InitStruct.GPIO_Pin =RF_MODE_PIN; 
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN; 
	GPIO_Init(RF_MODE_PORT, &GPIO_InitStruct);
	
	
    /****************************************
   RF_DIO2
  ****************************************/
  GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
  GPIO_InitStruct.GPIO_Speed=GPIO_Speed_Level_2;
  GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_Pin=RF_DIO2_IO;
  GPIO_Init(RF_DIO2_PORT, &GPIO_InitStruct);
  
  
  
  
  /****************************************
   RF_DIO3
  ****************************************/
  GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
  GPIO_InitStruct.GPIO_Speed=GPIO_Speed_Level_2;
  GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_Pin=RF_DIO3_IO;
  GPIO_Init(RF_DIO3_PORT, &GPIO_InitStruct);
  
  
}

