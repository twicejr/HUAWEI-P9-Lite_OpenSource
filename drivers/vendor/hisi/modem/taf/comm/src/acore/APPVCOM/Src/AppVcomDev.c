

/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "PsTypeDef.h"
#include "vos.h"
#include "PsCommonDef.h"
#include "AppVcomDev.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 */
#define    THIS_FILE_ID        PS_FILE_ID_APP_VCOM_DEV_C
/*lint -e767 */

/*****************************************************************************
   2 全局变量定义
*****************************************************************************/

/* VCOM CTX,用于保存VCOM的全局变量*/
APP_VCOM_DEV_CTX_STRU                   g_astVcomCtx[APP_VCOM_MAX_NUM];

APP_VCOM_DEBUG_INFO_STRU                g_stAppVcomDebugInfo;



/* 虚拟串口文件操作接口 */
#if (VOS_OS_VER == VOS_WIN32)
static struct file_operations           g_stOperations_Fops;
#else
static const struct file_operations     g_stOperations_Fops =
{
    .owner = THIS_MODULE,
    .read  = APP_VCOM_Read,
    .poll  = APP_VCOM_Poll,
    .write = APP_VCOM_Write,
    .open  = APP_VCOM_Open,
    .release = APP_VCOM_Release,
};
#endif


/* APPVCOM的规格和应用
APPVCOM ID   缓存大小  用途           是否AT的CLIENT    ModemId
APPVCOM        4K      RIL(主)               是         MODEM0
APPVCOM1       4K      RIL(呼叫)             是         MODEM0
APPVCOM2       4K      工程菜单              是         MODEM0
APPVCOM3       8K      生产装备(AT SERVER)   是         MODEM0
APPVCOM4       4K      audio RIL             是         MODEM0
APPVCOM5       4K      RIL(主)               是         MODEM1
APPVCOM6       4K      RIL(呼叫)             是         MODEM1
APPVCOM7       8K      生产装备(AT SERVER)   是         MODEM1
APPVCOM8       4K      工程菜单/HIDP         是         MODEM1
APPVCOM9       4K      AGPS                  是         MODEM0
APPVCOM10      4K      NFC/BIP               是         MODEM0
APPVCOM11      4K      ISDB                  是         MODEM0
APPVCOM12      4K      AGPS                  是         MODEM1
APPVCOM13      4K      RIL(查询)             是         MODEM0
APPVCOM14      4K      RIL(查询)             是         MODEM1
APPVCOM15      4K      NFC                   是         MODEM1
APPVCOM16      4K      HIDP                  是         MODEM0
APPVCOM17      4K      AGPS-AP               是         MODEM0
APPVCOM18      4K      预留                  是         MODEM0
APPVCOM19      4K      预留                  是         MODEM0
APPVCOM20      4K      RIL(主)               是         MODEM2
APPVCOM21      4K      RIL(呼叫)             是         MODEM2
APPVCOM22      4K      工程菜单              是         MODEM2
APPVCOM23      8K      生产装备(AT SERVER)   是         MODEM2
APPVCOM24      4K      AGPS                  是         MODEM2
APPVCOM25      4K      NFC                   是         MODEM2
APPVCOM26      4K      RIL(查询)             是         MODEM2
APPVCOM27      2M      CBT                   是         MODEM0
APPVCOM28      4K      T/L装备               否
APPVCOM29      16K     errlog                否
APPVCOM30      2M      log 3.5               否
APPVCOM31      2M      log 3.5               否
*/
#if (FEATURE_ON == FEATURE_VCOM_EXT)
const APP_VCOM_DEV_CONFIG_STRU g_astAppVcomCogfigTab[] =
{
    {APP_VCOM_DEV_NAME_0, APP_VCOM_SEM_NAME_0, 0x1000, 0},                      /* APPVCOM */
    {APP_VCOM_DEV_NAME_1, APP_VCOM_SEM_NAME_1, 0x1000, 0},                      /* APPVCOM1 */
    {APP_VCOM_DEV_NAME_2, APP_VCOM_SEM_NAME_2, 0x1000, 0},                      /* APPVCOM2 */
    {APP_VCOM_DEV_NAME_3, APP_VCOM_SEM_NAME_3, 0x2000, 0},                      /* APPVCOM3 */
    {APP_VCOM_DEV_NAME_4, APP_VCOM_SEM_NAME_4, 0x1000, 0},                      /* APPVCOM4 */
    {APP_VCOM_DEV_NAME_5, APP_VCOM_SEM_NAME_5, 0x1000, 0},                      /* APPVCOM5 */
    {APP_VCOM_DEV_NAME_6, APP_VCOM_SEM_NAME_6, 0x1000, 0},                      /* APPVCOM6 */
    {APP_VCOM_DEV_NAME_7, APP_VCOM_SEM_NAME_7, 0x2000, 0},                      /* APPVCOM7 */
    {APP_VCOM_DEV_NAME_8, APP_VCOM_SEM_NAME_8, 0x1000, 0},                      /* APPVCOM8 */
    {APP_VCOM_DEV_NAME_9, APP_VCOM_SEM_NAME_9, 0x2000, 0},                      /* APPVCOM9 */
    {APP_VCOM_DEV_NAME_10, APP_VCOM_SEM_NAME_10, 0x1000, 0},                    /* APPVCOM10 */
    {APP_VCOM_DEV_NAME_11, APP_VCOM_SEM_NAME_11, 0x1000, 0},                    /* APPVCOM11 */
    {APP_VCOM_DEV_NAME_12, APP_VCOM_SEM_NAME_12, 0x1000, 0},                    /* APPVCOM12 */
    {APP_VCOM_DEV_NAME_13, APP_VCOM_SEM_NAME_13, 0x1000, 0},                    /* APPVCOM13 */
    {APP_VCOM_DEV_NAME_14, APP_VCOM_SEM_NAME_14, 0x1000, 0},                    /* APPVCOM14 */
    {APP_VCOM_DEV_NAME_15, APP_VCOM_SEM_NAME_15, 0x1000, 0},                    /* APPVCOM15 */
    {APP_VCOM_DEV_NAME_16, APP_VCOM_SEM_NAME_16, 0x1000, 0},                    /* APPVCOM16 */
    {APP_VCOM_DEV_NAME_17, APP_VCOM_SEM_NAME_17, 0x1000, 0},                    /* APPVCOM17 */
    {APP_VCOM_DEV_NAME_18, APP_VCOM_SEM_NAME_18, 0x1000, 0},                    /* APPVCOM18 */
    {APP_VCOM_DEV_NAME_19, APP_VCOM_SEM_NAME_19, 0x1000, 0},                    /* APPVCOM19 */
    {APP_VCOM_DEV_NAME_20, APP_VCOM_SEM_NAME_20, 0x1000, 0},                    /* APPVCOM20 */
    {APP_VCOM_DEV_NAME_21, APP_VCOM_SEM_NAME_21, 0x1000, 0},                    /* APPVCOM21 */
    {APP_VCOM_DEV_NAME_22, APP_VCOM_SEM_NAME_22, 0x1000, 0},                    /* APPVCOM22 */
    {APP_VCOM_DEV_NAME_23, APP_VCOM_SEM_NAME_23, 0x2000, 0},                    /* APPVCOM23 */
    {APP_VCOM_DEV_NAME_24, APP_VCOM_SEM_NAME_24, 0x1000, 0},                    /* APPVCOM24 */
    {APP_VCOM_DEV_NAME_25, APP_VCOM_SEM_NAME_25, 0x1000, 0},                    /* APPVCOM25 */
    {APP_VCOM_DEV_NAME_26, APP_VCOM_SEM_NAME_26, 0x1000, 0},                    /* APPVCOM26 */
    {APP_VCOM_DEV_NAME_27, APP_VCOM_SEM_NAME_27, 0x200000, 0},                  /* APPVCOM27 */
    {APP_VCOM_DEV_NAME_28, APP_VCOM_SEM_NAME_28, 0x1000, 0},                    /* APPVCOM28 */
    {APP_VCOM_DEV_NAME_29, APP_VCOM_SEM_NAME_29, 0x4000, 0},                    /* APPVCOM29 */
    {APP_VCOM_DEV_NAME_30, APP_VCOM_SEM_NAME_30, 0x200000, 0},                  /* APPVCOM30 */
    {APP_VCOM_DEV_NAME_31, APP_VCOM_SEM_NAME_31, 0x200000, 0}                   /* APPVCOM31 */
};
#else
const APP_VCOM_DEV_CONFIG_STRU g_astAppVcomCogfigTab[] =
{
    {APP_VCOM_DEV_NAME_0, APP_VCOM_SEM_NAME_0, 0x1000, 0},                      /* APPVCOM */
    {APP_VCOM_DEV_NAME_1, APP_VCOM_SEM_NAME_1, 0x1000, 0}                       /* APPVCOM1 */
#if 0
    {APP_VCOM_DEV_NAME_2, APP_VCOM_SEM_NAME_2, 0x1000},                         /* APPVCOM2 */
    {APP_VCOM_DEV_NAME_3, APP_VCOM_SEM_NAME_3, 0x2000},                         /* APPVCOM3 */
    {APP_VCOM_DEV_NAME_4, APP_VCOM_SEM_NAME_4, 0x1000}                          /* APPVCOM4 */
#endif
};
#endif

