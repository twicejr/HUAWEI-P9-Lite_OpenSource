

#ifndef __OAL_WINDOWS_GPIO_H__
#define __OAL_WINDOWS_GPIO_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/

OAL_STATIC OAL_INLINE oal_int32 oal_config_gpio_pin(oal_uint32 ulGPIOBaseAddr, oal_uint32 ulGPIOPinBits, oal_uint8 ucInOut, oal_uint8 ucGPIOType)
{
    return 0;
}


OAL_STATIC OAL_INLINE oal_int32 oal_set_gpio_level(oal_uint32 ulGPIOBaseAddr, oal_uint32 ulGpioBit, oal_uint8 ucLevel)
{
    return 0;
}


OAL_STATIC OAL_INLINE oal_int32 oal_set_gpio_trigger_type(oal_uint32 ulGPIOBaseAddr, oal_uint32 ulGpioBit, oal_uint8 ucTrigTypeLevelEdge, oal_uint8 ucTrigTypeHighLow)
{
    return 0;
}


OAL_STATIC OAL_INLINE oal_int32 oal_get_gpio_level(oal_uint32 ulGPIOBaseAddr, oal_uint32 ulGpioBit, oal_uint8 *ucLevel)
{
    return 0;
}

OAL_STATIC OAL_INLINE oal_int32 oal_clear_gpio_int(oal_uint32 ulGPIOBaseAddr, oal_uint32 ulGPIOBit)
{
    return 0;
}


OAL_STATIC OAL_INLINE oal_int32 oal_debounce_gpio_int(oal_uint32 ulGPIOBaseAddr, oal_uint32  ulGPIOBit, oal_uint8 ucDebounceType)
{
    return 0;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_ext_if.h */
