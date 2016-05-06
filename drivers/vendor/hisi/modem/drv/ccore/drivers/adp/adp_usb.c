//#include "drv_usb.h"

/********************************************************
函数说明： 返回当前设备列表中支持(sel=1)或者不支持(sel=0)PCSC的设备形态值
函数功能:
输入参数：sel
          0: 通过参数dev_type返回当前不带PCSC是设备形态值
          1：通过参数dev_type返回当前带PCSC是设备形态值
输出参数：dev_type 写入需要的设备形态值，如果没有则不写入值。
          NV中存储的设备形态值
输出参数：pulDevType 与ulCurDevType对应的设备形态值，如果没有返回值1。
返回值：
          0：查询到相应的设备形态值；
          1：没有查询到响应的设备形态值。
********************************************************/
int BSP_USB_PcscInfoSet(unsigned int  ulSel, unsigned int  ulCurDevType, unsigned int *pulDevType)
{
    return 0;
}

/*****************************************************************************
 函 数 名  : BSP_USB_GetDiagModeValue
 功能描述  : 获得设备类型
 输入参数  : 无
 输出参数  : ucDialmode:  0 - 使用Modem拨号; 1 - 使用NDIS拨号; 2 - Modem和NDIS共存
              ucCdcSpec:   0 - Modem/NDIS都符合CDC规范; 1 - Modem符合CDC规范;
                           2 - NDIS符合CDC规范;         3 - Modem/NDIS都符合CDC规范
 返 回 值  : VOS_OK/VOS_ERR
*****************************************************************************/
int BSP_USB_GetDiagModeValue(unsigned char *pucDialmode,
                             unsigned char *pucCdcSpec)
{
    return 0;
}

/*****************************************************************************
 函 数 名  : BSP_USB_GetU2diagDefaultValue
 功能描述  : 获得端口默认u2diag值
 输入参数  : 无
 输出参数  : 无
 返回值：   u2diag值

*****************************************************************************/
unsigned int BSP_USB_GetU2diagDefaultValue(void)
{
    return 0;
}


typedef unsigned int (*MNTN_ERRLOGREGFUN)(char * cFileName,unsigned int ulFileId, unsigned int ulLine,
                unsigned int ulErrNo, void * pBuf, unsigned int ulLen);

/*****************************************************************************
 函 数 名  : ErrlogRegFunc
 功能描述  : USB MNTN注册异常日志接口，Porting项目中打桩
             Added by c00204787 for errorlog,20120211
 输入参数  : 无
 输出参数  : 无
 返回值    ：无

*****************************************************************************/
void MNTN_ERRLOG_REG_FUNC(MNTN_ERRLOGREGFUN pRegFunc)
{
    return ;
}


