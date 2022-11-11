#ifndef __PORTCOM_H__
#define __PORTCOM_H__

#include <windows.h>

/*- Function Prototype(s) ------------------------------------------ GLOBAL -*/

#ifdef __cplusplus
extern "C" {
#endif

extern INT CreateCommDevice(HWND hWnd,
                            BYTE bPort,
                            UINT nMessage,
                            BOOL bAlwaysSend);

extern BOOL DestroyCommDevice(INT iIndex);

extern BOOL OpenCommDevice(INT iIndex,
                           DWORD dwFuncDTR,
                           DWORD dwFuncRTS);

extern BOOL SetupCommDevice(INT iIndex);

extern BOOL CloseCommDevice(INT iIndex);

extern BOOL IsOnCommSignal(BOOL *pOK,
                           INT iIndex,
                           DWORD dwEvent);

extern BOOL EscapeFunction(INT iIndex,
                           DWORD dwFunc);

extern HWND ChangeWndMessage(INT iIndex,
                             HWND hWnd);

#ifdef __cplusplus
};
#endif

/*- End Of File -------------------------------------------------------------*/

#endif  /* __PORTCOM_H__ */