APP_VCOM_DEBUG_CFG_STRU              g_stAppVcomDebugCfg;

/*****************************************************************************
   3 函数、变量声明
*****************************************************************************/

/*****************************************************************************
   4 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : APP_VCOM_GetVcomCtxAddr
 功能描述  : 获取当前设备的全局变量
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : APP_VCOM_DEV_CTX_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月5日
    作    者   : z00220246
    修改内容   : 新生成函数

*****************************************************************************/
APP_VCOM_DEV_CTX_STRU* APP_VCOM_GetVcomCtxAddr(VOS_UINT8 ucIndex)
{
    return &(g_astVcomCtx[ucIndex]);
}

/*****************************************************************************
 函 数 名  : APP_VCOM_GetAppVcomDevEntity
 功能描述  : 获取当前VCOM的设备实体指针
 输入参数  : VOS_UINT8 ucIndex
 输出参数  :
 返 回 值  : 返回当前VCOM的设备实体
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年12月03日
   作    者   : z00220246
   修改内容   : 新生成函数

*****************************************************************************/
APP_VCOM_DEV_ENTITY_STRU* APP_VCOM_GetAppVcomDevEntity(VOS_UINT8 ucIndex)
{
    return (g_astVcomCtx[ucIndex].pstAppVcomDevEntity);
}

