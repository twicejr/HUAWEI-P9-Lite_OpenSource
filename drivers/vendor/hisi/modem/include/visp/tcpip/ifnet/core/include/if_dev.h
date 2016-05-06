/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                         IF_DEV.H  
 *
 *  Project Code: VISP1.5
 *   Module Name: IFNET
 *  Date Created: 2000/03/8 
 *        Author: yuanjie
 *   Description: 设备相关头文件
 *               
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2000/03/8       yuanjie         Create
 *  2006/03/30      liai            Adjust for D00654
 *  2006/04/21      liai            Adjust for D00878
 *
 ************************************************************************/

#ifndef _TCPIP_IF_DEV_H_
#define _TCPIP_IF_DEV_H_

#ifdef  __cplusplus
extern "C"{
#endif


/************************************************************************
 * 请在这里填写该头文件的具体内容                                       *
 ************************************************************************/

#define IF_CREATE_DEVLINK       11  /* need modified */

ULONG IF_SetDevLinkPtr(ULONG ulType,DEVLINK_S ** ppDev);

ULONG IF_GetDevLinkLen(DEVLINK_S* pDev);




#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _TEMPLETE_H_ */

