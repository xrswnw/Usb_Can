#ifndef _USB_HL_H_
#define _USB_HL_H_


#include "SysTick.h"

#define USB_STAT_IDLE       0x00000001
#define USB_STAT_RX         0x00000002
#define USB_STAT_TX         0x00000004
#define USB_STAT_OP         0x00000008
extern u32 g_nUsbState;

#define USB_FRAME_HEAD1_FLAG            0x7E
#define USB_FRAME_HEAD2_FLAG            0x55

#define USB_FRAME_BUF_MAX_LEN           256

typedef struct usbRxFrame{
    u8 frame[USB_FRAME_BUF_MAX_LEN + 1];
    u16 len;
    u32 time;
}USB_RXFRAME;
extern USB_RXFRAME g_sUsbRxFrame;

#define USB_RCV_TIMEOUT         10  //ÿ��tick��5ms
#define USB_IsRcvFrame()        (a_CheckStateBit(g_nUsbState, USB_STAT_OP) || \
                                 (a_CheckStateBit(g_nUsbState, USB_STAT_RX) && (g_sUsbRxFrame.time + USB_RCV_TIMEOUT < g_nSysTick)))
#define USB_ClearBuffer()       a_memset(&g_sUsbRxFrame, 0, sizeof(g_sUsbRxFrame))

void USB_InitInterface(void);
void USB_ConfigInt(void);
void USB_RxFrame(void);
void USB_TxFrame(u8 *pFrame, u8 len);
BOOL USB_CheckFrame(u8 *pFrame, u8 len);
void USB_SendUid(u8 len, u8 *pUid);
u8 USB_ProcessFrame(u8 *pFrame, u16 len);

#endif
