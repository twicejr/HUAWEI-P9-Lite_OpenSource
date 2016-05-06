/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : usb_api.c
  版 本 号   : 初稿
  作    者   : 夏青 00195127
  生成日期   : 2012年9月15日
  最近修改   :
  功能描述   : USB模块对外接口实现,接口定义参见接口文档
  函数列表   :
  修改历史   :
  1.日    期   : 2012年9月15日
    作    者   : 夏青 00195127
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  <linux/slab.h>
#include  <linux/kernel.h>
#include  <linux/module.h>
#include  <drv_usb_if.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
PNP_CALLBACK_STACK* pEnableStack = NULL;
PNP_CALLBACK_STACK* pDisableStack = NULL;
DEFINE_SPINLOCK(enable_lock);
DEFINE_SPINLOCK(disable_lock);
static ACM_HANDLE_COMMAND_CB_T pAcmHandleCmdCB= NULL;
int g_ul_reg_enable_count = 0;
int g_ul_reg_disable_count = 0;
int g_usb_enum_complete = 0;


/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
   与NAS的接口实现，包含打桩实现
*****************************************************************************/

void BSP_USB_Dump_EnableCBStack(void)
{
    PNP_CALLBACK_STACK* pEnableFunc = NULL;
    USB_API_DBG("BSP_USB_Dump_EnableCBStack enter:%d\n",g_ul_reg_enable_count);

    pEnableFunc = pEnableStack;
    while (pEnableFunc)
    {
        USB_API_DBG("BSP_USB_Dump_EnableCBStack :%p\n",pEnableFunc->pCallback);
        pEnableFunc = pEnableFunc->pPre;
    }

    USB_API_DBG("BSP_USB_Dump_EnableCBStack leave:\n");
}

void BSP_USB_Dump_DisableCBStack(void)
{
    PNP_CALLBACK_STACK* pDisableFunc = NULL;
    USB_API_DBG("BSP_USB_Dump_DisableCBStack enter:%d\n",g_ul_reg_disable_count);

    pDisableFunc = pDisableStack;
    while (pDisableFunc)
    {
        USB_API_DBG("BSP_USB_Dump_DisableCBStack :%p\n",pDisableFunc->pCallback);
        pDisableFunc = pDisableFunc->pPre;
    }

    USB_API_DBG("BSP_USB_Dump_DisableCBStack leave:\n");
}

/*****************************************************************************
 函 数 名  : BSP_USB_RegUdiEnableCB
 功能描述  : 协议栈通知USB上层应用打开UDI设备端口
 输入参数  : USB_UDI_ENABLE_CB_T pFunc  : USB使能回调函数指针
 输出参数  : 无
 返 回 值  : unsigned int: 0表示成功 1表示失败,与VOS定义的返回值类型一致
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月15日
    作    者   : 夏青 00195127
    修改内容   : 自V3R2移植函数

*****************************************************************************/
unsigned int BSP_USB_RegUdiEnableCB(USB_UDI_ENABLE_CB_T pFunc)
{
    PNP_CALLBACK_STACK* tmp = NULL;
    PNP_CALLBACK_STACK* new_stack = NULL;
    USB_API_DBG(" BSP_USB_RegUdiEnableCB :%p\n",pFunc);

    g_ul_reg_enable_count++;
    if (NULL == pFunc) {
        USB_API_DBG("pFunc NULL\n");
        return 1;
    }

    new_stack = (PNP_CALLBACK_STACK*) kmalloc(sizeof(PNP_CALLBACK_STACK), M_ZERO);
    if (NULL == new_stack) {
        USB_API_DBG("BSP_USB_RegUdiEnableCB new_stack NULL\n");
        return 1;
    }

    spin_lock(&enable_lock);
    tmp = pEnableStack;
    pEnableStack = new_stack;
    pEnableStack->pPre = tmp;
    pEnableStack->pCallback = pFunc;

    if(g_usb_enum_complete) {
        spin_unlock(&enable_lock);
        pEnableStack->pCallback();
    } else {
        spin_unlock(&enable_lock);
    }

    return 0;
}

