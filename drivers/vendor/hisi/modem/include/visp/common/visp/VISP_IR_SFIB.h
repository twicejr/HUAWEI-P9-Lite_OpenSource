/*************************************************************************
 *
 *              Copyright 2006, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                         VISP_IR_SFIB.H  
 *
 *  Project Code: VISP1.6
 *   Module Name: PPMNG
 *  Date Created: 2006/11/16   
 *        Author: LIUYONG 57500
 *   Description: 这个头文件内容是从VISP SIFB相关的各个头文件抽取IR需要的宏和结构构成，
 *                在后续开发和维护时，需要关注同VISP保持同步!
 *               
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *
 ************************************************************************/
#ifndef _VISP_IR_SFIB_H_
#define _VISP_IR_SFIB_H_

#ifdef  __cplusplus
extern "C"{
#endif

/******************  from sfib6_sh_rm.h************************/
#define SFIB_AM6_NEW_ADDRESS 0
#define SFIB_AM6_DEL_ADDRESS 1

typedef struct tagSFIB_AM6_MSG
{
    ULONG  ulIfnetIndex;      /* IFNET index of bound physical interface */
    ULONG  ulMsgType;         /* address added or deleted */
    ULONG  ulLogAddr[4];      /* address */
    ULONG  ulSubMaskLen;      /* Address mask length*/
    /* Begin:VISP V3R2C10 VRF chandra , 2014-03-18 */
    ULONG  ulInstanceID;
    /* End: VISP V3R2C10 VRF chandra , 2014-03-18 */      
} SFIB_AM6_MSG_S;

/******************  from fiba_pub_defs.h************************/
#define FIB6_LOADBALANCE_ENABLE    1
#define FIB6_LOADBALANCE_DISABLE   0

/* Search flags */
#define FIB6_RTF_UP                0x1         /* route usable */
#define FIB6_RTF_GATEWAY           0x2         /* destination is a gateway */
#define FIB6_RTF_HOST              0x4         /* host entry (net otherwise) */
#define FIB6_RTF_REJECT            0x8         /* host or net unreachable */

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _VISP_IR_SFIB_H_ */
