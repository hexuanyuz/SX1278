#include "stm32f0xx.h"
#include "Sx1276-1278.h"
#include "delay.h"
#include "user.h"

/**************************************************************************************************************************************
Demo ��������  EnableMaster=true  Ϊ�����ˣ������˷���һ��"PING"���ݺ��л������գ��ȴ��ӻ����ص�Ӧ��"PONG"����LED��˸

               EnableMaster=false Ϊ�ӻ��ˣ��ӻ��˽��յ������˷�������"PING"���ݺ�LED��˸������һ��"PONG"������ΪӦ��
***************************************************************************************************************************************/

//��ʾ: FSK��LORAģʽ�л�ֻ��Ҫͨ��radio.h �ļ��еĺ궨���޸�   #define LORA       1// [0: OFF, 1: ON] 1��LORAģʽ 0:FSKģʽ


#define  EnableMaster        GPIO_ReadInputDataBit(RF_MODE_PORT, RF_MODE_PIN)//����ѡ���


tRadioDriver *Radio = 0;
const uint8_t PingMsg[] = "PING";
const uint8_t PongMsg[] = "PONG";
uint16_t num_rx=0;
uint8_t   RXBuffer[RF_BUFFER_SIZE];  //RX buffer			
uint8_t   TXBuffer[RF_BUFFER_SIZE];  //TX buffer
uint16_t  crc_value;



void SysClock_48()
{ 
   RCC_PLLCmd(DISABLE);
   RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_12);//48M
   RCC_PLLCmd(ENABLE);
   while(!RCC_GetFlagStatus(RCC_FLAG_PLLRDY));
   RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
}

void Tick_Configration()
{
    /* Setup SysTick Timer for 1ms interrupts ( not too often to save power ) */
    if( SysTick_Config( SystemCoreClock / 1000 ) )
    { 
        /* Capture error */ 
        while (1);
    }
}

void RCC_Configuration()
{   
  /* Enable GPIO clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA|RCC_AHBPeriph_GPIOB|RCC_AHBPeriph_GPIOC|RCC_AHBPeriph_GPIOF, ENABLE);
  
  /* Enable peripheral Clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2|RCC_APB1Periph_PWR, ENABLE);  
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_SYSCFG, ENABLE); 

}

void NVIC_Config()
{
  NVIC_InitTypeDef  NVIC_InitStructure;
  EXTI_InitTypeDef  EXTI_InitStructure;
  
  EXTI_ClearITPendingBit(EXTI_Line1);
  EXTI_InitStructure.EXTI_Line = EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource1);

  /* Enable and set EXTI0 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0x00;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void HW_Int()//MCU��Χ��Դ��ʼ��
{
  SysClock_48(); 
  Tick_Configration();
  RCC_Configuration();
  GPIO_int();
  SPI2_Int();
}


void LedToggle(void)
{
  GPIO_WriteBit( LED1_PORT, LED1_PIN,Bit_RESET);//LED��˸
  HAL_Delay_nMs (10);
  GPIO_WriteBit( LED1_PORT, LED1_PIN,Bit_SET);
}

/*
 * Manages the master operation
 */
void OnMaster( void )
{  
    switch(Radio->Process())
    {
      case RF_TX_DONE:
           
	       Radio->StartRx( ); 
      break;
		
      case RF_RX_DONE:
        Radio->GetRxPacket( RXBuffer, ( uint16_t* )&num_rx );
        
        if(num_rx > 0)
        {
           crc_value=RXBuffer[num_rx-2];
           crc_value<<=8;
           crc_value|=RXBuffer[num_rx-1];
           if(crc_value==RadioComputeCRC(RXBuffer,num_rx-2,CRC_TYPE_IBM))//CRC check
           {
            if(strncmp(( const char* )RXBuffer, ( const char* )PongMsg,4)==0)
            {
                  LedToggle();//LED��˸
                 
                 // Send the next PING frame            
		          TXBuffer[0] = 'P';
                  TXBuffer[1] = 'I';
                  TXBuffer[2] = 'N';
                  TXBuffer[3] = 'G';
                  crc_value=RadioComputeCRC(TXBuffer,4,CRC_TYPE_IBM);//����ó�Ҫ�������ݰ�CRCֵ
                  TXBuffer[4]=crc_value>>8;
                  TXBuffer[5]=crc_value;
			      
                  Radio->SetTxPacket( TXBuffer, 6);	
            }
           }
        }            
        break;
        
        case RF_RX_TIMEOUT:
        // Send the next PING frame
        TXBuffer[0] = 'P';
        TXBuffer[1] = 'I';
        TXBuffer[2] = 'N';
        TXBuffer[3] = 'G';
        crc_value=RadioComputeCRC(TXBuffer,4,CRC_TYPE_IBM);//����ó�Ҫ�������ݰ�CRCֵ
        TXBuffer[4]=crc_value>>8;
        TXBuffer[5]=crc_value;
			      		 
        Radio->SetTxPacket( TXBuffer, 6);
        break;
				
        
     default:break;
    }
}

/*
 * Manages the slave operation
 */
void OnSlave( void )
{
    switch(Radio->Process())
    {
     case RF_RX_DONE:
        Radio->GetRxPacket(RXBuffer,(uint16_t* )&num_rx );
        
        if(num_rx >0)
        {
           crc_value=RXBuffer[num_rx-2];
           crc_value<<=8;
           crc_value|=RXBuffer[num_rx-1];
           if(crc_value==RadioComputeCRC(RXBuffer,num_rx-2,CRC_TYPE_IBM))//CRC check
           {
            if( strncmp( ( const char* )RXBuffer, ( const char* )PingMsg, 4 ) == 0 )
            {
                  LedToggle();//LED��˸
                  
                  // Ack with PONG frame            
		          TXBuffer[0] = 'P';
                  TXBuffer[1] = 'O';
                  TXBuffer[2] = 'N';
                  TXBuffer[3] = 'G';
                  crc_value=RadioComputeCRC(TXBuffer,4,CRC_TYPE_IBM);//����ó�Ҫ�������ݰ�CRCֵ
                  TXBuffer[4]=crc_value>>8;
                  TXBuffer[5]=crc_value;
			      
                  Radio->SetTxPacket( TXBuffer, 6);				
            } 
           }
        }
        
        break;
        
        case RF_TX_DONE:
        
       
        Radio->StartRx( ); 
     
        break;
        
      default:break;
    }
}


int main(void)
{
   HW_Int();//MCU��ʼ��
   Radio = RadioDriverInit();
   Radio->Init();
   
   if(EnableMaster )
   {
     TXBuffer[0] = 'P';
     TXBuffer[1] = 'I';
     TXBuffer[2] = 'N';
     TXBuffer[3] = 'G';
     crc_value=RadioComputeCRC(TXBuffer,4,CRC_TYPE_IBM);//����ó�Ҫ�������ݰ�CRCֵ
     TXBuffer[4]=crc_value>>8;
     TXBuffer[5]=crc_value;
     Radio->SetTxPacket(TXBuffer,6);//���Ҫ���͵����ݰ�
    }
   else
   {
       Radio->StartRx();
   }
   
  while(1)
  { 
     if(EnableMaster)
      {  
        OnMaster();
      }    
      else
      {
        OnSlave();
      }
  }
}