/*****************************************************************************
 函 数 名  : BSP_USB_RegUdiDisableCB
 功能描述  : 协议栈通知USB上层应用关闭UDI设备端口
 输入参数  : USB_UDI_DISABLE_CB_T pFunc  : USB使能回调函数指针
 输出参数  : 无
 返 回 值  : unsigned int: 0表示成功 1表示失败,与VOS定义的返回值类型一致
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月15日
    作    者   : 夏青 00195127
    修改内容   : 自V3R2移植函数

*****************************************************************************/
unsigned int BSP_USB_RegUdiDisableCB(USB_UDI_DISABLE_CB_T pFunc)
{
    PNP_CALLBACK_STACK* tmp = NULL;
    PNP_CALLBACK_STACK* new_stack = NULL;
    USB_API_DBG("BSP_USB_RegUdiDisableCB :%p\n",pFunc);

    g_ul_reg_disable_count++;
    if (NULL == pFunc) {
        USB_API_DBG("pFunc NULL\n");
        return 1;
    }
    new_stack = (PNP_CALLBACK_STACK*) kmalloc(sizeof(PNP_CALLBACK_STACK), M_ZERO);
    if (NULL == new_stack) {
        USB_API_DBG("BSP_USB_RegUdiDisableCB new_stack NULL\n");
        return 1;
    }

    spin_lock(&disable_lock);
    tmp = pDisableStack;
    pDisableStack = new_stack;
    pDisableStack->pPre = tmp;
    pDisableStack->pCallback = pFunc;
    spin_unlock(&disable_lock);
    return 0;
}

/*****************************************************************************
 函 数 名  : BSP_USB_UdiEnableNotify
 功能描述  : USB模块调用上层注册回调通知上层USB已经OK，可以打开UDI
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月15日
    作    者   : 夏青 00195127
    修改内容   : 自V3R2移植函数

*****************************************************************************/
void BSP_USB_UdiEnableNotify (void)
{
    PNP_CALLBACK_STACK* pEnableFunc = NULL;
    USB_API_DBG("BSP_USB_UdiEnableNotify enter:\n");

    /* 模拟USB插入通知 */
    spin_lock(&enable_lock);
    g_usb_enum_complete = 1;
    pEnableFunc = pEnableStack;
    while (pEnableFunc)
    {
        spin_unlock(&enable_lock);
        pEnableFunc->pCallback();
        spin_lock(&enable_lock);
        pEnableFunc = pEnableFunc->pPre;
    }
    spin_unlock(&enable_lock);

    USB_API_DBG("BSP_USB_UdiEnableNotify leave:\n");
}

/*****************************************************************************
 函 数 名  : BSP_USB_UdiDisableNotify
 功能描述  : USB模块调用上层注册回调通知上层USB已经关闭，需要关闭UDI
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月15日
    作    者   : 夏青 00195127
    修改内容   : 自V3R2移植函数

*****************************************************************************/
void BSP_USB_UdiDisableNotify (void)
{
    PNP_CALLBACK_STACK* pDisableFunc = NULL;
    USB_API_DBG("BSP_USB_UdiDisableNotify enter:\n");
    /* 模拟USB插入通知 */
    spin_lock(&disable_lock);
    pDisableFunc = pDisableStack;
    while (pDisableFunc)
    {
        spin_unlock(&disable_lock);
        pDisableFunc->pCallback();
        spin_lock(&disable_lock);
        pDisableFunc = pDisableFunc->pPre;
    }
    spin_unlock(&disable_lock);
    g_usb_enum_complete = 0;
    USB_API_DBG("BSP_USB_UdiDisableNotify leave:\n");
}

/*****************************************************************************
 函 数 名  : BSP_USB_RegUdiEnableCB
 功能描述  : 用于注册acm控制通道命令处理接口，注册接口在gser_request_complete
             中北调用
 输入参数  : ACM_HANDLE_COMMAND_CB_T pFunc  : acm控制通道命令处理回调函数指针
 输出参数  : 无
 返 回 值  : unsigned int: 0表示成功 1表示失败,与VOS定义的返回值类型一致
 调用函数  :
 被调函数  :
*****************************************************************************/
unsigned int BSP_ACM_RegCmdHandle(ACM_HANDLE_COMMAND_CB_T pFunc)
{
    if (NULL == pFunc)
    {
        USB_API_DBG("pFunc NULL\n");
        return 1;
    }

    pAcmHandleCmdCB = pFunc;

    return 0;
}

/*****************************************************************************
 函 数 名  : BSP_ACM_CmdHandle
 功能描述  : 执行acm控制通道命令处理回调接口
 输入参数  : cmd        控制通道命令
             interface  处理命令的接口号
             buf        待处理数据
             size       待处理数据大小

 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :gser_request_complete
*****************************************************************************/
int BSP_ACM_CmdHandle(int cmd, int tty_idx, char *buf, int size)
{
    int ret = 0;
    if (NULL == pAcmHandleCmdCB)
    {
        USB_API_DBG("pFunc NULL\n");
        return -1;
    }

    ret = pAcmHandleCmdCB(cmd, tty_idx, buf, size);
    return ret;
}



/*提供给NAS的接口*/
EXPORT_SYMBOL(BSP_USB_RegUdiEnableCB);
EXPORT_SYMBOL(BSP_USB_RegUdiDisableCB);
EXPORT_SYMBOL(BSP_USB_UdiEnableNotify);
EXPORT_SYMBOL(BSP_USB_UdiDisableNotify);


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
