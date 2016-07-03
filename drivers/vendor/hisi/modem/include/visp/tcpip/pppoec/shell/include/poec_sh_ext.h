

#ifndef  _POEC_SH_EXT_H_
#define  _POEC_SH_EXT_H_

#ifdef __cplusplus
extern "C"{
#endif

extern ULONG ulSOCKTmrQueID;

extern IFNET_S * IF_CreateVAByDialerIf ( IFNET_S *pstDialerif );
extern IFNET_S * IF_GetIfByFullName ( CHAR *szFull ) ;

#ifdef __cplusplus
}
#endif

#endif

