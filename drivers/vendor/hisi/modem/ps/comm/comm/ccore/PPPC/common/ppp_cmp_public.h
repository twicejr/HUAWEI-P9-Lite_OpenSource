/******************************************************************************

                  版权所有 (C), 2012-2020, 华为技术有限公司

 ******************************************************************************
  文 件 名   : hsgw_public.h
  版 本 号   : 初稿
  作    者   : zhaichao 00129699
  生成日期   : 2012年10月30日
  最近修改   :
  功能描述   : HSGW/PDSN PPP和压缩模块公用数据结构定义
  函数列表   :
  修改历史   :
  1.日    期   : 2012年10月30日
    作    者   : zhaichao 0129699
    修改内容   : 创建文件

******************************************************************************/

#ifndef __PPP_CMP_PUBLIC_H__
#define __PPP_CMP_PUBLIC_H__

#define PPPCOMP_LZS1_MAXUSER  5
#define PPPCOMP_LZS0_MAXUSER  5

#if defined(__LINUX_VM__) || defined(__WIN32_PLATFORM__)
#define CMP_MAX_USER_NUM 10                   /* 和缓存消息数保持一致 */
#define PPPCOMP_MPPC_MAXUSER 10               /* MPPC支持的用户数 */
#define PPPCOMP_TCPIPCOMP_MAXUSER 10          /* VJ支持的用户数 */
#define PPPCOMP_LZS_MAXUSER  10
#else
#define CMP_MAX_USER_NUM  (HSGW_PRODUCT_TOTAL_PDN_NUMBER)                   /* 支持的最大用户数 */
#define PPPCOMP_MPPC_MAXUSER (HSGW_PRODUCT_MPPC_PDP_NUMBER * 16 / 10)        /* MPPC支持的用户数 */
#define PPPCOMP_TCPIPCOMP_MAXUSER (HSGW_PRODUCT_VJ_USER_NUMBER * 16 / 10)    /* VJ支持的用户数 */
#define PPPCOMP_LZS_MAXUSER  (PPPCOMP_LZS1_MAXUSER + PPPCOMP_LZS0_MAXUSER)
#endif

#ifndef __LINUX_PLATFORM__
#define CMP_MAX_USER_INDEX_NUM (2*CMP_MAX_USER_NUM)
#else
#define CMP_MAX_USER_INDEX_NUM CMP_MAX_USER_NUM
#endif

#endif /* __PPP_CMP_PUBLIC_H__ */
