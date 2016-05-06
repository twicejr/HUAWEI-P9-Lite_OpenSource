/******************************************************************************

   Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasEmmSecuSoftUsim.c
  Description     :
  History         :
     1.liuwenyu 143951       2008-12-27   Draft Enact

******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEmmSecuSoftUsim.h"
#include    "NasLmmPubMPrint.h"
#include    "NasEmmSecuOm.h"
#include    "NasLmmPubMNvim.h"

#if(VOS_WIN32 == VOS_OS_VER)
#include    "msp.h"
#endif

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMSECUSOFTUSIM_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMSECUSOFTUSIM_C
/*lint +e767*/


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/

/*****************************************************************************
  3 Function
*****************************************************************************/

#if(VOS_WIN32 == VOS_OS_VER)


#endif

/*****************************************************************************
 Function Name   : PS_GetLeastSignBitsByTrunc
 Description     : 从256bits数据中得到低128bits数据
 Input           : VOS_UINT8 aucSrcData[MAX_HMAC_HASH_SIZE]
                   VOS_UINT8 aucDestData[MAX_HMAC_HASH_SIZE/2]
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.l51045      2008-12-11  Draft Enact

*****************************************************************************/
VOS_VOID PS_GetLeastSignBitsByTrunc(const VOS_UINT8 aucSrcData[MAX_HMAC_HASH_SIZE],
                                              VOS_UINT8 aucDestData[MAX_HMAC_HASH_SIZE/2])
{
    VOS_UINT32                          ulLoop              = 0;
    VOS_UINT32                          ulTmpLoop           = 0;

    for ( ulLoop = 0 ; ulLoop< (MAX_HMAC_HASH_SIZE/2); ulLoop++ )
    {
        /*修改:应该取低位，而不是高位*/
        ulTmpLoop = ulLoop + (MAX_HMAC_HASH_SIZE/2);
        aucDestData[ulLoop] = aucSrcData[ulTmpLoop];
    }

    return;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

