

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "CsdDebug.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if( FEATURE_ON == FEATURE_CSD )

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
CSD_UL_STATUS_INFO_STRU                 g_stCsdStatusInfo = {0};

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : CSD_ShowULStatus
 功能描述  : 显示CSD上行统计信息
 输入参数  : vos_void
 输出参数  : 无
 返 回 值  : vos_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月29日
    作    者   : w00199382
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CSD_ShowULStatus(VOS_VOID)
{
    (VOS_VOID)vos_printf("CSD收到上行数据的个数                             %d\n",g_stCsdStatusInfo.ulULRecvPktNum);
    (VOS_VOID)vos_printf("CSD上行缓存中数据包的个数                         %d\n",g_stCsdStatusInfo.ulULSaveBuffPktNum);
    (VOS_VOID)vos_printf("CSD上行入队失败的次数                             %d\n",g_stCsdStatusInfo.ulULEnQueFail);
    (VOS_VOID)vos_printf("CSD发送上行缓存包数量                             %d\n",g_stCsdStatusInfo.ulULSendPktNum);
    (VOS_VOID)vos_printf("CSD发送上行数据时从队列中获取到空指针包数目       %d\n",g_stCsdStatusInfo.ulULQueNullNum);
    (VOS_VOID)vos_printf("CSD发送上行数据sk_buffer头转换到IMM头失败的包数目 %d\n",g_stCsdStatusInfo.ulULZcToImmFailNum);
    (VOS_VOID)vos_printf("CSD发送上行数据插入DICC通道失败的包数目           %d\n",g_stCsdStatusInfo.ulULInsertDiccFailNum);
    (VOS_VOID)vos_printf("\r\n");

    return;
}
/*****************************************************************************
 函 数 名  : CSD_ShowDLStatus
 功能描述  : 显示CSD下行统计信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月29日
    作    者   : w00199382
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CSD_ShowDLStatus(VOS_VOID)
{
    (VOS_VOID)vos_printf("CSD收到下行数据的个数                             %d\n",g_stCsdStatusInfo.ulDLRecvPktNum);
    (VOS_VOID)vos_printf("CSD发送下行缓存包数量                             %d\n",g_stCsdStatusInfo.ulDLSendPktNum);
    (VOS_VOID)vos_printf("CSD下行发送失败包的数目                           %d\n",g_stCsdStatusInfo.ulDLSendFailNum);
    (VOS_VOID)vos_printf("\r\n");

    return;
}
/*****************************************************************************
 函 数 名  : CSD_Help
 功能描述  : CSD软调试入口
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月29日
    作    者   : w00199382
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CSD_Help(VOS_VOID)
{
    (VOS_VOID)vos_printf("********************CSD软调信息************************\n");
    (VOS_VOID)vos_printf("CSD_ShowULStatus                         显示CSD上行统计信息\n");
    (VOS_VOID)vos_printf("CSD_ShowDLStatus                         显示CSD下行统计信息\n");

    return;
}









#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
