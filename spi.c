#include "stm32f0xx.h"

void SPI2_Int()
{
    SPI_InitTypeDef  SPI_InitStruct;
    
    SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;//ȫ˫��ģʽ
    SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
    SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;//��һ������
    SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;//�����ز���
    SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8; // 6MHz
    SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStruct.SPI_CRCPolynomial = 7;
    SPI_Init(SPI2,&SPI_InitStruct);
    
    SPI_RxFIFOThresholdConfig(SPI2, SPI_RxFIFOThreshold_QF);
    SPI_Cmd(SPI2, ENABLE );
}


uint8_t SpiInputOutput_Data(SPI_TypeDef* SPIx,uint8_t InputData)
{
 
    while( SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET);//������bufferΪ��ʱ(˵����һ�������Ѹ��Ƶ���λ�Ĵ�����)�˳�,��ʱ������buffer����д����
    SPI_SendData8(SPIx, InputData);
    
  
    while( SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET);//������bufferΪ�ǿ�ʱ�˳�
    return SPI_ReceiveData8(SPIx);
}

