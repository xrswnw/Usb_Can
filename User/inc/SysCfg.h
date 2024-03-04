#ifndef _SYSCFG_H_
#define _SYSCFG_H_

#include "Config.h"
#include "SysTick.h"
#include "Usb_HL.h"
#include  "usbd_hid_core.h"
#include  "usbd_usr.h"
extern u32 g_nSysState;

#define SYS_STAT_IDLE           0x00000001	    //系统初始化后处于空闲状态
#define SYS_STAT_RUNLED         0x00000002


extern const PORT_INF SYS_RUNLED_COM;
#define Sys_RunLedOn()				SYS_RUNLED_COM.Port->BRR = SYS_RUNLED_COM.Pin
#define Sys_RunLedOff()				SYS_RUNLED_COM.Port->BSRR = SYS_RUNLED_COM.Pin

void Sys_Delayms(u32 n);
void Sys_CfgClock(void);
void Sys_CfgPeriphClk(FunctionalState state);
void Sys_CtrlIOInit(void);
void Sys_Init();


void Sys_LedTask(void);
#endif