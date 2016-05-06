

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "NasEmmPlmnPublic.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMPLMNPUBLIC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMPLMNPUBLIC_C
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

/*****************************************************************************
 Function Name   : NAS_EMM_ClearLocalResource
 Description     : 清除本地资源
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lining 00141619      2008-10-18  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_EMM_ClearLocalResource( VOS_VOID )
{
    /*EMM&MMC 全局变量清空 */
    NAS_LMM_EmmAndMmcGlobInfoClear();

    /*初始化EMM全局变量*/
    NAS_LMM_EmmInfoInit();

    /* 清除各种模块*/
    NAS_LMM_EmmSubModGlobClear();

    /*NAS_LMM_SoftUsimInit();*//*可能有问题*/
    return;
}










#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

