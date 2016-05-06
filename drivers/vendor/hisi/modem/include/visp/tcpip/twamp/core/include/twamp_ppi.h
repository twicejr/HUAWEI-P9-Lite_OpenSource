
#ifndef _TCPIP_TWAMP_PPI_H_
#define _TCPIP_TWAMP_PPI_H_

#ifdef __cplusplus
extern "C"
{
#endif




extern ULONG TWAMP_SenderPpiUpdate(TWAMP_CLIENT_S *pstClient, TWAMP_SENDER_S *pstSender, UCHAR *pucSessDscp, ULONG ulType);



extern ULONG TWAMP_ResponderPpiUpdate(TWAMP_REFLECTOR_TEST_SESSION_S *pstTestSession, 
                                                                    UCHAR *pucSessDscp, 
                                                                    ULONG ulType);

#ifdef __cplusplus
}
#endif


#endif/* end of _TWAMP_PPI_H_*/


