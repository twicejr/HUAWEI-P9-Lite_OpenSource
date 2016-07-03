

#ifndef _CSN_AM_PUBLIC_H_H_H_
#define _CSN_AM_PUBLIC_H_H_H_


typedef struct tagA11_RRQ_PARSER_FOR_CSN
{
    A11_IMSI_S stIMSI;
    VOS_UINT32  ulPcfIp;
    VOS_UINT32  ulSpi;
    VOS_UINT32  ulIdHigh;          /* Identification: higher 4 bytes */    
    VOS_UINT32  ulIdLow;           /* Identification: lower 4 bytes */
    VOS_UINT16 usLifetime;
    UCHAR  ucMsgType;
    UCHAR  ucReserved;
    VOS_UINT16 usDstPortNum;
    VOS_UINT16 usReserved;
}VOS_PACKED A11_PARSER_FOR_CSN_S;

typedef struct tagCSN_INTERFACE_INFO
{
    VOS_UINT32 ulCsnifIPAddr;         /*CSN接口IP地址*/
    VOS_UINT32 ulCsnifVpnId;           /*CSN接口VPN ID*/
    VOS_UINT32 ulCsnifSubIdx;         
    VOS_UINT32 ulCsnifIdx;             
}CSN_INTERFACE_INFO_S;  

#define CSN_IF_IPADDR                         (g_stCsnifInfo.ulCsnifIPAddr)
#define CSN_IF_VPNID                          (g_stCsnifInfo.ulCsnifVpnId)
#define CSN_IF_SUBIDX                         (g_stCsnifInfo.ulCsnifSubIdx)
#define CSN_IF_IDX                            (g_stCsnifInfo.ulCsnifIdx)

#define CSN_RPIF_IPADDR                       (g_stCSNRpifInfo.ulCsnifIPAddr)
#define CSN_RPIF_VPNID                        (g_stCSNRpifInfo.ulCsnifVpnId)
#define CSN_RPIF_SUBIDX                       (g_stCSNRpifInfo.ulCsnifSubIdx)
#define CSN_RPIF_IDX                          (g_stCSNRpifInfo.ulCsnifIdx)

#define CSN_DETC_MSG_BUF_LEN      4096      /* 探测消息缓冲的最大长度 */

enum CSN_BACKUP_MSG_CODE
{
    CSN_MSGCODE_FCM_DETECEREPLY,    
    CSN_MSGCODE_VP_BACKUP,
    CSN_MSGCODE_FCM_BACKUP,   /* 调整备份消息码位置为了在fcm消息中区分转发上送的探测应答消息和备份消息 */
    CSN_MSGCODE_BULT
};

extern VOS_UINT32 g_ulCsnServiceReadyFlag;
extern VOS_UINT32 CSN_OmInitial(VOID);

#endif


