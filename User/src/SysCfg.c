#include "SysCfg.h"

u32 g_nSysState = 0;

void Sys_Delayms(u32 n)
{
    //
    n *= 0x2400;
    n++;
    while(n--);
}

void Sys_CfgClock(void)
{

}

void Sys_CfgPeriphClk(FunctionalState state)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA |
						  RCC_AHBPeriph_GPIOB |
						  RCC_AHBPeriph_GPIOC |
						  RCC_AHBPeriph_GPIOD , state);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB | 
						   RCC_APB1Periph_PWR, state);
}

const PORT_INF SYS_RUNLED_COM = {GPIOA, GPIO_Pin_0};
void Sys_CtrlIOInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = SYS_RUNLED_COM.Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(SYS_RUNLED_COM.Port, &GPIO_InitStructure);
}

RCC_ClocksTypeDef g_sSysclockFrep;
USB_CORE_HANDLE  USB_Device_dev ;
void Sys_Init()
{
	//Sys_CfgClock(); 
	RCC_GetClocksFreq(&g_sSysclockFrep);    //查看时钟频率
	Sys_CfgPeriphClk(ENABLE);
	
	Sys_DisableInt();
	Sys_CtrlIOInit();
	
	USB_InitInterface();
    USB_ConfigInt();
	USBD_Init(&USB_Device_dev, &USR_desc,  &USBD_HID_cb, &USR_cb);
	Sys_Delayms(1000);
	STick_InitSysTick();
	
	Sys_EnableInt();
}


void Sys_LedTask(void)
{
    if(a_CheckStateBit(g_nSysState, SYS_STAT_RUNLED))
    {
        static u32 ledTimes = 0;

		ledTimes ++;
        a_ClearStateBit(g_nSysState, SYS_STAT_RUNLED);
		if(ledTimes & 0x01)
		{
			Sys_RunLedOn();
		}
		else
		{
			Sys_RunLedOff();
		}
    #if SYS_ENABLE_WDT
        WDG_FeedIWDog();
    #endif
    }
}

void Sys_UsbTask(void)
{

}