/*****************************************************************************
 函 数 名  : APP_VCOM_RegDataCallback
 功能描述  : VCOM上行数据处理模块为AT模块提供的注册上行AT码流接收函数接口
 输入参数  : VOS_UINT8  ucDevIndex,    SEND_UL_AT_FUNC pFunc
 输出参数  : 无
 返 回 值  : VOS_UINT32

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月23日
    作    者   : z00220246
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 APP_VCOM_RegDataCallback(VOS_UINT8 ucDevIndex, SEND_UL_AT_FUNC pFunc)
{
    APP_VCOM_DEV_CTX_STRU              *pstVcomCtx;

    /* 索引号错误*/
    if (ucDevIndex >= APP_VCOM_DEV_INDEX_BUTT)
    {
        return VOS_ERR;
    }

    pstVcomCtx = APP_VCOM_GetVcomCtxAddr(ucDevIndex);

    /* 函数指针赋给全局变量*/
    pstVcomCtx->pSendUlAtFunc = pFunc;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : APP_VCOM_RegEvtCallback
 功能描述  : VCOM为外部模块提供的注册端口事件处理函数接口
 输入参数  : VOS_UINT8  ucDevIndex,    EVENT_FUNC pFunc
 输出参数  : 无
 返 回 值  : VOS_UINT32

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月23日
    作    者   : z00220246
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 APP_VCOM_RegEvtCallback(VOS_UINT8 ucDevIndex, EVENT_FUNC pFunc)
{
    APP_VCOM_DEV_CTX_STRU              *pstVcomCtx;

    /* 索引号错误*/
    if (ucDevIndex >= APP_VCOM_DEV_INDEX_BUTT)
    {
        return VOS_ERR;
    }

    pstVcomCtx = APP_VCOM_GetVcomCtxAddr(ucDevIndex);

    /* 函数指针赋给全局变量*/
    pstVcomCtx->pEventFunc = pFunc;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : APP_VCOM_GetIndexFromMajorDevId
 功能描述  : 根据主设备号，得到设备在全局变量中的索引号
 输入参数  : VOS_UINT32 ulMajorDevId
 输出参数  : 无
 返 回 值  : VOS_UINT8 设备索引号

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月23日
    作    者   : z00220246
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 APP_VCOM_GetIndexFromMajorDevId(VOS_UINT ulMajorDevId)
{
    VOS_UINT8                           ucLoop;
    APP_VCOM_DEV_CTX_STRU              *pstVcomCtx;

    for (ucLoop = 0; ucLoop < APP_VCOM_MAX_NUM; ucLoop++)
    {
        pstVcomCtx = APP_VCOM_GetVcomCtxAddr(ucLoop);

        if (pstVcomCtx->ulAppVcomMajorId == ulMajorDevId)
        {
            break;
        }
    }

    return ucLoop;
}

/*****************************************************************************
 函 数 名  : APP_VCOM_InitSpecCtx
 功能描述  : 初始化VCOM 模块全局变量
 输入参数  : VOS_UINT8 ulDevIndex
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月23日
    作    者   : z00220246
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  APP_VCOM_InitSpecCtx(VOS_UINT8 ucDevIndex)
{
    APP_VCOM_DEV_CTX_STRU              *pstVcomCtx;

    if (ucDevIndex >= APP_VCOM_MAX_NUM)
    {
        return;
    }

    pstVcomCtx = APP_VCOM_GetVcomCtxAddr(ucDevIndex);

    VOS_MemSet(pstVcomCtx->aucSendSemName, 0, APP_VCOM_SEM_NAME_MAX_LEN);
    VOS_MemSet(pstVcomCtx->aucAppVcomName, 0, APP_VCOM_DEV_NAME_MAX_LEN);

    VOS_MemCpy(pstVcomCtx->aucAppVcomName,
               g_astAppVcomCogfigTab[ucDevIndex].pcAppVcomName,
               VOS_StrLen(g_astAppVcomCogfigTab[ucDevIndex].pcAppVcomName));

    VOS_MemCpy(pstVcomCtx->aucSendSemName,
               g_astAppVcomCogfigTab[ucDevIndex].pcSendSemName,
               VOS_StrLen(g_astAppVcomCogfigTab[ucDevIndex].pcSendSemName));

    pstVcomCtx->ulAppVcomMajorId = APP_VCOM_MAJOR_DEV_ID + ucDevIndex;
}

/*****************************************************************************
 函 数 名  : APP_VCOM_Setup
 功能描述  : 将虚拟串口添加到字符设备中
 输入参数  : APP_VCOM_DEV_ENTITY_STRU *pstDev
             VOS_UINT8                 ucIndex
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : sunshaohua
    修改内容   : 新生成函数

  2.日    期   : 2012年11月23日
    作    者   : z00220246
    修改内容   : DSDA Phase I

*****************************************************************************/
VOS_VOID APP_VCOM_Setup(
    APP_VCOM_DEV_ENTITY_STRU *pstDev,
    VOS_UINT8                 ucIndex
)
{
    VOS_INT                             iErr;
    dev_t                               ulDevno;
    static struct class                *pstCom_class;
    APP_VCOM_DEV_CTX_STRU              *pstVcomCtx;

    pstVcomCtx = APP_VCOM_GetVcomCtxAddr(ucIndex);

    ulDevno = MKDEV(pstVcomCtx->ulAppVcomMajorId, ucIndex);

    cdev_init(&pstDev->stAppVcomDev, &g_stOperations_Fops);

    iErr = cdev_add(&pstDev->stAppVcomDev, ulDevno, 1);
    if (iErr)
    {
        APP_VCOM_TRACE_ERR(ucIndex, "APP_VCOM_Setup cdev_add error! ");
        return;
    }

#if (VOS_OS_VER == VOS_WIN32)

#else
    pstCom_class = class_create(THIS_MODULE, pstVcomCtx->aucAppVcomName);

    device_create(pstCom_class,
                  NULL,
                  MKDEV(pstVcomCtx->ulAppVcomMajorId, ucIndex),
                  "%s",
                  pstVcomCtx->aucAppVcomName);
#endif

    return;
}

/*****************************************************************************
 函 数 名  : APP_VCOM_Init
 功能描述  : 虚拟串口初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_OK    成功
             VOS_ERR   失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : sunshaohua
    修改内容   : 新生成函数
  2.日    期   : 2012年11月23日
    作    者   : z00220246
    修改内容   : DSDA Phase I
  3.日    期   : 2013年08月01日
    作    者   : j00177245
    修改内容   : 调整appvcom初始化时序
  4.日    期   : 2013年10月25日
    作    者   : j00177245
    修改内容   : 增加appvcom可维可测记录到文件
  5.日    期   : 2014年4月22日
    作    者   : A00165503
    修改内容   : DTS2014042208020: 增加写信号量初始化
*****************************************************************************/
VOS_INT __init APP_VCOM_Init(VOS_VOID)
{
    VOS_INT                             iResult1;
    VOS_INT                             iResult2;
    dev_t                               ulDevno;
    VOS_UINT8                           ucIndex;
    APP_VCOM_DEV_CTX_STRU              *pstVcomCtx;
    APP_VCOM_DEV_ENTITY_STRU           *pstVcomDevp;

    printk("APP_VCOM_Init entry,%u",VOS_GetSlice());

    pstVcomCtx = VOS_NULL_PTR;
    pstVcomDevp  = VOS_NULL_PTR;

    /* 初始化可维可测全局变量 */
    VOS_MemSet(&g_stAppVcomDebugInfo, 0x0, sizeof(g_stAppVcomDebugInfo));

    VOS_MemSet(&g_stAppVcomDebugCfg, 0x0, sizeof(g_stAppVcomDebugCfg));

    /* 初始化虚拟设备 */
    for (ucIndex = 0; ucIndex < APP_VCOM_MAX_NUM; ucIndex++)
    {
        /* 初始化全局变量 */
        APP_VCOM_InitSpecCtx(ucIndex);

        /* 获取全局变量指针 */
        pstVcomCtx = APP_VCOM_GetVcomCtxAddr(ucIndex);

        /* 将设备号转换成dev_t 类型 */
        ulDevno = MKDEV(pstVcomCtx->ulAppVcomMajorId, ucIndex);

        iResult1 = register_chrdev_region(ulDevno, 1, pstVcomCtx->aucAppVcomName);

        /* 注册失败则动态申请设备号 */
        if (iResult1 < 0)
        {
            iResult2 = alloc_chrdev_region(&ulDevno, 0, 1, pstVcomCtx->aucAppVcomName);

            if (iResult2 < 0 )
            {
                return VOS_ERROR;
            }

            pstVcomCtx->ulAppVcomMajorId = MAJOR(ulDevno);
        }

        /* 动态申请设备结构体内存 */
        pstVcomCtx->pstAppVcomDevEntity = kmalloc(sizeof(APP_VCOM_DEV_ENTITY_STRU) , GFP_KERNEL);

        if (VOS_NULL_PTR == pstVcomCtx->pstAppVcomDevEntity)
        {
            /* 去注册该设备，返回错误 */
            unregister_chrdev_region(ulDevno, 1);
            APP_VCOM_TRACE_ERR(ucIndex, "APP_VCOM_Init malloc device Entity fail. ");
            return VOS_ERROR;
        }

        /* 获取设备实体指针 */
        pstVcomDevp = pstVcomCtx->pstAppVcomDevEntity;

        VOS_MemSet(pstVcomDevp, 0, sizeof(APP_VCOM_DEV_ENTITY_STRU));

        pstVcomDevp->pucAppVcomMem = kmalloc(g_astAppVcomCogfigTab[ucIndex].ulAppVcomMemSize, GFP_KERNEL);

        if (VOS_NULL_PTR == pstVcomDevp->pucAppVcomMem)
        {
            /* 去注册该设备，返回错误 */
            unregister_chrdev_region(ulDevno, 1);
            APP_VCOM_TRACE_ERR(ucIndex, "APP_VCOM_Init malloc device buff fail. ");
            kfree(pstVcomCtx->pstAppVcomDevEntity);
            pstVcomCtx->pstAppVcomDevEntity = VOS_NULL_PTR;
            return VOS_ERROR;
        }

        init_waitqueue_head(&pstVcomDevp->Read_Wait);
        VOS_MemSet(pstVcomDevp->acWakeLockName, 0x00, APP_VCOM_RD_WAKE_LOCK_NAME_LEN);
        snprintf(pstVcomDevp->acWakeLockName, APP_VCOM_RD_WAKE_LOCK_NAME_LEN, "appvcom%d_rd_wake", ucIndex);
        pstVcomDevp->acWakeLockName[APP_VCOM_RD_WAKE_LOCK_NAME_LEN - 1] = '\0';
        wake_lock_init(&pstVcomDevp->stRdWakeLock, WAKE_LOCK_SUSPEND, pstVcomDevp->acWakeLockName);

        APP_VCOM_Setup(pstVcomDevp, ucIndex);

        /* 创建信号量 */
        sema_init(&pstVcomDevp->stMsgSendSem,1);
        sema_init(&pstVcomDevp->stWrtSem, 1);
    }


    printk("APP_VCOM_Init eixt,%u",VOS_GetSlice());

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : APP_VCOM_Release
 功能描述  : 文件关闭函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_OK    成功
             VOS_ERROR   失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月14日
    作    者   : sunshaohua
    修改内容   : 新生成函数
*****************************************************************************/
int APP_VCOM_Release(
    struct inode                       *inode,
    struct file                        *filp
)
{
    VOS_UINT                            ulDevMajor;
    VOS_UINT8                           ucIndex;
    APP_VCOM_DEV_CTX_STRU              *pstVcomCtx;

    if (VOS_NULL_PTR == inode || VOS_NULL_PTR == filp)
    {
        return VOS_ERROR;
    }

    /* 获取主设备号 */
    ulDevMajor = imajor(inode);

    /* 根据主设备号得到设备在全局变量中的索引值 */
    ucIndex = APP_VCOM_GetIndexFromMajorDevId(ulDevMajor);

    if (ucIndex >= APP_VCOM_MAX_NUM)
    {
        APP_VCOM_TRACE_ERR(ucIndex, "APP_VCOM_Release ucIndex is error. ");
        return VOS_ERROR;
    }

    /* 获取VCOM全局变量 */
    pstVcomCtx = APP_VCOM_GetVcomCtxAddr(ucIndex);

    if (VOS_NULL_PTR == pstVcomCtx->pstAppVcomDevEntity)
    {
        APP_VCOM_TRACE_ERR(ucIndex, "APP_VCOM_Release VcomDevEntity is NULL. ");
        return VOS_ERROR;
    }

    /* 将设备结构体指针赋值给文件私有数据指针 */
    filp->private_data = pstVcomCtx->pstAppVcomDevEntity;

    APP_VCOM_TRACE_INFO(ucIndex, "APP_VCOM_Release enter. ");

    if(NULL != pstVcomCtx->pEventFunc)
    {
		(VOS_VOID)(pstVcomCtx->pEventFunc(APP_VCOM_EVT_RELEASE));
    }

    pstVcomCtx->pstAppVcomDevEntity->ulIsDeviceOpen = VOS_FALSE;
    wake_unlock(&pstVcomCtx->pstAppVcomDevEntity->stRdWakeLock);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : APP_VCOM_Open
 功能描述  : 文件打开函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_OK    成功
             VOS_ERROR   失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月14日
    作    者   : sunshaohua
    修改内容   : 新生成函数
  2.日    期   : 2012年11月23日
    作    者   : z00220246
    修改内容   : DSDA Phase I
*****************************************************************************/
int APP_VCOM_Open(
    struct inode                       *inode,
    struct file                        *filp
)
{
    VOS_UINT                            ulDevMajor;
    VOS_UINT8                           ucIndex;
    APP_VCOM_DEV_CTX_STRU              *pstVcomCtx;

    if (VOS_NULL_PTR == inode || VOS_NULL_PTR == filp)
    {
        return VOS_ERROR;
    }

    /* 获取主设备号 */
    ulDevMajor = imajor(inode);

    /* 根据主设备号得到设备在全局变量中的索引值 */
    ucIndex = APP_VCOM_GetIndexFromMajorDevId(ulDevMajor);

    if (ucIndex >= APP_VCOM_MAX_NUM)
    {
        APP_VCOM_TRACE_ERR(ucIndex, "APP_VCOM_Open ucIndex is error. ");
        return VOS_ERROR;
    }

    /* 获取VCOM全局变量 */
    pstVcomCtx = APP_VCOM_GetVcomCtxAddr(ucIndex);

    if (VOS_NULL_PTR == pstVcomCtx->pstAppVcomDevEntity)
    {
        APP_VCOM_TRACE_ERR(ucIndex, "APP_VCOM_Open VcomDevEntity is NULL. ");
        return VOS_ERROR;
    }

    /* 将设备结构体指针赋值给文件私有数据指针 */
    filp->private_data = pstVcomCtx->pstAppVcomDevEntity;

    APP_VCOM_TRACE_INFO(ucIndex, "APP_VCOM_Open enter. ");

    if(NULL != pstVcomCtx->pEventFunc)
    {
        (VOS_VOID)(pstVcomCtx->pEventFunc(APP_VCOM_EVT_OPEN));
    }

    pstVcomCtx->pstAppVcomDevEntity->ulIsDeviceOpen = VOS_TRUE;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : APP_VCOM_Read
 功能描述  : 虚拟串口读操作
 输入参数  : struct file *stFilp
             char __user *buf
             size_t       count
             loff_t      *ppos
 输出参数  : 无
 返 回 值  : ssize_t
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : sunshaohua
    修改内容   : 新生成函数
  2.日    期   : 2012年11月23日
    作    者   : z00220246
    修改内容   : DSDA Phase I
  3.日    期   : 2013年08月01日
    作    者   : j00177245
    修改内容   : 调整appvcom初始化时序
  4.日    期   : 2013年10月28日
    作    者   : f00179208
    修改内容   : DTS2013102801414:手机打电话及挂电话慢，上层读VCOM会读到0字节的长度
*****************************************************************************/
ssize_t APP_VCOM_Read(
    struct file                        *stFilp,
    char __user                        *buf,
    size_t                              count,
    loff_t                             *ppos
)
{
    APP_VCOM_DEV_ENTITY_STRU           *pstVcomDev;
    struct cdev                        *pstCdev;
    VOS_UINT                            ulDevMajor;
    VOS_UINT8                           ucIndex;
    APP_VCOM_DEV_CTX_STRU              *pstVcomCtx;

    /* 获得设备结构体指针 */
    pstVcomDev = stFilp->private_data;

    /* 获得设备主设备号 */
    pstCdev = &(pstVcomDev->stAppVcomDev);
    ulDevMajor = MAJOR(pstCdev->dev);

    /* 获得设备在全局变量中的索引值 */
    ucIndex = APP_VCOM_GetIndexFromMajorDevId(ulDevMajor);

    if (ucIndex >= APP_VCOM_MAX_NUM)
    {
        return APP_VCOM_ERROR;
    }

    pstVcomCtx = APP_VCOM_GetVcomCtxAddr(ucIndex);

    APP_VCOM_TRACE_INFO(ucIndex, "APP_VCOM_Read, read count:%d, current_len:%d. ", count, pstVcomDev->current_len);
    APP_VCOM_TRACE_INFO(ucIndex, "APP_VCOM_Read, f_flags:%d. ", stFilp->f_flags);
    APP_VCOM_TRACE_INFO(ucIndex, "APP_VCOM_Read, wait_event 111, flag:%d. ", pstVcomDev->ulReadWakeUpFlg);

    if (stFilp->f_flags & O_NONBLOCK)
    {
        return APP_VCOM_ERROR;
    }

#if (VOS_OS_VER == VOS_WIN32)

#else
    /*lint -e730 修改人:l60609;检视人:z60575;原因:两个线程会同时写该全局变量  */
    if (wait_event_interruptible(pstVcomDev->Read_Wait, (pstVcomDev->current_len != 0)))
    {
        return -ERESTARTSYS;
    }
    /*lint +e730 修改人:l60609;检视人:z60575;原因:两个线程会同时写该全局变量  */
#endif

    if (0 == pstVcomDev->current_len)
    {
        g_stAppVcomDebugInfo.ulReadLenErr[ucIndex]++;
    }

    APP_VCOM_TRACE_INFO(ucIndex, "APP_VCOM_Read, wait_event 222,flag:%d. ", pstVcomDev->ulReadWakeUpFlg);

    /* 获取信号量 */
    down(&pstVcomCtx->pstAppVcomDevEntity->stMsgSendSem);

    if (count > pstVcomDev->current_len)
    {
        count = pstVcomDev->current_len;
    }

    if (copy_to_user(buf, pstVcomDev->pucAppVcomMem, (VOS_ULONG)count))
    {
        APP_VCOM_TRACE_ERR(ucIndex, "APP_VCOM_Read, copy_to_user fail. ");

        /* 释放信号量 */
        up(&pstVcomCtx->pstAppVcomDevEntity->stMsgSendSem);
        return APP_VCOM_ERROR;
    }

    if ((pstVcomDev->current_len - count) > 0)
    {
        /* FIFO数据前移 */
        memmove(pstVcomDev->pucAppVcomMem, (pstVcomDev->pucAppVcomMem + count), (pstVcomDev->current_len - count));
        APP_VCOM_TRACE_INFO(ucIndex, "APP_VCOM_Read, FIFO move. ");
    }

    /* 有效数据长度减小*/
    pstVcomDev->current_len -= count;

    APP_VCOM_TRACE_INFO(ucIndex, "APP_VCOM_Read, read %d bytes, current_len:%d. ", count, pstVcomDev->current_len);

    if (0 == pstVcomDev->current_len)
    {
        APP_VCOM_TRACE_NORM(ucIndex, "APP_VCOM_Send: read all data. ");
        wake_unlock(&pstVcomDev->stRdWakeLock);
    }

    /* 释放信号量 */
    up(&pstVcomCtx->pstAppVcomDevEntity->stMsgSendSem);

    return (ssize_t)count;
}

/*****************************************************************************
 函 数 名  : APP_VCOM_Write
 功能描述  : 虚拟串口写操作
 输入参数  : struct file       *stFilp
             const char __user *buf
             size_t             count
             loff_t            *ppos
 输出参数  : 无
 返 回 值  : ssize_t
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : sunshaohua
    修改内容   : 新生成函数
  2.日    期   : 2012年11月23日
    作    者   : z00220246
    修改内容   : DSDA Phase I
  3.日    期   : 2013年10月25日
    作    者   : j00177245
    修改内容  :  增加appvcom可维可测记录到文件
  4.日    期   : 2014年4月22日
    作    者   : A00165503
    修改内容   : DTS2014042208020: 增加APPVCOM9和APPVCOM12的缓存处理
*****************************************************************************/
ssize_t APP_VCOM_Write(
    struct file                        *stFilp,
    const char __user                  *buf,
    size_t                              count,
    loff_t                             *ppos
)
{
    VOS_UINT8                          *pucDataBuf;
    VOS_INT                             iRst;
    APP_VCOM_DEV_ENTITY_STRU           *pstVcomDev;
    struct cdev                        *pstCdev;
    VOS_UINT                            ulDevMajor;
    VOS_UINT8                           ucIndex;
    APP_VCOM_DEV_CTX_STRU              *pstVcomCtx;

    /* 获得设备结构体指针 */
    pstVcomDev = stFilp->private_data;

    /* 获得设备主设备号 */
    pstCdev = &(pstVcomDev->stAppVcomDev);
    ulDevMajor = MAJOR(pstCdev->dev);

    /* 获得设备在全局变量中的索引值 */
    ucIndex = APP_VCOM_GetIndexFromMajorDevId(ulDevMajor);

    if(ucIndex >= APP_VCOM_MAX_NUM)
    {
        APP_VCOM_TRACE_ERR(ucIndex, "APP_VCOM_Write, ucIndex fail. ");
        return APP_VCOM_ERROR;
    }

    if (NULL == buf)
    {
        APP_VCOM_TRACE_ERR(ucIndex, "APP_VCOM_Write, buf is null ");
        return APP_VCOM_ERROR;
    }

    if (count > APP_VCOM_MAX_DATA_LENGTH)
    {
        APP_VCOM_TRACE_ERR(ucIndex, "APP_VCOM_Write, count is %d, to large", count);
        return APP_VCOM_ERROR;
    }

    /* 获得全局变量地址 */
    pstVcomCtx = APP_VCOM_GetVcomCtxAddr(ucIndex);

    /* 申请内存 */
    pucDataBuf = kmalloc(count, GFP_KERNEL);
    if (VOS_NULL_PTR == pucDataBuf )
    {
        APP_VCOM_TRACE_ERR(ucIndex, "APP_VCOM_Write, kmalloc fail. ");

        return APP_VCOM_ERROR;
    }

    /* buffer清零 */
    VOS_MemSet(pucDataBuf, 0x00, (VOS_SIZE_T)count);

    if (copy_from_user(pucDataBuf, buf, (VOS_ULONG)count))
    {
        APP_VCOM_TRACE_ERR(ucIndex, "APP_VCOM_Write, copy_from_user fail. ");

        kfree(pucDataBuf);
        return APP_VCOM_ERROR;
    }

#if (FEATURE_ON == FEATURE_VCOM_EXT)
    if ((APP_VCOM_DEV_INDEX_9 == ucIndex) || (APP_VCOM_DEV_INDEX_12 == ucIndex))
    {
        down(&pstVcomCtx->pstAppVcomDevEntity->stWrtSem);

        if (VOS_NULL_PTR != pstVcomCtx->pstAppVcomDevEntity->pucWrtBuffer)
        {
            APP_VCOM_TRACE_NORM(ucIndex, "APP_VCOM_Write: free buff. ");

            kfree(pstVcomCtx->pstAppVcomDevEntity->pucWrtBuffer);
            pstVcomCtx->pstAppVcomDevEntity->pucWrtBuffer   = VOS_NULL_PTR;
            pstVcomCtx->pstAppVcomDevEntity->ulWrtBufferLen = 0;
        }

        if (VOS_NULL_PTR == pstVcomCtx->pSendUlAtFunc)
        {
            APP_VCOM_TRACE_NORM(ucIndex, "APP_VCOM_Write: save buff. ");

            pstVcomCtx->pstAppVcomDevEntity->pucWrtBuffer   = pucDataBuf;
            pstVcomCtx->pstAppVcomDevEntity->ulWrtBufferLen = count;
            up(&pstVcomCtx->pstAppVcomDevEntity->stWrtSem);
            return (ssize_t)count;
        }

        up(&pstVcomCtx->pstAppVcomDevEntity->stWrtSem);
    }
#endif

    /* 调用回调函数处理buf中的AT码流*/
    if (VOS_NULL_PTR == pstVcomCtx->pSendUlAtFunc)
    {
        APP_VCOM_TRACE_ERR(ucIndex, "APP_VCOM_Write, pSendUlAtFunc is null. ");
        kfree(pucDataBuf);
        return APP_VCOM_ERROR;
    }

    iRst = pstVcomCtx->pSendUlAtFunc(ucIndex, pucDataBuf, (VOS_UINT32)count);
    if (VOS_OK != iRst)
    {
        g_stAppVcomDebugInfo.ulAtCallBackErr[ucIndex]++;
        APP_VCOM_TRACE_ERR(ucIndex, "APP_VCOM_Write, AT_RcvFromAppCom fail. ");

        kfree(pucDataBuf);

        return APP_VCOM_ERROR;
    }

    APP_VCOM_TRACE_INFO(ucIndex, "APP_VCOM_Write, write %d bytes, AT_RcvFromAppCom Success.",count);

    /* 释放内存 */
    kfree(pucDataBuf);

    return (ssize_t)count;
}

/*****************************************************************************
 函 数 名  : APP_VCOM_Poll
 功能描述  : 虚拟串口POLL
 输入参数  : struct file *fp
             struct poll_table_struct *wait
 输出参数  : 无
 返 回 值  : 0
             POLLIN | POLLRDNORM
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月6日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
unsigned int APP_VCOM_Poll(struct file *fp, struct poll_table_struct *wait)
{
    APP_VCOM_DEV_ENTITY_STRU           *pstVcomDev = VOS_NULL_PTR;
    unsigned int                        mask = 0;

    struct cdev                        *pstCdev;
    VOS_UINT                            ulDevMajor;
    VOS_UINT8                           ucIndex;

    pstVcomDev = fp->private_data;

    pstCdev = &(pstVcomDev->stAppVcomDev);
    ulDevMajor = MAJOR(pstCdev->dev);
    ucIndex = APP_VCOM_GetIndexFromMajorDevId(ulDevMajor);

    poll_wait(fp, &pstVcomDev->Read_Wait, wait);

    if (0 != pstVcomDev->current_len)
    {
        mask |= POLLIN | POLLRDNORM;
    }

    APP_VCOM_TRACE_INFO(ucIndex, "APP_VCOM_Poll, mask = %d. ", mask);

    return mask;
}

/*****************************************************************************
 函 数 名  : APP_VCOM_Send
 功能描述  : 接收AT模块的码流，写入设备中
 输入参数  : APP_VCOM_DEV_INDEX_UINT8 enDevIndex
             VOS_UINT8  *pData
             VOS_UINT32 uslength
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月20日
    作    者   : lijun 00171473
    修改内容   : 新生成函数
  2.日    期   : 2012年11月23日
    作    者   : z00220246
    修改内容   : DSDA Phase I
  3.日    期   : 2013年08月01日
    作    者   : j00177245
    修改内容   : 调整appvcom初始化时序
  4.日    期   : 2013年10月25日
    作    者   : j00177245
    修改内容   : 增加appvcom可维可测记录到文件
  5.日    期   : 2014年4月22日
    作    者   : A00165503
    修改内容   : DTS2014042208020: 增加APPVCOM9和APPVCOM12的缓存处理
*****************************************************************************/
VOS_UINT32  APP_VCOM_Send (
    APP_VCOM_DEV_INDEX_UINT8            enDevIndex,
    VOS_UINT8                          *pData,
    VOS_UINT32                          uslength
)
{
    APP_VCOM_DEV_ENTITY_STRU           *pstVcomDev;
#if (FEATURE_ON == FEATURE_VCOM_EXT)
    APP_VCOM_DEV_CTX_STRU              *pstVcomCtx;
#endif

    if (enDevIndex >= APP_VCOM_MAX_NUM)
    {
        g_stAppVcomDebugInfo.ulDevIndexErr++;
        APP_VCOM_TRACE_ERR(enDevIndex, "APP_VCOM_Send, enDevIndex is error. ");
        return VOS_ERR;
    }

#if (FEATURE_ON == FEATURE_VCOM_EXT)
    pstVcomCtx = APP_VCOM_GetVcomCtxAddr(enDevIndex);
    if (VOS_NULL_PTR == pstVcomCtx)
    {
        APP_VCOM_TRACE_ERR(enDevIndex, "APP_VCOM_Send, pstVcomCtx is null. ");
        return VOS_ERR;
    }
#endif

    /* 获得设备实体指针 */
    pstVcomDev = APP_VCOM_GetAppVcomDevEntity(enDevIndex);
    if (VOS_NULL_PTR == pstVcomDev)
    {
        g_stAppVcomDebugInfo.ulVcomDevErr[enDevIndex]++;
        APP_VCOM_TRACE_ERR(enDevIndex, "APP_VCOM_Send, pstVcomDev is null. ");
        return VOS_ERR;
    }

#if (FEATURE_ON == FEATURE_VCOM_EXT)
    if ((APP_VCOM_DEV_INDEX_9 == enDevIndex) || (APP_VCOM_DEV_INDEX_12 == enDevIndex))
    {
        down(&pstVcomDev->stWrtSem);

        if (VOS_NULL_PTR != pstVcomDev->pucWrtBuffer)
        {
            if (VOS_NULL_PTR != pstVcomCtx->pSendUlAtFunc)
            {
                APP_VCOM_TRACE_NORM(enDevIndex, "APP_VCOM_Send: handle buff. ");

                (VOS_VOID)pstVcomCtx->pSendUlAtFunc(enDevIndex,
                                        pstVcomDev->pucWrtBuffer,
                                        pstVcomDev->ulWrtBufferLen);

                kfree(pstVcomDev->pucWrtBuffer);
                pstVcomDev->pucWrtBuffer   = VOS_NULL_PTR;
                pstVcomDev->ulWrtBufferLen = 0;
            }
        }

        up(&pstVcomDev->stWrtSem);
    }
#endif

    APP_VCOM_TRACE_INFO(enDevIndex, "APP_VCOM_Send, uslength:%d, current_len:%d. ", uslength, pstVcomDev->current_len);

    /* 获取信号量 */
    down(&pstVcomDev->stMsgSendSem);

    /* 队列满则直接返回 */
    if (g_astAppVcomCogfigTab[enDevIndex].ulAppVcomMemSize == pstVcomDev->current_len)
    {
        APP_VCOM_TRACE_NORM(enDevIndex, "APP_VCOM_Send: VCOM MEM FULL. ");
        g_stAppVcomDebugInfo.ulMemFullErr[enDevIndex]++;
        up(&pstVcomDev->stMsgSendSem);
        return VOS_ERR;
    }

    /* 发送数据大于剩余Buffer大小 */
    if (uslength > (g_astAppVcomCogfigTab[enDevIndex].ulAppVcomMemSize - pstVcomDev->current_len))
    {
        APP_VCOM_TRACE_NORM(enDevIndex, "APP_VCOM_Send: data more than Buffer. ");
        uslength = g_astAppVcomCogfigTab[enDevIndex].ulAppVcomMemSize - (VOS_UINT32)pstVcomDev->current_len;
    }

    /* 复制到BUFFER */
    memcpy(pstVcomDev->pucAppVcomMem + pstVcomDev->current_len, pData, uslength);
    pstVcomDev->current_len += uslength;

    APP_VCOM_TRACE_INFO(enDevIndex, "APP_VCOM_Send, written %d byte(s), new len: %d. ", uslength, pstVcomDev->current_len);

    APP_VCOM_TRACE_INFO(enDevIndex, "APP_VCOM_Send, IsDeviceOpen: %d. ", pstVcomDev->ulIsDeviceOpen);
    /*lint -e713*/
    if (VOS_TRUE == pstVcomDev->ulIsDeviceOpen)
    {
        wake_lock_timeout(&pstVcomDev->stRdWakeLock, msecs_to_jiffies(APP_VCOM_READ_WAKE_LOCK_LEN));
    }
    /*lint +e713*/

    /* 释放信号量 */
    up(&pstVcomDev->stMsgSendSem);
#ifdef __PC_UT__

#else
    wake_up_interruptible(&pstVcomDev->Read_Wait);
#endif

    if (0 == pstVcomDev->current_len)
    {
        g_stAppVcomDebugInfo.ulSendLenErr[enDevIndex]++;
    }

    APP_VCOM_TRACE_INFO(enDevIndex, "APP_VCOM_Send, wakeup. ");
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : APP_VCOM_ShowDebugInfo
 功能描述  : 打印appvcom的可维可测信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年09月21日
    作    者   : j00174725
    修改内容  : 新增函数
*****************************************************************************/
VOS_VOID APP_VCOM_ShowDebugInfo(VOS_VOID)
{
    int                                 i;
    (VOS_VOID)vos_printf("App Vcom Debug Info:");
    (VOS_VOID)vos_printf("Index Err: %d\r\n", g_stAppVcomDebugInfo.ulDevIndexErr);

    for (i = 0; i < APP_VCOM_MAX_NUM; i++)
    {
        (VOS_VOID)vos_printf("\r\n");
        (VOS_VOID)vos_printf("AppVcom[%d] Callback Function Return Err Num: %d\r\n", i, g_stAppVcomDebugInfo.ulAtCallBackErr[i]);
        (VOS_VOID)vos_printf("AppVcom[%d] Mem Full Num:                     %d\r\n", i, g_stAppVcomDebugInfo.ulMemFullErr[i]);
        (VOS_VOID)vos_printf("AppVcom[%d] Read Data Length = 0 Num:         %d\r\n", i, g_stAppVcomDebugInfo.ulReadLenErr[i]);
        (VOS_VOID)vos_printf("AppVcom[%d] Send Data Length = 0 Num:         %d\r\n", i, g_stAppVcomDebugInfo.ulSendLenErr[i]);
        (VOS_VOID)vos_printf("AppVcom[%d] Get App Vcom Dev Entity Err Num:  %d\r\n", i, g_stAppVcomDebugInfo.ulVcomDevErr[i]);
    }
}

#if (VOS_WIN32 == VOS_OS_VER)
/*****************************************************************************
 函 数 名  : APP_VCOM_FreeMem
 功能描述  : APPVCOM 分配内存释放函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月24日
    作    者   : j00174725
    修改内容  : 新增函数
*****************************************************************************/
VOS_VOID APP_VCOM_FreeMem(VOS_VOID)
{
    APP_VCOM_DEV_CTX_STRU              *pstVcomCtx;
    VOS_UINT8                           ucIndex;
    APP_VCOM_DEV_ENTITY_STRU           *pstVcomDevp;

    pstVcomCtx = VOS_NULL_PTR;
    pstVcomDevp  = VOS_NULL_PTR;

   for (ucIndex = 0; ucIndex < APP_VCOM_MAX_NUM; ucIndex++)
    {
        pstVcomCtx = APP_VCOM_GetVcomCtxAddr(ucIndex);

        pstVcomDevp = pstVcomCtx->pstAppVcomDevEntity;

        if (VOS_NULL_PTR != pstVcomDevp->pucAppVcomMem)
        {
            free(pstVcomDevp->pucAppVcomMem);
            pstVcomDevp->pucAppVcomMem = VOS_NULL_PTR;

        }

        if(VOS_NULL_PTR != pstVcomCtx->pstAppVcomDevEntity)
        {
            free(pstVcomCtx->pstAppVcomDevEntity);
            pstVcomCtx->pstAppVcomDevEntity = VOS_NULL_PTR;
        }
    }

   return;
}
#endif

/*****************************************************************************
 函 数 名  : APP_VCOM_SendDebugNvCfg
 功能描述  : 接收关于VCOM Debug 配置相关的NV项
 输入参数  : VOS_UINT32 ulAppVcomDebugNvCfg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月03日
    作    者   : n00269697
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID APP_VCOM_SendDebugNvCfg(
    VOS_UINT32                          ulPortIdMask,
    VOS_UINT32                          ulDebugLevel
)
{
    g_stAppVcomDebugCfg.ulPortIdMask = ulPortIdMask;
    g_stAppVcomDebugCfg.ulDebugLevel = ulDebugLevel;
}

/*****************************************************************************
 函 数 名  : APP_VCOM_MNTN_LogPrintf
 功能描述  : APP VCOM可维可测LOG输出
 输入参数  : VOS_CHAR *pcFmt
             ...
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月03日
    作    者   : N00269697
    修改内容   : 新生成函数
*****************************************************************************/
/*lint -esym(960,69)*/
VOS_VOID APP_VCOM_MNTN_LogPrintf(VOS_CHAR *pcFmt, ...)
{
    VOS_CHAR                            acBuf[APP_VCOM_TRACE_BUF_LEN] = {0};
    VOS_UINT32                          ulPrintLength = 0;

    /* 格式化输出BUFFER */
    APP_VCOM_LOG_FORMAT(ulPrintLength, acBuf, APP_VCOM_TRACE_BUF_LEN, pcFmt);

#if (VOS_OS_VER == VOS_LINUX)
    printk(KERN_ERR "%s", acBuf);
#endif
    return;
}
/*lint +esym(960,69)*/

#if (VOS_LINUX == VOS_OS_VER)
#if (FEATURE_ON == FEATURE_DELAY_MODEM_INIT)
module_init(APP_VCOM_Init);
#endif
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


