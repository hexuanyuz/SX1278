#ifndef _GPIO_H_
#define _GPIO_H_


#define  RF_CLK_PORT       GPIOB
#define  RF_CLK_IO         GPIO_Pin_13
#define  RF_CLK_AF         GPIO_PinSource13

#define  RF_MISO_PORT      GPIOB
#define  RF_MISO_IO        GPIO_Pin_14
#define  RF_MISO_AF        GPIO_PinSource14

#define  RF_MOSI_PORT      GPIOB
#define  RF_MOSI_IO        GPIO_Pin_15
#define  RF_MOSI_AF        GPIO_PinSource15

#define  RF_NSS_PORT       GPIOB
#define  RF_NSS_IO         GPIO_Pin_12

#define  RF_RST_PORT       GPIOB
#define  RF_RST_IO         GPIO_Pin_2

#define  RF_DIO0_PORT      GPIOA
#define  RF_DIO0_IO        GPIO_Pin_0

#define  RF_DIO1_PORT      GPIOA
#define  RF_DIO1_IO        GPIO_Pin_1

#define  RF_DIO2_PORT      GPIOA
#define  RF_DIO2_IO        GPIO_Pin_6

#define  RF_DIO3_PORT      GPIOB
#define  RF_DIO3_IO        GPIO_Pin_0

#define LED1_PORT          GPIOA
#define LED1_PIN           GPIO_Pin_15


#define RF_MODE_PIN                     GPIO_Pin_2
#define RF_MODE_PORT                    GPIOA


void GPIO_int(void);


#endif

