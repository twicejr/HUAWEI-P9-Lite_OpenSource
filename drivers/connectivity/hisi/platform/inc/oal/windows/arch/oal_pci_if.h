

#ifndef __OAL_WINDOWS_PCI_IF_H__
#define __OAL_WINDOWS_PCI_IF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)

#include "oal_types.h"
#include "oal_util.h"
#include "oal_hardware.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_OAL_PCI_IF_H

/*****************************************************************************
  2 枚举定义
*****************************************************************************/

/*****************************************************************************
  3 全局变量声明
*****************************************************************************/


/*****************************************************************************
  4 宏定义
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

OAL_STATIC OAL_INLINE oal_int32  oal_pci_register_driver(oal_pci_driver_stru *pst_drv)
{
    return OAL_SUCC;
}


OAL_STATIC OAL_INLINE oal_int32  oal_pci_unregister_driver(oal_pci_driver_stru *pst_drv)
{
    return OAL_SUCC;
}


OAL_STATIC OAL_INLINE oal_int32  oal_pci_enable_device(oal_pci_dev_stru *pst_dev)
{
    return OAL_SUCC;
}


OAL_STATIC OAL_INLINE oal_void  oal_pci_disable_device(oal_pci_dev_stru *pst_dev)
{

}


OAL_STATIC OAL_INLINE oal_int32  oal_pci_read_config_byte(oal_pci_dev_stru *pst_dev, oal_int32 ul_where, oal_uint8 *puc_val)
{
    return 0;
}


OAL_STATIC OAL_INLINE oal_int32  oal_pci_read_config_word(oal_pci_dev_stru *pst_dev, oal_int32 ul_where, oal_uint16 *pus_val)
{
    return 0;
}


OAL_STATIC OAL_INLINE oal_int32  oal_pci_read_config_dword(oal_pci_dev_stru *pst_dev, oal_int32 ul_where, oal_uint32 *pul_val)
{
    return 0;
}


OAL_STATIC OAL_INLINE oal_int32  oal_pci_write_config_byte(oal_pci_dev_stru *pst_dev, oal_int32 ul_where, oal_uint8 uc_val)
{
    return 0;
}


OAL_STATIC OAL_INLINE oal_int32  oal_pci_write_config_word(oal_pci_dev_stru *pst_dev, oal_int32 ul_where, oal_uint16 us_val)
{
    return 0;
}


OAL_STATIC OAL_INLINE oal_int32  oal_pci_write_config_dword(oal_pci_dev_stru *pst_dev, oal_int32 ul_where, oal_uint32 ul_val)
{
    return 0;
}


OAL_STATIC OAL_INLINE oal_uint  oal_pci_resource_start(oal_pci_dev_stru *pst_dev, oal_int32 l_bar)
{
    return 0x40000000;
}


OAL_STATIC OAL_INLINE oal_uint  oal_pci_resource_end(oal_pci_dev_stru *pst_dev, oal_int32 l_bar)
{
    return 0x40000000 + 0x1000;
}


OAL_STATIC OAL_INLINE oal_uint32 oal_pci_resource_len(oal_pci_dev_stru *pst_dev, oal_int32 l_bar)
{
    return 0x1000;
}



OAL_STATIC OAL_INLINE oal_int oal_pci_save_state(oal_pci_dev_stru *pst_dev)
{
    return OAL_SUCC;

}



OAL_STATIC OAL_INLINE oal_int oal_pci_restore_state(oal_pci_dev_stru *pst_dev)
{
    return OAL_SUCC;
}


OAL_STATIC OAL_INLINE oal_void  oal_pci_set_drvdata(oal_pci_dev_stru *pst_dev, oal_void *p_data)
{

}


OAL_STATIC OAL_INLINE void *oal_pci_get_drvdata(oal_pci_dev_stru *pst_dev)
{
    return 0;
}

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_pci_if.h */
