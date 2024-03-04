#include "Usb_HL.h"
u32 g_nUsbState = USB_STAT_IDLE;
USB_RXFRAME g_sUsbRxFrame = {0};

const PORT_INF USB_PORT = {GPIOA, GPIO_Pin_11 | GPIO_Pin_12};
void USB_InitInterface(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = USB_PORT.Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_Init(USB_PORT.Port, &GPIO_InitStructure);
}

void USB_ConfigInt(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    NVIC_InitStructure.NVIC_IRQChannel = USB_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPriority = 14;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);
}

BOOL USB_CheckFrame(u8 *pFrame, u8 len)
{
    BOOL b = FALSE;

    
    return b;
}

u8 USB_ProcessFrame(u8 *pFrame, u16 len)
{
    u8 frameLen = 0;


    return frameLen;
}

void USB_RxFrame(void)
{
 
}

void USB_TxFrame(u8 *pFrame, u8 len)
{
   
}

void USB_SendUid1(u8 len, u8 *pUid)
{

}



