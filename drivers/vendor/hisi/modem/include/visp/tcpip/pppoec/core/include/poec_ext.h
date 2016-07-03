

#ifndef  _POEC_EXT_H_
#define  _POEC_EXT_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "tcpip/public/tcpip_basefun.h"
extern IFNET_S *IF_CreateVAByDialerIf ( IFNET_S *pstDialerif );
extern IFNET_S * IF_DynamicCreateIfNet( CHAR * szFullName, ULONG ulSubType );

#ifdef __cplusplus
}
#endif

#endif

