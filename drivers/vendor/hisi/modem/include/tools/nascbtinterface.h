
#ifndef NAS_CCBT_H
#define NAS_CCBT_H

/*******************************************************************************
 1. Other files included
*******************************************************************************/

#include "vos.h"

#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */
#pragma pack(4)

/*******************************************************************************
 2. Macro definitions
*******************************************************************************/
#define ID_CCBT_MTA_LOAD_PS_RRC_REQ            (0x0175)
#define ID_MTA_CCBT_LOAD_PS_RRC_CNF            (0x0175)

#define ID_CCBT_MTA_QRY_PS_RRC_LOAD_STATUS_REQ (0x0176)
#define ID_MTA_CCBT_QRY_PS_RRC_LOAD_STATUS_CNF (0x0176)




/*******************************************************************************
 3. Enumerations declarations
*******************************************************************************/

/*******************************************************************************
 4. Message Header declaration
*******************************************************************************/

/*******************************************************************************
 5. Message declaration
*******************************************************************************/

/*******************************************************************************
 6. STRUCT and UNION declaration
*******************************************************************************/

/*******************************************************************************
 7. OTHER declarations
*******************************************************************************/

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          enMsgId;
    VOS_UINT16                          usOpId;
}CCBT_MTA_MSG_HEADER_STRU;

/** ****************************************************************************
 * Name        : CCBT_MTA_LOAD_PS_RRC_REQ_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          enMsgId;
    VOS_UINT16                          usOpId;
    VOS_RATMODE_ENUM_UINT32             enRatType;
} CCBT_MTA_LOAD_PS_RRC_REQ_STRU;

/** ****************************************************************************
 * Name        : MTA_CCBT_LOAD_PS_RRC_CNF_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usTransPrimId;/*0x6001*/
    VOS_UINT16                          usReserve;
    VOS_UINT16                          enMsgId;
    VOS_UINT16                          usOpId;
    VOS_RATMODE_ENUM_UINT32             enRatType;
    VOS_UINT32                          ulIsLoaded;       /* VOS_OK(0)表示成功，VOS_ERR(1)表示失败 */
} MTA_CCBT_LOAD_PS_RRC_CNF_STRU;

/** ****************************************************************************
 * Name        : CCBT_MTA_QRY_PS_RRC_LOAD_STATUS_REQ
 *               ID_CCBT_MTA_QRY_PS_RRC_LOAD_STATUS_REQ
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          enMsgId;
    VOS_UINT16                          usOpId;
    VOS_RATMODE_ENUM_UINT32             enRatType;
} CCBT_MTA_QRY_PS_RRC_LOAD_STATUS_REQ_STRU;

/** ****************************************************************************
 * Name        : MTA_CCBT_QRY_PS_RRC_LOAD_STATUS_CNF
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usTransPrimId;/*0x6001*/
    VOS_UINT16                          usReserve;
    VOS_UINT16                          enMsgId;
    VOS_UINT16                          usOpId;
    VOS_RATMODE_ENUM_UINT32             enRatType;
    VOS_UINT32                          ulIsLoaded;       /* VOS_OK(0)表示成功，VOS_ERR(1)表示失败 */
} MTA_CCBT_QRY_PS_RRC_LOAD_STATUS_CNF_STRU;


/*******************************************************************************
 8. Global  declaration
*******************************************************************************/

/*******************************************************************************
 9. Function declarations
*******************************************************************************/

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif
